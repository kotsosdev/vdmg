#include "../../include/cpu.hpp"

#include <cstdint>

uint8_t CPU::next_u8() {
    uint8_t val = mmu->read(regs.pc());
    regs.set_pc(regs.pc() + 1);
    return val;
}

int8_t CPU::next_i8() {
    return (int8_t)(next_u8());
}

uint16_t CPU::next_u16() {
    uint16_t val = (mmu->read(regs.pc() + 1) << 8) | mmu->read(regs.pc());
    regs.set_pc(regs.pc() + 2);
    return val;
}