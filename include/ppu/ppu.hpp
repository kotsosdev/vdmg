#pragma once

#include <cstdint>

class PPU {
    private:
        uint8_t vram[0x2000];
        uint8_t oam[0xa0];

    public:
};