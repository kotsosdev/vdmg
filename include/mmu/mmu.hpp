#pragma once

#include <cstdint>

class MMU {
    private:
        uint8_t wram[0x2000];
        uint8_t hram[0x80];

    public:
};