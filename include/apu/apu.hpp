#pragma once

#include <cstdint>

class APU {
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);

    private:
        uint8_t io[0x17]; /// 0xff10 - 0xff26
        uint8_t wavram[0x10]; /// 0xff30 - 0xff3f
};