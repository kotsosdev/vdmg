#pragma once

#include "./apu/apu.hpp"
#include "./cpu/cpu.hpp"
#include "./mmu/mmu.hpp"
#include "./ppu/ppu.hpp"

struct Bus {
    APU* apu{nullptr};
    CPU* cpu{nullptr};
    MMU* mmu{nullptr};
    PPU* ppu{nullptr};

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t byte);
};