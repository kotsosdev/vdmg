#pragma once

#include "./bus.hpp"
#include "./cartridge/cartridge.hpp"
#include "./apu/apu.hpp"
#include "./cpu/cpu.hpp"
#include "./mmu/mmu.hpp"
#include "./ppu/ppu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    private:
        Bus bus;
        Cartridge cart;

        APU apu;
        CPU cpu{&bus};
        MMU mmu;
        PPU ppu;

        uint16_t div{0};
        uint16_t tima{0};

    public:
        VDMG();
};