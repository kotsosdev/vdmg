#include "../../include/cpu.hpp"

#include <print>
#include <cstdio>
#include <cstdint>

using std::println;

void CPU::set_mmu(MMU* mmu) {
    this->mmu = mmu;
}

void CPU::reset() {
    regs.set_sp(0xfffe);
    regs.set_pc(0x0100);
    regs.set_a(0x01);
    regs.set_b(0x00);
    regs.set_c(0x13);
    regs.set_d(0x00);
    regs.set_e(0xd8);
    regs.set_f(0xb0);
    regs.set_h(0x01);
    regs.set_l(0x4d);
}

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

void CPU::cp(uint8_t val) {
    sub(val);
}

uint8_t CPU::cpl() {
    uint8_t res = ~regs.a();

    regs.set_n_flag(true);
    regs.set_h_flag(true);

    return res;
}

void CPU::jr(int8_t offset) {
    regs.set_pc(regs.pc() + static_cast<int16_t>(offset));
}

void CPU::jp(uint16_t addr) {
    regs.set_pc(addr);
}

void CPU::call(uint16_t addr) {
    push(regs.pc());
    regs.set_pc(addr);
}

void CPU::rst(uint8_t addr) {
    call(0x00 | addr);
}

void CPU::ret() {
    regs.set_pc(pop());
}

uint8_t CPU::rlca() {
    uint8_t msb = (regs.a() & 0x80) >> 7;
    uint8_t res = (regs.a() << 1) | msb;

    regs.set_z_flag(false);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(msb);

    return res;
}

uint8_t CPU::rrca() {
    uint8_t lsb = regs.a() & 0x01;
    uint8_t res = (lsb << 7) | (regs.a() >> 1);

    regs.set_z_flag(false);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

void CPU::stop() {
    stopped = true;
}

uint8_t CPU::rla() {
    uint8_t msb = (regs.a() & 0x80) >> 7;
    uint8_t res = (regs.a() << 1) | static_cast<uint8_t>(regs.c_flag());

    regs.set_z_flag(false);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(msb);

    return res;
}

uint8_t CPU::rra() {
    uint8_t lsb = regs.a() & 0x01;
    uint8_t res = (static_cast<uint8_t>(regs.c_flag()) << 7) | (regs.a() >> 1);

    regs.set_z_flag(false);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

uint8_t CPU::daa() {
    uint8_t adj = 0x00;
    bool c_flag = false;
    uint8_t res = regs.a();

    if (regs.n_flag()) {

        if (regs.h_flag()) {
            adj |= 0x06;
        }
        if (regs.c_flag()) {
            adj |= 0x60;
            c_flag = true;
        }
        res -= adj;

    } else {

        if (((res & 0x0f) > 0x09) || regs.h_flag()) {
            adj |= 0x06;
        }
        if ((res > 0x99) || regs.c_flag()) {
            adj |= 0x60;
            c_flag = true;
        }
        res += adj;

    }

    regs.set_z_flag(!res);
    regs.set_h_flag(false);
    regs.set_c_flag(c_flag);

    return res;
}

void CPU::scf() {
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(true);
}

void CPU::ccf() {
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(!regs.c_flag());
}

void CPU::halt() {
    bool interrupts = pending_interrupts();
    halt_bug_flag = !ime && interrupts;
    halted = !interrupts;
}

void CPU::reti() {
    ret();
    ime = true;
}

void CPU::di() {
    ime = false;
}

void CPU::ei() {
    ime_pending = 2;
}

void CPU::unused(uint8_t op) {
    println(stderr, "Unused opcode {:#04x} was run", static_cast<int>(op));
    stop();
}

void CPU::bit(uint8_t bit, uint8_t val) {
    uint8_t mask = 0x01 << bit;

    regs.set_z_flag(!(val & mask));
    regs.set_n_flag(false);
    regs.set_h_flag(true);
}

uint8_t CPU::res(uint8_t bit, uint8_t val) {
    uint8_t mask = ~(0x01 << bit);
    uint8_t res = val & mask;
    
    return res;
}

uint8_t CPU::set(uint8_t bit, uint8_t val) {
    uint8_t mask = 0x01 << bit;
    uint8_t res = val | mask;

    return res;
}

uint8_t CPU::rlc(uint8_t val) {
    uint8_t msb = (val & 0x80) >> 7;
    uint8_t res = (val << 1) | msb;

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(msb);

    return res;
}

uint8_t CPU::rrc(uint8_t val) {
    uint8_t lsb = val & 0x01;
    uint8_t res = (lsb << 7) | (val >> 1);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

uint8_t CPU::rl(uint8_t val) {
    uint8_t msb = (val & 0x80) >> 7;
    uint8_t res = (val << 1) | static_cast<uint8_t>(regs.c_flag());

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(msb);

    return res;
}

uint8_t CPU::rr(uint8_t val) {
    uint8_t lsb = val & 0x01;
    uint8_t res = (static_cast<uint8_t>(regs.c_flag()) << 7) | (val >> 1);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

uint8_t CPU::sla(uint8_t val) {
    uint8_t msb = (val & 0x80) >> 7;
    uint8_t res = val << 1;

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(msb);

    return res;
}

uint8_t CPU::sra(uint8_t val) {
    uint8_t msb_mask = val & 0x80;
    uint8_t lsb = val & 0x01;
    uint8_t res = msb_mask | (val >> 1);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

uint8_t CPU::srl(uint8_t val) {
    uint8_t lsb = val & 0x01;
    uint8_t res = val >> 1;

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(lsb);

    return res;
}

uint8_t CPU::swap(uint8_t val) {
    uint8_t high = val & 0xf0;
    uint8_t low = val & 0x0f;
    uint8_t res = (low << 4) | (high >> 4);

    regs.set_z_flag(!res);
    regs.set_n_flag(false);
    regs.set_h_flag(false);
    regs.set_c_flag(false);

    return res;
}