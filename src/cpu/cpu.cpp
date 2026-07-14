#include "../../include/cpu.hpp"

#include <cstdint>

uint8_t CPU::next_u8() {
    uint8_t val = mmu->read(regs.pc());
    regs.set_pc(regs.pc() + 1);
    return val;
}

int8_t CPU::next_i8() {
    return static_cast<int8_t>(next_u8());
}

uint16_t CPU::next_u16() {
    uint16_t val = (mmu->read(regs.pc() + 1) << 8) | mmu->read(regs.pc());
    regs.set_pc(regs.pc() + 2);
    return val;
}

void CPU::push(uint16_t val) {
    regs.set_sp(regs.sp() - 2);
    mmu->write(regs.sp(), val);
}

uint16_t CPU::pop() {
    uint16_t res = (mmu->read(regs.sp() + 1) << 8) | mmu->read(regs.sp());
    regs.set_sp(regs.sp() + 2);
    return res;
}

uint8_t CPU::add() {

}

uint8_t CPU::adc(uint8_t val) {
    uint16_t full = ( 
        static_cast<uint16_t>(regs.a()) +
        static_cast<uint16_t>(val) +
        static_cast<uint16_t>(regs.c_flag())
    );
    uint8_t low = (
        (regs.a() & 0x0f) +
        (val & 0x0f) +
        static_cast<uint8_t>(regs.c_flag())
    );
    uint8_t res = static_cast<uint8_t>(full);

    regs.set_z_flag(res == 0x00);
    regs.set_n_flag(false);
    regs.set_h_flag(low > 0x0f);
    regs.set_c_flag(full > 0xff);

    return res;
}

uint8_t CPU::sub() {

}

uint8_t CPU::sbc() {

}

uint8_t CPU::inc(uint8_t val) {
    uint8_t low = (val & 0x0f) + 0x01;
    uint8_t res = val + 0x01;
    
    regs.set_z_flag(res == 0x00);
    regs.set_n_flag(false);
    regs.set_h_flag(low > 0x0f);
    
    return res;
}

uint16_t CPU::inc(uint16_t val) {
    return ++val;
}

uint8_t CPU::dec() {

}

uint8_t CPU::daa() {

}