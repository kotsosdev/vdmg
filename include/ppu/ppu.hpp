#pragma once

#include <cstdint>

class PPU {
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);

    private:
        uint8_t vram[0x2000]{}; /// 0x8000 - 0x9fff
        uint8_t oam[0xa0]{}; /// 0xfe00 - 0xfe9f
        uint8_t io1[0x5]{}; /// 0xff40 - 0xff45
        uint8_t io2[0x5]{}; /// 0xff47 - 0xff4b
};