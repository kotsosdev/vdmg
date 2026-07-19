#include "../../include/cpu.hpp"

uint8_t CPU::op_0x00() {
    return 4;
}

uint8_t CPU::op_0x01() {
    regs.set_bc(next_u16());
    return 12;
}

uint8_t CPU::op_0x02() {
    mmu->write(regs.bc(), regs.a());
    return 8;
}

uint8_t CPU::op_0x03() {
    regs.set_bc(inc(regs.bc()));
    return 8;
}

uint8_t CPU::op_0x04() {
    regs.set_b(inc(regs.b()));
    return 4;
}

uint8_t CPU::op_0x05() {
    regs.set_b(dec(regs.b()));
    return 4;
}

uint8_t CPU::op_0x06() {
    regs.set_b(next_u8());
    return 8;
}

uint8_t CPU::op_0x07() {
    regs.set_a(rlca());
    return 4;
}

uint8_t CPU::op_0x08() {
    mmu->write(next_u16(), regs.sp());
    return 20;
}

uint8_t CPU::op_0x09() {
    regs.set_hl(add(regs.bc()));
    return 8;
}

uint8_t CPU::op_0x0a() {
    regs.set_a(mmu->read(regs.bc()));
    return 8;
}

uint8_t CPU::op_0x0b() {
    regs.set_bc(dec(regs.bc()));
    return 8;
}

uint8_t CPU::op_0x0c() {
    regs.set_c(inc(regs.c()));
    return 4;
}

uint8_t CPU::op_0x0d() {
    regs.set_c(dec(regs.c()));
    return 4;
}

uint8_t CPU::op_0x0e() {
    regs.set_c(next_u8());
    return 8;
}

uint8_t CPU::op_0x0f() {
    regs.set_a(rrca());
    return 4;
}

uint8_t CPU::op_0x10() {
    stop();
    return 4;
}

uint8_t CPU::op_0x11() {
    regs.set_de(next_u16());
    return 12;
}

uint8_t CPU::op_0x12() {
    mmu->write(regs.de(), regs.a());
    return 8;
}

uint8_t CPU::op_0x13() {
    regs.set_de(inc(regs.de()));
    return 8;
}

uint8_t CPU::op_0x14() {
    regs.set_d(inc(regs.d()));
    return 4;
}

uint8_t CPU::op_0x15() {
    regs.set_d(dec(regs.d()));
    return 4;
}

uint8_t CPU::op_0x16() {
    regs.set_d(next_u8());
    return 8;
}

uint8_t CPU::op_0x17() {
    regs.set_a(rla());
    return 4;
}

uint8_t CPU::op_0x18() {
    jr(next_i8());
    return 12;
}

uint8_t CPU::op_0x19() {
    regs.set_hl(add(regs.de()));
    return 8;
}

uint8_t CPU::op_0x1a() {
    regs.set_a(mmu->read(regs.de()));
    return 8;
}

uint8_t CPU::op_0x1b() {
    regs.set_de(dec(regs.de()));
    return 8;
}

uint8_t CPU::op_0x1c() {
    regs.set_e(inc(regs.e()));
    return 4;
}

uint8_t CPU::op_0x1d() {
    regs.set_e(dec(regs.e()));
    return 4;
}

uint8_t CPU::op_0x1e() {
    regs.set_e(next_u8());
    return 8;
}

uint8_t CPU::op_0x1f() {
    regs.set_a(rra());
    return 4;
}

uint8_t CPU::op_0x20() {
    int8_t offset = next_i8();
    if (!regs.z_flag()) {
        jr(offset);
        return 12;
    }
    return 8;
}

uint8_t CPU::op_0x21() {
    regs.set_hl(next_u16());
    return 12;
}

uint8_t CPU::op_0x22() {
    mmu->write(regs.hl(), regs.a());
    regs.set_hl(inc(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x23() {
    regs.set_hl(inc(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x24() {
    regs.set_h(inc(regs.h()));
    return 4;
}

uint8_t CPU::op_0x25() {
    regs.set_h(dec(regs.h()));
    return 4;
}

uint8_t CPU::op_0x26() {
    regs.set_h(next_u8());
    return 8;
}

uint8_t CPU::op_0x27() {
    regs.set_a(daa());
    return 4;
}

uint8_t CPU::op_0x28() {
    int8_t offset = next_i8();
    if (regs.z_flag()) {
        jr(offset);
        return 12;
    }
    return 8;
}

uint8_t CPU::op_0x29() {
    regs.set_hl(add(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x2a() {
    regs.set_a(mmu->read(regs.hl()));
    regs.set_hl(inc(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x2b() {
    regs.set_hl(dec(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x2c() {
    regs.set_l(inc(regs.l()));
    return 4;
}

uint8_t CPU::op_0x2d() {
    regs.set_l(dec(regs.l()));
    return 4;
}

uint8_t CPU::op_0x2e() {
    regs.set_l(next_u8());
    return 8;
}

uint8_t CPU::op_0x2f() {
    regs.set_a(cpl());
    return 4;
}

uint8_t CPU::op_0x30() {
    int8_t offset = next_i8();
    if (!regs.c_flag()) {
        jr(offset);
        return 12;
    }
    return 8;
}

uint8_t CPU::op_0x31() {
    regs.set_sp(next_u16());
    return 12;
}

uint8_t CPU::op_0x32() {
    mmu->write(regs.hl(), regs.a());
    regs.set_hl(dec(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x33() {
    regs.set_sp(inc(regs.sp()));
    return 8;
}

uint8_t CPU::op_0x34() {
    mmu->write(regs.hl(), inc(mmu->read(regs.hl())));
    return 12;
}

uint8_t CPU::op_0x35() {
    mmu->write(regs.hl(), dec(mmu->read(regs.hl())));
    return 12;
}

uint8_t CPU::op_0x36() {
    mmu->write(regs.hl(), next_u8());
    return 12;
}

uint8_t CPU::op_0x37() {
    scf();
    return 4;
}

uint8_t CPU::op_0x38() {
    int8_t offset = next_i8();
    if (regs.c_flag()) {
        jr(offset);
        return 12;
    }
    return 8;
}

uint8_t CPU::op_0x39() {
    regs.set_hl(add(regs.sp()));
    return 8;
}

uint8_t CPU::op_0x3a() {
    regs.set_a(mmu->read(regs.hl()));
    regs.set_hl(dec(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x3b() {
    regs.set_sp(dec(regs.sp()));
    return 8;
}

uint8_t CPU::op_0x3c() {
    regs.set_a(inc(regs.a()));
    return 4;
}

uint8_t CPU::op_0x3d() {
    regs.set_a(dec(regs.a()));
    return 4;
}

uint8_t CPU::op_0x3e() {
    regs.set_a(next_u8());
    return 8;
}

uint8_t CPU::op_0x3f() {
    ccf();
    return 4;
}

uint8_t CPU::op_0x40() {
    return 4;
}

uint8_t CPU::op_0x41() {
    regs.set_b(regs.c());
    return 4;
}

uint8_t CPU::op_0x42() {
    regs.set_b(regs.d());
    return 4;
}

uint8_t CPU::op_0x43() {
    regs.set_b(regs.e());
    return 4;
}

uint8_t CPU::op_0x44() {
    regs.set_b(regs.h());
    return 4;
}

uint8_t CPU::op_0x45() {
    regs.set_b(regs.l());
    return 4;
}

uint8_t CPU::op_0x46() {
    regs.set_b(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x47() {
    regs.set_b(regs.a());
    return 4;
}

uint8_t CPU::op_0x48() {
    regs.set_c(regs.b());
    return 4;
}

uint8_t CPU::op_0x49() {
    return 4;
}

uint8_t CPU::op_0x4a() {
    regs.set_c(regs.d());
    return 4;
}

uint8_t CPU::op_0x4b() {
    regs.set_c(regs.e());
    return 4;
}

uint8_t CPU::op_0x4c() {
    regs.set_c(regs.h());
    return 4;
}

uint8_t CPU::op_0x4d() {
    regs.set_c(regs.l());
    return 4;
}

uint8_t CPU::op_0x4e() {
    regs.set_c(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x4f() {
    regs.set_c(regs.a());
    return 4;
}

uint8_t CPU::op_0x50() {
    regs.set_d(regs.b());
    return 4;
}

uint8_t CPU::op_0x51() {
    regs.set_d(regs.c());
    return 4;
}

uint8_t CPU::op_0x52() {
    return 4;
}

uint8_t CPU::op_0x53() {
    regs.set_d(regs.e());
    return 4;
}

uint8_t CPU::op_0x54() {
    regs.set_d(regs.h());
    return 4;
}

uint8_t CPU::op_0x55() {
    regs.set_d(regs.l());
    return 4;
}

uint8_t CPU::op_0x56() {
    regs.set_d(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x57() {
    regs.set_d(regs.a());
    return 4;
}

uint8_t CPU::op_0x58() {
    regs.set_e(regs.b());
    return 4;
}

uint8_t CPU::op_0x59() {
    regs.set_e(regs.c());
    return 4;
}

uint8_t CPU::op_0x5a() {
    regs.set_e(regs.d());
    return 4;
}

uint8_t CPU::op_0x5b() {
    return 4;
}

uint8_t CPU::op_0x5c() {
    regs.set_e(regs.h());
    return 4;
}

uint8_t CPU::op_0x5d() {
    regs.set_e(regs.l());
    return 4;
}

uint8_t CPU::op_0x5e() {
    regs.set_e(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x5f() {
    regs.set_e(regs.a());
    return 4;
}

uint8_t CPU::op_0x60() {
    regs.set_h(regs.b());
    return 4;
}

uint8_t CPU::op_0x61() {
    regs.set_h(regs.c());
    return 4;
}

uint8_t CPU::op_0x62() {
    regs.set_h(regs.d());
    return 4;
}

uint8_t CPU::op_0x63() {
    regs.set_h(regs.e());
    return 4;
}

uint8_t CPU::op_0x64() {
    return 4;
}

uint8_t CPU::op_0x65() {
    regs.set_h(regs.l());
    return 4;
}

uint8_t CPU::op_0x66() {
    regs.set_h(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x67() {
    regs.set_h(regs.a());
    return 4;
}

uint8_t CPU::op_0x68() {
    regs.set_l(regs.b());
    return 4;
}

uint8_t CPU::op_0x69() {
    regs.set_l(regs.c());
    return 4;
}

uint8_t CPU::op_0x6a() {
    regs.set_l(regs.d());
    return 4;
}

uint8_t CPU::op_0x6b() {
    regs.set_l(regs.e());
    return 4;
}

uint8_t CPU::op_0x6c() {
    regs.set_l(regs.h());
    return 4;
}

uint8_t CPU::op_0x6d() {
    return 4;
}

uint8_t CPU::op_0x6e() {
    regs.set_l(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x6f() {
    regs.set_l(regs.a());
    return 4;
}

uint8_t CPU::op_0x70() {
    mmu->write(regs.hl(), regs.b());
    return 8;
}

uint8_t CPU::op_0x71() {
    mmu->write(regs.hl(), regs.c());
    return 8;
}

uint8_t CPU::op_0x72() {
    mmu->write(regs.hl(), regs.d());
    return 8;
}

uint8_t CPU::op_0x73() {
    mmu->write(regs.hl(), regs.e());
    return 8;
}

uint8_t CPU::op_0x74() {
    mmu->write(regs.hl(), regs.h());
    return 8;
}

uint8_t CPU::op_0x75() {
    mmu->write(regs.hl(), regs.l());
    return 8;
}

uint8_t CPU::op_0x76() {
    halt();
    return 4;
}

uint8_t CPU::op_0x77() {
    mmu->write(regs.hl(), regs.a());
    return 8;
}

uint8_t CPU::op_0x78() {
    regs.set_a(regs.b());
    return 4;
}

uint8_t CPU::op_0x79() {
    regs.set_a(regs.c());
    return 4;
}

uint8_t CPU::op_0x7a() {
    regs.set_a(regs.d());
    return 4;
}

uint8_t CPU::op_0x7b() {
    regs.set_a(regs.e());
    return 4;
}

uint8_t CPU::op_0x7c() {
    regs.set_a(regs.h());
    return 4;
}

uint8_t CPU::op_0x7d() {
    regs.set_a(regs.l());
    return 4;
}

uint8_t CPU::op_0x7e() {
    regs.set_a(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0x7f() {
    return 4;
}

uint8_t CPU::op_0x80() {
    regs.set_a(add(regs.b()));
    return 4;
}

uint8_t CPU::op_0x81() {
    regs.set_a(add(regs.c()));
    return 4;
}

uint8_t CPU::op_0x82() {
    regs.set_a(add(regs.d()));
    return 4;
}

uint8_t CPU::op_0x83() {
    regs.set_a(add(regs.e()));
    return 4;
}

uint8_t CPU::op_0x84() {
    regs.set_a(add(regs.h()));
    return 4;
}

uint8_t CPU::op_0x85() {
    regs.set_a(add(regs.l()));
    return 4;
}

uint8_t CPU::op_0x86() {
    regs.set_a(add(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0x87() {
    regs.set_a(add(regs.a()));
    return 4;
}

uint8_t CPU::op_0x88() {
    regs.set_a(adc(regs.b()));
    return 4;
}

uint8_t CPU::op_0x89() {
    regs.set_a(adc(regs.c()));
    return 4;
}

uint8_t CPU::op_0x8a() {
    regs.set_a(adc(regs.d()));
    return 4;
}

uint8_t CPU::op_0x8b() {
    regs.set_a(adc(regs.e()));
    return 4;
}

uint8_t CPU::op_0x8c() {
    regs.set_a(adc(regs.h()));
    return 4;
}

uint8_t CPU::op_0x8d() {
    regs.set_a(adc(regs.l()));
    return 4;
}

uint8_t CPU::op_0x8e() {
    regs.set_a(adc(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0x8f() {
    regs.set_a(adc(regs.a()));
    return 4;
}

uint8_t CPU::op_0x90() {
    regs.set_a(sub(regs.b()));
    return 4;
}

uint8_t CPU::op_0x91() {
    regs.set_a(sub(regs.c()));
    return 4;
}

uint8_t CPU::op_0x92() {
    regs.set_a(sub(regs.d()));
    return 4;
}

uint8_t CPU::op_0x93() {
    regs.set_a(sub(regs.e()));
    return 4;
}

uint8_t CPU::op_0x94() {
    regs.set_a(sub(regs.h()));
    return 4;
}

uint8_t CPU::op_0x95() {
    regs.set_a(sub(regs.l()));
    return 4;
}

uint8_t CPU::op_0x96() {
    regs.set_a(sub(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0x97() {
    regs.set_a(sub(regs.a()));
    return 4;
}

uint8_t CPU::op_0x98() {
    regs.set_a(sbc(regs.b()));
    return 4;
}

uint8_t CPU::op_0x99() {
    regs.set_a(sbc(regs.c()));
    return 4;
}

uint8_t CPU::op_0x9a() {
    regs.set_a(sbc(regs.d()));
    return 4;
}

uint8_t CPU::op_0x9b() {
    regs.set_a(sbc(regs.e()));
    return 4;
}

uint8_t CPU::op_0x9c() {
    regs.set_a(sbc(regs.h()));
    return 4;
}

uint8_t CPU::op_0x9d() {
    regs.set_a(sbc(regs.l()));
    return 4;
}

uint8_t CPU::op_0x9e() {
    regs.set_a(sbc(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0x9f() {
    regs.set_a(sbc(regs.a()));
    return 4;
}

uint8_t CPU::op_0xa0() {
    regs.set_a(bit_and(regs.b()));
    return 4;
}

uint8_t CPU::op_0xa1() {
    regs.set_a(bit_and(regs.c()));
    return 4;
}

uint8_t CPU::op_0xa2() {
    regs.set_a(bit_and(regs.d()));
    return 4;
}

uint8_t CPU::op_0xa3() {
    regs.set_a(bit_and(regs.e()));
    return 4;
}

uint8_t CPU::op_0xa4() {
    regs.set_a(bit_and(regs.h()));
    return 4;
}

uint8_t CPU::op_0xa5() {
    regs.set_a(bit_and(regs.l()));
    return 4;
}

uint8_t CPU::op_0xa6() {
    regs.set_a(bit_and(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0xa7() {
    regs.set_a(bit_and(regs.a()));
    return 4;
}

uint8_t CPU::op_0xa8() {
    regs.set_a(bit_xor(regs.b()));
    return 4;
}

uint8_t CPU::op_0xa9() {
    regs.set_a(bit_xor(regs.c()));
    return 4;
}

uint8_t CPU::op_0xaa() {
    regs.set_a(bit_xor(regs.d()));
    return 4;
}

uint8_t CPU::op_0xab() {
    regs.set_a(bit_xor(regs.e()));
    return 4;
}

uint8_t CPU::op_0xac() {
    regs.set_a(bit_xor(regs.h()));
    return 4;
}

uint8_t CPU::op_0xad() {
    regs.set_a(bit_xor(regs.l()));
    return 4;
}

uint8_t CPU::op_0xae() {
    regs.set_a(bit_xor(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0xaf() {
    regs.set_a(bit_xor(regs.a()));
    return 4;
}

uint8_t CPU::op_0xb0() {
    regs.set_a(bit_or(regs.b()));
    return 4;
}

uint8_t CPU::op_0xb1() {
    regs.set_a(bit_or(regs.c()));
    return 4;
}

uint8_t CPU::op_0xb2() {
    regs.set_a(bit_or(regs.d()));
    return 4;
}

uint8_t CPU::op_0xb3() {
    regs.set_a(bit_or(regs.e()));
    return 4;
}

uint8_t CPU::op_0xb4() {
    regs.set_a(bit_or(regs.h()));
    return 4;
}

uint8_t CPU::op_0xb5() {
    regs.set_a(bit_or(regs.l()));
    return 4;
}

uint8_t CPU::op_0xb6() {
    regs.set_a(bit_or(mmu->read(regs.hl())));
    return 8;
}

uint8_t CPU::op_0xb7() {
    regs.set_a(bit_or(regs.a()));
    return 4;
}

uint8_t CPU::op_0xb8() {
    cp(regs.b());
    return 4;
}

uint8_t CPU::op_0xb9() {
    cp(regs.c());
    return 4;
}

uint8_t CPU::op_0xba() {
    cp(regs.d());
    return 4;
}

uint8_t CPU::op_0xbb() {
    cp(regs.e());
    return 4;
}

uint8_t CPU::op_0xbc() {
    cp(regs.h());
    return 4;
}

uint8_t CPU::op_0xbd() {
    cp(regs.l());
    return 4;
}

uint8_t CPU::op_0xbe() {
    cp(mmu->read(regs.hl()));
    return 8;
}

uint8_t CPU::op_0xbf() {
    cp(regs.a());
    return 4;
}

uint8_t CPU::op_0xc0() {
    if (!regs.z_flag()) {
        ret();
        return 20;
    }
    return 8;
}

uint8_t CPU::op_0xc1() {
    regs.set_bc(pop());
    return 12;
}

uint8_t CPU::op_0xc2() {
    uint16_t addr = next_u16();
    if (!regs.z_flag()) {
        jp(addr);
        return 16;
    }
    return 12;
}

uint8_t CPU::op_0xc3() {
    jp(next_u16());
    return 16;
}

uint8_t CPU::op_0xc4() {
    uint16_t addr = next_u16();
    if (!regs.z_flag()) {
        call(addr);
        return 24;
    }
    return 12;
}

uint8_t CPU::op_0xc5() {
    push(regs.bc());
    return 16;
}

uint8_t CPU::op_0xc6() {
    regs.set_a(add(next_u8()));
    return 8;
}

uint8_t CPU::op_0xc7() {
    rst(0x00);
    return 16;
}

uint8_t CPU::op_0xc8() {
    if (regs.z_flag()) {
        ret();
        return 20;
    }
    return 8;
}

uint8_t CPU::op_0xc9() {
    ret();
    return 16;
}

uint8_t CPU::op_0xca() {
    uint16_t offset = next_u16();
    if (regs.z_flag()) {
        jp(offset);
        return 16;
    }
    return 12;
}

uint8_t CPU::op_0xcc() {
    uint16_t addr = next_u16();
    if (regs.z_flag()) {
        call(addr);
        return 24;
    }
    return 12;
}

uint8_t CPU::op_0xcd() {
    call(next_u16());
    return 24;
}

uint8_t CPU::op_0xce() {
    regs.set_a(adc(next_u8()));
    return 8;
}

uint8_t CPU::op_0xcf() {
    rst(0x08);
    return 16;
}

uint8_t CPU::op_0xd0() {
    if (!regs.c_flag()) {
        ret();
        return 20;
    }
    return 8;
}

uint8_t CPU::op_0xd1() {
    regs.set_de(pop());
    return 12;
}

uint8_t CPU::op_0xd2() {
    uint16_t addr = next_u16();
    if (!regs.c_flag()) {
        jp(addr);
        return 16;
    }
    return 12;
}

uint8_t CPU::op_0xd3() {
    unused(0xd3);
    return 4;
}

uint8_t CPU::op_0xd4() {
    uint16_t addr = next_u16();
    if (!regs.c_flag()) {
        call(addr);
        return 24;
    }
    return 12;
}

uint8_t CPU::op_0xd5() {
    push(regs.de());
    return 16;
}

uint8_t CPU::op_0xd6() {
    regs.set_a(sub(next_u8()));
    return 8;
}

uint8_t CPU::op_0xd7() {
    rst(0x10);
    return 16;
}

uint8_t CPU::op_0xd8() {
    if (regs.c_flag()) {
        ret();
        return 20;
    }
    return 8;
}

uint8_t CPU::op_0xd9() {
    reti();
    return 16;
}

uint8_t CPU::op_0xda() {
    uint16_t addr = next_u16();
    if (regs.c_flag()) {
        jp(addr);
        return 16;
    }
    return 12;
}

uint8_t CPU::op_0xdb() {
    unused(0xdb);
    return 4;
}

uint8_t CPU::op_0xdc() {
    uint16_t addr = next_u16();
    if (regs.c_flag()) {
        call(addr);
        return 24;
    }
    return 12;
}

uint8_t CPU::op_0xdd() {
    unused(0xdd);
    return 4;
}

uint8_t CPU::op_0xde() {
    regs.set_a(sbc(next_u8()));
    return 8;
}

uint8_t CPU::op_0xdf() {
    rst(0x18);
    return 16;
}

uint8_t CPU::op_0xe0() {
    mmu->write(static_cast<uint16_t>(0xff00 | next_u8()), regs.a());
    return 12;
}

uint8_t CPU::op_0xe1() {
    regs.set_hl(pop());
    return 12;
}

uint8_t CPU::op_0xe2() {
    mmu->write(static_cast<uint16_t>(0xff00 | regs.c()), regs.a());
    return 8;
}

uint8_t CPU::op_0xe3() {
    unused(0xe3);
    return 4;
}

uint8_t CPU::op_0xe4() {
    unused(0xe4);
    return 4;
}

uint8_t CPU::op_0xe5() {
    push(regs.hl());
    return 16;
}

uint8_t CPU::op_0xe6() {
    regs.set_a(bit_and(next_u8()));
    return 8;
}

uint8_t CPU::op_0xe7() {
    rst(0x20);
    return 16;
}

uint8_t CPU::op_0xe8() {
    regs.set_sp(sp_offset(next_i8()));
    return 16;
}

uint8_t CPU::op_0xe9() {
    jp(regs.hl());
    return 4;
}

uint8_t CPU::op_0xea() {
    mmu->write(next_u16(), regs.a());
    return 16;
}

uint8_t CPU::op_0xeb() {
    unused(0xeb);
    return 4;
}

uint8_t CPU::op_0xec() {
    unused(0xec);
    return 4;
}

uint8_t CPU::op_0xed() {
    unused(0xed);
    return 4;
}

uint8_t CPU::op_0xee() {
    regs.set_a(bit_xor(next_u8()));
    return 8;
}

uint8_t CPU::op_0xef() {
    rst(0x28);
    return 16;
}

uint8_t CPU::op_0xf0() {
    regs.set_a(mmu->read(static_cast<uint16_t>(0xff00 | next_u8())));
    return 12;
}

uint8_t CPU::op_0xf1() {
    regs.set_af(pop());
    return 12;
}

uint8_t CPU::op_0xf2() {
    regs.set_a(mmu->read(static_cast<uint16_t>(0xff00 | regs.c())));
    return 8;
}

uint8_t CPU::op_0xf3() {
    di();
    return 4;
}

uint8_t CPU::op_0xf4() {
    unused(0xf4);
    return 4;
}

uint8_t CPU::op_0xf5() {
    push(regs.af());
    return 16;
}

uint8_t CPU::op_0xf6() {
    regs.set_a(bit_or(next_u8()));
    return 8;
}

uint8_t CPU::op_0xf7() {
    rst(0x30);
    return 16;
}

uint8_t CPU::op_0xf8() {
    regs.set_hl(sp_offset(next_i8()));
    return 12;
}

uint8_t CPU::op_0xf9() {
    regs.set_sp(regs.hl());
    return 8;
}

uint8_t CPU::op_0xfa() {
    regs.set_a(mmu->read(next_u16()));
    return 16;
}

uint8_t CPU::op_0xfb() {
    ei();
    return 4;
}

uint8_t CPU::op_0xfc() {
    unused(0xfc);
    return 4;
}

uint8_t CPU::op_0xfd() {
    unused(0xfd);
    return 4;
}

uint8_t CPU::op_0xfe() {
    cp(next_u8());
    return 8;
}

uint8_t CPU::op_0xff() {
    rst(0x38);
    return 16;
}