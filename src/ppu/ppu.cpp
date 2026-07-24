#include "ppu.hpp"

#include <cstdint>
#include <algorithm>
#include <array>

using std::fill;
using std::array;
using std::sort;

void PPU::sync_ppu(int cycles) {
    running_ppu_cycles += cycles;
    
    bool lcd_enabled = mmu->direct_read(0xff40) & 0x80;
    uint8_t stat = mmu->direct_read(0xff41);

    if (!lcd_enabled) {
        running_ppu_cycles = 0;
        running_window_line = 0;
        mmu->direct_write(0xff44, 0);
        mmu->direct_write(0xff41, (stat & 0xfc) | 0x01);
        rgba_buffer.fill(0x000000ff);
        return;
    }

    uint8_t ly = mmu->direct_read(0xff44);
    if (running_ppu_cycles >= 456) {
        ++ly;
        if (ly >= 154) {
            ly = 0;
            running_window_line = 0;
        }

        mmu->direct_write(0xff44, ly);

        if (ly == 144) mmu->direct_write(0xff0f, mmu->direct_read(0xff0f) | 0x01);

        running_ppu_cycles -= 456;
    }

    uint8_t curr_mode = stat & 0x03;
    uint8_t next_mode = (
        (ly >= 144) ? 0x01 :
        (running_ppu_cycles < 80) ? 0x02 :
        (running_ppu_cycles < 252) ? 0x03 : 0x00
    );

    if (curr_mode != next_mode) {
        if (next_mode == 0x02) oam_scan();
        else if (next_mode == 0x03) draw_pixels();
    }

    mmu->direct_write(0xff41, (stat & 0xfc) | next_mode);

    lyc_coincidence();
}

void PPU::oam_scan() {
    uint16_t addr = 0xfe00;
    int ly = static_cast<int>(mmu->direct_read(0xff44));
    int sprite_height = (mmu->direct_read(0xff40) & 0x04) ? 16 : 8;
    int oam_i = 0;

    sprite_buffer.clear();
    while (oam_i < 40 && sprite_buffer.size() < 10) {
        uint8_t y = mmu->direct_read(addr);
        int screen_y = static_cast<int>(y) - 16;

        if (screen_y <= ly && ly < (screen_y + sprite_height)) {
            uint8_t x = mmu->direct_read(addr + 0x0001);
            uint8_t tile_i = mmu->direct_read(addr + 0x0002);
            tile_i = (sprite_height == 16) ? (tile_i & 0xfe) : tile_i;
            uint8_t attrs = mmu->direct_read(addr + 0x0003);

            sprite_buffer.emplace_back(y, x, tile_i, attrs, oam_i);
        }

        ++oam_i;
        addr += 0x0004;
    }

    sort(sprite_buffer.begin(), sprite_buffer.end(), [](const Sprite& s1, const Sprite& s2) {
        if (s1.x != s2.x) return s1.x < s2.x;
        return s1.oam_i < s2.oam_i;
    });
}

void PPU::draw_pixels() {
    if (headless) return;

    uint8_t lcdc = mmu->direct_read(0xff40);
    uint16_t window_map_base_addr = (lcdc & 0x40) ? 0x9c00 : 0x9800;
    bool window_display = (lcdc & 0x20);
    bool u_addr_mode = lcdc & 0x10;
    uint16_t bg_map_base_addr = (lcdc & 0x08) ? 0x9c00 : 0x9800;
    int sprite_height = (mmu->direct_read(0xff40) & 0x04) ? 16 : 8;
    bool sprite_display = lcdc & 0x02;
    bool bg_window_display = lcdc & 0x01;

    uint8_t bgp = mmu->direct_read(0xff47);

    uint8_t ly = mmu->direct_read(0xff44);
    uint8_t scx = mmu->direct_read(0xff43);
    uint8_t scy = mmu->direct_read(0xff42);
    uint8_t wx = mmu->direct_read(0xff4b);
    uint8_t wy = mmu->direct_read(0xff4a);

    bool window_on_screen = window_display && wx <= 166 && wy <= ly;
    bool window_drawn = false;

    int window_tile_y = running_window_line / 8;
    int window_pixel_y = running_window_line % 8;

    int world_y = (scy + ly) % 256;
    int bg_tile_y = world_y / 8;
    int bg_pixel_y = world_y % 8;
    int line_start = ly * 160;

    fill(bgw_pixel_buffer.begin() + line_start, bgw_pixel_buffer.begin() + line_start + 160, 0x00);

    for (int x_offset = 0; x_offset < 160; ++x_offset) {
        int screen_i = line_start + x_offset;

        // None
        if (!bg_window_display) {
            bgw_pixel_buffer[screen_i] = 0x00;
            rgba_buffer[screen_i] = 0x000000ff;
            continue;
        }

        // Window
        if (window_on_screen && ((x_offset + 7) >= wx)) {
            window_drawn = true;

            int window_x_offset = x_offset + 7 - wx;
            int window_tile_x = window_x_offset / 8;
            int window_pixel_x = window_x_offset % 8;

            uint8_t tile_i = mmu->direct_read(window_map_base_addr + (window_tile_y * 32) + window_tile_x);

            uint16_t pixel_addr;
            if (u_addr_mode) pixel_addr = 0x8000 + (tile_i * 16) + (window_pixel_y * 2);
            else pixel_addr = 0x9000 + (static_cast<int8_t>(tile_i) * 16) + (window_pixel_y * 2);

            uint8_t low = mmu->direct_read(pixel_addr);
            uint8_t high = mmu->direct_read(pixel_addr + 0x01);

            int bit_offset = 7 - window_pixel_x;
            uint8_t pixel = (((high >> bit_offset) & 1) << 1) | ((low >> bit_offset) & 1);

            bgw_pixel_buffer[screen_i] = pixel;

            int palette_i = (bgp >> (pixel * 2)) & 0x03;
            rgba_buffer[screen_i] = palette[palette_i];

        // Background
        } else {

            int world_x = (scx + x_offset) % 256;
            int bg_tile_x = world_x / 8;
            int bg_pixel_x = world_x % 8;

            uint8_t tile_i = mmu->direct_read(bg_map_base_addr + (bg_tile_y * 32) + bg_tile_x);

            uint16_t pixel_addr;
            if (u_addr_mode) pixel_addr = 0x8000 + (tile_i * 16) + (bg_pixel_y * 2);
            else pixel_addr = 0x9000 + (static_cast<int8_t>(tile_i) * 16) + (bg_pixel_y * 2);

            uint8_t low = mmu->direct_read(pixel_addr);
            uint8_t high = mmu->direct_read(pixel_addr + 0x01);

            int bit_offset = 7 - bg_pixel_x;
            uint8_t pixel = (((high >> bit_offset) & 1) << 1) | ((low >> bit_offset) & 1);

            bgw_pixel_buffer[screen_i] = pixel;
            
            int palette_i = (bgp >> (pixel * 2)) & 0x03;
            rgba_buffer[screen_i] = palette[palette_i];
        }
    }

    if (window_drawn) ++running_window_line;

    // Sprites
    if (sprite_display) {
        array<bool, 160> sprite_drawn{};

        for (const Sprite& sprite : sprite_buffer) {
            bool bg_priority = sprite.attrs & 0x80;
            bool flip_y = sprite.attrs & 0x40;
            bool flip_x = sprite.attrs & 0x20;
            uint8_t obp = (sprite.attrs & 0x10) ? mmu->direct_read(0xff49) : mmu->direct_read(0xff48);

            int sprite_row = ly - (sprite.y - 16);

            if (flip_y) sprite_row = sprite_height - 1 - sprite_row;

            int tile_offset = sprite_row / 8;
            int tile_row = sprite_row % 8;

            uint16_t pixel_addr = 0x8000 + ((sprite.tile_i + tile_offset) * 16) + (tile_row * 2);
            uint8_t low = mmu->direct_read(pixel_addr);
            uint8_t high = mmu->direct_read(pixel_addr + 0x01);

            for (int x_offset = 0; x_offset < 8; ++x_offset) {
                int screen_x = sprite.x - 8 + x_offset;
                int screen_i = line_start + screen_x;
                if (screen_x < 0 || screen_x >= 160) continue;
                if (sprite_drawn[screen_x]) continue;

                int bit_offset = flip_x ? x_offset : (7 - x_offset);
                uint8_t pixel = (((high >> bit_offset) & 1) << 1) | ((low >> bit_offset) & 1);
                
                if (pixel == 0x00) continue;
                sprite_drawn[screen_x] = true;

                if (bg_priority && bgw_pixel_buffer[screen_i] > 0) continue;

                int palette_i = (obp >> (pixel * 2)) & 0x03;
                rgba_buffer[screen_i] = palette[palette_i];
            }
        }
    }
}

void PPU::lyc_coincidence() {
    uint8_t ly = mmu->direct_read(0xff44);
    uint8_t lyc = mmu->direct_read(0xff45);
    uint8_t stat = mmu->direct_read(0xff41);

    if (ly == lyc) stat |= 0x04;  
    else stat &= 0xfb;

    mmu->direct_write(0xff41, stat);
}