#include "../../include/cpu/cpu.hpp"

#include <cstdint>

uint8_t CPU::next_u8() {
    uint8_t val = memory->read(regs.pc());
    regs.inc_pc();
    return val;
}

int8_t CPU::next_i8() {
    return (int8_t)(next_u8());
}

uint16_t CPU::next_u16() {
    uint16_t val = (memory->read(regs.pc() + 1) << 8) | memory->read(regs.pc());
    regs.add_pc(2);
    return val;
}