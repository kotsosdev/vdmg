#include "../include/ppu.hpp"

#include <cstdint>

void PPU::sync_ppu(int cycles) {
    running_ppu_cycles += cycles;
    uint8_t stat = mmu->read(0xff41);
    uint8_t ppu_mode = stat & 0x03;
    uint8_t ly = mmu->read(0xff44);

    if (!lcd) {
        running_ppu_cycles = 0;
        mmu->write(0xff44, static_cast<uint8_t>(0));
        mmu->write(0xff41, static_cast<uint8_t>((stat & 0xfc) | 0x01));
        return;
    }

    if (running_ppu_cycles <= 80 && ppu_mode != 0x02) {
        mmu->write(0xff41, static_cast<uint8_t>((stat & 0xfc) | 0x02));
        oam_scan();

    } else if (running_ppu_cycles <= 252 && ppu_mode != 0x03) {
        mmu->write(0xff41, static_cast<uint8_t>((stat & 0xfc) | 0x03));
        draw_pixels();

    } else if (running_ppu_cycles <= 456 && ppu_mode != 0x00) {
        mmu->write(0xff41, static_cast<uint8_t>((stat & 0xfc) | 0x00));

    } else if (ly >= 144 && ppu_mode != 0x01) {
        mmu->write(0xff41, static_cast<uint8_t>((stat & 0xfc) | 0x01));
    }

}

void PPU::set_mmu(MMU* mmu) {
    this->mmu = mmu;
}

void PPU::draw_pixels() {
    uint8_t ly = mmu->read(0xff44);
    uint8_t lyc = mmu->read(0xff45);

    int start_i = ly * 160;
    for (int i = start_i; i < start_i + 160; ++i) {

    }

    mmu->write(0xff44, ++ly);
}

void PPU::lyc_coincidence() {
    uint8_t ly = mmu->read(0xff44);
    uint8_t lyc = mmu->read(0xff45);
    uint8_t stat = mmu->read(0xff41);

    if (ly == lyc) stat |= 0x08;  
    else stat &= 0xf7;

    mmu->write(0xff41, stat);
}