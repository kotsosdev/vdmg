#pragma once

#include "./registers.hpp"
#include "../bus.hpp"

#include <cstdint>

class CPU {
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);

        void set_bus(Bus* b);

    private:
        uint8_t wram[0x2000]{}; // 0xc000 - 0xdfff
        uint8_t io[0x10]{}; // 0xff00 - 0xff0f
        uint8_t boot{}; // 0xff50
        uint8_t hram[0x7f]{}; // 0xff80 - 0xfffe
        uint8_t ie{}; // 0xffff

        typedef uint8_t (CPU::*OpFunc)();
        OpFunc op_table[0x100]{};
        OpFunc op_cb_table[0x100]{};
        bool locked{};

        Bus* bus{};
        Registers regs{};

        uint8_t next_u8();
        int8_t next_i8();
        uint16_t next_u16();
};