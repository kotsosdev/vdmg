#include "../../include/cpu/cpu.hpp"

#include "../../include/bus.hpp"

#include <cstdint>

uint8_t CPU::next_u8() {
    uint8_t val = bus->read(regs.pc());
    regs.inc_pc();
    return val;
}

int8_t CPU::next_i8() {
    int8_t val = (int8_t)(bus->read(regs.pc()));
    regs.inc_pc();
    return val;
}

uint16_t CPU::next_u16() {
    uint16_t val = (bus->read(regs.pc() + 1) << 8) | bus->read(regs.pc());
    regs.add_pc(2);
    return val;
}

uint8_t CPU::read(uint16_t addr) {

}

void CPU::write(uint16_t addr, uint8_t val) {

}

void CPU::set_bus(Bus* b) {
    bus = b;
}