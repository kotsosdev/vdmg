#pragma once

#include "./bus.hpp"
#include "./cartridge/cartridge.hpp"
#include "./apu/apu.hpp"
#include "./cpu/cpu.hpp"
#include "./ppu/ppu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    private:
        Bus bus;

        Cartridge cart;
        APU apu;
        CPU cpu;
        PPU ppu;

    public:
        VDMG();
};