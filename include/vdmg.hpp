#pragma once

#include "./bus.hpp"
#include "./cartridge/cartridge.hpp"
#include "./apu/apu.hpp"
#include "./cpu/cpu.hpp"
#include "./ppu/ppu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    public:
        VDMG();

    private:
        Cartridge cart{};
        APU apu{};
        CPU cpu{};
        PPU ppu{};

        Bus bus{&cart, &apu, &cpu, &ppu};
};