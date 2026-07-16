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
    uint8_t low = next_u8();
    uint8_t high = next_u8();
    return (static_cast<uint16_t>(high) << 8) | (static_cast<uint16_t>(low));
}

uint16_t CPU::sp_offset(int8_t offset) {
    uint16_t full_sum = (
        static_cast<uint16_t>(regs.sp() & 0x00ff) +
        static_cast<uint16_t>(offset & 0x00ff)
    );
    uint8_t half_sum = (
        static_cast<uint8_t>(regs.sp() & 0x0f) +
        static_cast<uint8_t>(offset & 0x0f)
    );
    uint16_t res = (
        regs.sp() +
        static_cast<int16_t>(offset)
    );

    regs.set_z_flag(false);
    regs.set_n_flag(false);
    regs.set_h_flag(half_sum & 0x10);
    regs.set_c_flag(full_sum & 0x0100);

    return res;
}

void CPU::push(uint16_t val) {
    regs.set_sp(regs.sp() - 2);
    mmu->write(regs.sp(), val);
}

uint16_t CPU::pop() {
    uint16_t res = (
        mmu->read(regs.sp() + 1) << 8) |
        mmu->read(regs.sp()
    );
    regs.set_sp(regs.sp() + 2);
    return res;
}

uint8_t CPU::add(uint8_t val) {
    uint16_t full_sum = (
        static_cast<uint16_t>(regs.a()) +
        static_cast<uint16_t>(val)
    );
    uint8_t half_sum = (
        (regs.a() & 0x0f) +
        (val & 0x0f)
    );
    uint8_t res = static_cast<uint8_t>(full_sum);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(half_sum & 0x10);
    regs.set_c_flag(full_sum & 0x0100);

    return res;
}

uint16_t CPU::add(uint16_t val) {
    uint32_t full_sum = (
        static_cast<uint32_t>(regs.hl()) +
        static_cast<uint32_t>(val)
    );
    uint16_t half_sum = (
        static_cast<uint16_t>(regs.hl() & 0x0fff) +
        static_cast<uint16_t>(val & 0x0fff)
    );
    uint16_t res = static_cast<uint16_t>(full_sum);

    regs.set_n_flag(false);
    regs.set_h_flag(half_sum & 0x1000);
    regs.set_c_flag(full_sum & 0x00010000);

    return res;
}

uint8_t CPU::adc(uint8_t val) {
    uint16_t full_sum = ( 
        static_cast<uint16_t>(regs.a()) +
        static_cast<uint16_t>(val) +
        static_cast<uint16_t>(regs.c_flag())
    );
    uint8_t half_sum = (
        (regs.a() & 0x0f) +
        (val & 0x0f) +
        static_cast<uint8_t>(regs.c_flag())
    );
    uint8_t res = static_cast<uint8_t>(full_sum);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(half_sum & 0x10);
    regs.set_c_flag(full_sum & 0x0100);

    return res;
}

uint8_t CPU::inc(uint8_t val) {
    uint8_t half_sum = (val & 0x0f) + 0x01;
    uint8_t res = val + 0x01;
    
    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(half_sum & 0x10);
    
    return res;
}

uint16_t CPU::inc(uint16_t val) {
    return val + 0x0001;
}

uint8_t CPU::sub(uint8_t val) {
    uint8_t half_a = regs.a() & 0x0f;
    uint8_t half_val = val & 0x0f;
    uint8_t res = regs.a() - val;

    regs.set_z_flag(!res);
    regs.set_n_flag(true);
    regs.set_h_flag(half_a < half_val);
    regs.set_c_flag(regs.a() < val);

    return res;
}

uint8_t CPU::sbc(uint8_t val) {
    uint16_t full_val = static_cast<uint16_t>(val) + static_cast<uint16_t>(regs.c_flag());
    uint8_t half_a = regs.a() & 0x0f;
    uint16_t half_val = static_cast<uint16_t>(val & 0x0f) + static_cast<uint16_t>(regs.c_flag());
    uint8_t res = (
        regs.a() -
        val -
        static_cast<uint8_t>(regs.c_flag())
    );

    regs.set_z_flag(!res);
    regs.set_n_flag(true);
    regs.set_h_flag(half_a < half_val);
    regs.set_c_flag(regs.a() < full_val);

    return res;
}

uint8_t CPU::dec(uint8_t val) {
    uint8_t half_val = val & 0x0f;
    uint8_t res = val - 0x01;
    
    regs.set_z_flag(!res);
    regs.set_n_flag(true);
    regs.set_h_flag(half_val < 1);

    return res;
}

uint16_t CPU::dec(uint16_t val) {
    return val - 0x0001;
}

uint8_t CPU::bit_and(uint8_t val) {
    uint8_t res = regs.a() & val;
    
    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(true);
    regs.set_c_flag(false);

    return res;
}

uint8_t CPU::bit_or(uint8_t val) {
    uint8_t res = regs.a() | val;
    
    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(false);

    return res;
}

uint8_t CPU::bit_xor(uint8_t val) {
    uint8_t res = regs.a() ^ val;
    
    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(false);

    return res;
}