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

// TODO
void PPU::oam_scan() {

}

// TODO
void PPU::draw_pixels() {
    uint8_t ly = mmu->direct_read(0xff44);
    // uint8_t lyc = mmu->direct_read(0xff45);

    int start_i = ly * 160;
    for (int i = start_i; i < start_i + 160; ++i) {

    }

    mmu->write(0xff44, ++ly);
}

void PPU::lyc_coincidence() {
    uint8_t ly = mmu->direct_read(0xff44);
    uint8_t lyc = mmu->direct_read(0xff45);
    uint8_t stat = mmu->direct_read(0xff41);

    if (ly == lyc) stat |= 0x04;  
    else stat &= 0xfb;

    mmu->direct_write(0xff41, stat);
}