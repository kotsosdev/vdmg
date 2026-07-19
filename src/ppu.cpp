#include "../include/ppu.hpp"

#include <cstdint>
#include <iostream>

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
    while (running_ppu_cycles >= 456) {
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

void PPU::set_mmu(MMU* mmu) {
    this->mmu = mmu;
}

void PPU::oam_scan() {
    uint16_t addr = 0xfe00;
    int ly = static_cast<int>(mmu->direct_read(0xff44));
    int sprite_height = (mmu->direct_read(0xff40) & 0x04) ? 16 : 8;
    int oam_i = 0;

    sprite_buffer.clear();
    while (oam_i < 40 && sprite_buffer.size() < 10) {
        uint8_t y = mmu->direct_read(addr);
        int lcd_y = static_cast<int>(y) - 16;

        if (lcd_y <= ly && ly < (lcd_y + sprite_height)) {
            uint8_t x = mmu->direct_read(addr + 0x0001);
            uint8_t tile_i = mmu->direct_read(addr + 0x0002);
            uint8_t attrs = mmu->direct_read(addr + 0x0003);

            sprite_buffer.emplace_back(y, x, tile_i, attrs, oam_i);
        }

        ++oam_i;
        addr += 0x0004;
    }
}

// TODO
void PPU::draw_pixels() {
    uint8_t ly = mmu->direct_read(0xff44);
    uint8_t scx = mmu->direct_read(0xff43);
    uint8_t scy = mmu->direct_read(0xff42);

    for (int x_offset = 0; x_offset < 160; ++x_offset) {
        int x = (scx + x_offset) % 256;
        int y = (scy + ly) % 256;
        int i = (ly * 160) + x_offset;

        // frame[i] = get_pixel(x, y);
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