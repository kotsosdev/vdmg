#include "../include/ppu.hpp"

#include <cstdint>
#include <algorithm>
#include <array>

using std::sort;
using std::array;

void PPU::sync_ppu(int cycles) {
    running_ppu_cycles += cycles;
    
    bool lcd_enabled = mmu->direct_read(0xff40) & 0x80;
    uint8_t stat = mmu->direct_read(0xff41);

    if (!lcd_enabled) {
        running_ppu_cycles = 0;
        mmu->direct_write(0xff44, 0);
        mmu->direct_write(0xff41, (stat & 0xfc) | 0x01);
        return;
    }

    uint8_t ly = mmu->direct_read(0xff44);
    if (running_ppu_cycles >= 456) {
        ++ly;
        if (ly >= 154) ly = 0;

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
        if (s1.x != s2.x) return s1.x > s2.x;
        return s1.oam_i > s2.oam_i;
    });
}

void PPU::draw_pixels() {
    if (headless) return;

    uint8_t lcdc = mmu->direct_read(0xff40);
    bool window_tile_map = lcdc & 0x40;
    bool window_display = lcdc & 0x20;
    bool bg_window_u = lcdc & 0x10;
    bool bg_tile_map = lcdc & 0x08;
    int sprite_height = (mmu->direct_read(0xff40) & 0x04) ? 16 : 8;
    bool sprite_display = lcdc & 0x02;
    bool bg_window_display = lcdc & 0x01;

    uint8_t ly = mmu->direct_read(0xff44);

    uint8_t scx = mmu->direct_read(0xff43);
    uint8_t scy = mmu->direct_read(0xff42);

    uint8_t wx = mmu->direct_read(0xff4a);
    uint8_t wy = mmu->direct_read(0xff4b);

    int world_y = (scy + ly) % 256;
    int tile_y = world_y / 8;
    int pixel_y = world_y % 8;

    int line_start = ly * 160;

    for (int x_offset = 0; x_offset < 160; ++x_offset) {
        int world_x = (scx + x_offset) % 256;
        int tile_x = world_x / 8;
        int pixel_x = world_x % 8;
    }

    if (sprite_display) {
        for (const Sprite& sprite : sprite_buffer) {
            bool bg_priority = sprite.attrs & 0x80;
            bool flip_y = sprite.attrs & 0x40;
            bool flip_x = sprite.attrs & 0x20;
            uint8_t obp = (sprite.attrs & 0x10) ? mmu->read(0xff49) : mmu->read(0xff48);

            int rel_y = ly - (sprite.y - 16);
            int row_in_tile = flip_y ? (sprite_height - 1 - rel_y) : rel_y;

            uint16_t pixel_addr = 0x8000 + (sprite.tile_i * 16) + (row_in_tile * 2);
            uint8_t low = mmu->direct_read(pixel_addr);
            uint8_t high = mmu->direct_read(pixel_addr + 1);

            for (int x_offset = 0; x_offset < 8; ++x_offset) {
                int screen_x = sprite.x - 8 + x_offset;
                int screen_i = line_start + screen_x;
                if (screen_x < 0 || screen_x >= 160) continue;

                int bit_offset = flip_x ? x_offset : (7 - x_offset);

                uint8_t pixel = (((high >> bit_offset) & 1) << 1) | ((low >> bit_offset) & 1);
                
                if (pixel == 0x00) continue;
                if (bg_priority && bgw_pixel_buffer[screen_i] > 0) continue; // HACK: Restore background edge case

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