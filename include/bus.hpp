#pragma once

#include <cstdint>

class Cartridge;
class APU;
class CPU;
class PPU;

class Bus {
    public:
        Bus(Cartridge* cart, APU* apu, CPU* cpu, PPU* ppu);

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);
        void write(uint16_t addr, uint16_t val);

    private:
        Cartridge* cart{};
        APU* apu{};
        CPU* cpu{};
        PPU* ppu{};
};