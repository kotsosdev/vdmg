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
        uint8_t wram[0x2000]{}; /// 0xc000 - 0xdfff
        uint8_t io[0x10]{}; /// 0xff00 - 0xff0f
        uint8_t dma{}; /// 0xff46
        uint8_t boot{}; /// 0xff50
        uint8_t hram[0x7f]{}; /// 0xff80 - 0xfffe
        uint8_t ie{}; /// 0xffff

        Cartridge* cart{};
        APU* apu{};
        CPU* cpu{};
        PPU* ppu{};
};