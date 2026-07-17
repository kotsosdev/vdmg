#include "../../include/cpu.hpp"

uint8_t CPU::op_cb_0x00() {
    regs.set_b(rlc(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x01() {
    regs.set_c(rlc(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x02() {
    regs.set_d(rlc(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x03() {
    regs.set_e(rlc(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x04() {
    regs.set_h(rlc(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x05() {
    regs.set_l(rlc(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x06() {
    mmu->write(regs.hl(), rlc(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x07() {
    regs.set_a(rlc(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x08() {
    regs.set_b(rrc(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x09() {
    regs.set_c(rrc(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x0a() {
    regs.set_d(rrc(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x0b() {
    regs.set_e(rrc(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x0c() {
    regs.set_h(rrc(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x0d() {
    regs.set_l(rrc(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x0e() {
    mmu->write(regs.hl(), rrc(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x0f() {
    regs.set_a(rrc(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x10() {
    regs.set_b(rl(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x11() {
    regs.set_c(rl(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x12() {
    regs.set_d(rl(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x13() {
    regs.set_e(rl(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x14() {
    regs.set_h(rl(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x15() {
    regs.set_l(rl(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x16() {
    mmu->write(regs.hl(), rl(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x17() {
    regs.set_a(rl(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x18() {
    regs.set_b(rr(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x19() {
    regs.set_c(rr(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x1a() {
    regs.set_d(rr(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x1b() {
    regs.set_e(rr(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x1c() {
    regs.set_h(rr(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x1d() {
    regs.set_l(rr(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x1e() {
    mmu->write(regs.hl(), rr(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x1f() {
    regs.set_a(rr(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x20() {
    regs.set_b(sla(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x21() {
    regs.set_c(sla(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x22() {
    regs.set_d(sla(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x23() {
    regs.set_e(sla(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x24() {
    regs.set_h(sla(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x25() {
    regs.set_l(sla(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x26() {
    mmu->write(regs.hl(), sla(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x27() {
    regs.set_a(sla(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x28() {
    regs.set_b(sra(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x29() {
    regs.set_c(sra(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x2a() {
    regs.set_d(sra(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x2b() {
    regs.set_e(sra(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x2c() {
    regs.set_h(sra(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x2d() {
    regs.set_l(sra(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x2e() {
    mmu->write(regs.hl(), sra(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x2f() {
    regs.set_a(sra(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x30() {
    regs.set_b(swap(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x31() {
    regs.set_c(swap(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x32() {
    regs.set_d(swap(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x33() {
    regs.set_e(swap(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x34() {
    regs.set_h(swap(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x35() {
    regs.set_l(swap(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x36() {
    mmu->write(regs.hl(), swap(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x37() {
    regs.set_a(swap(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x38() {
    regs.set_b(srl(regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x39() {
    regs.set_c(srl(regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x3a() {
    regs.set_d(srl(regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x3b() {
    regs.set_e(srl(regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x3c() {
    regs.set_h(srl(regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x3d() {
    regs.set_l(srl(regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x3e() {
    mmu->write(regs.hl(), srl(mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x3f() {
    regs.set_a(srl(regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x40() {
    bit(0, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x41() {
    bit(0, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x42() {
    bit(0, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x43() {
    bit(0, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x44() {
    bit(0, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x45() {
    bit(0, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x46() {
    bit(0, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x47() {
    bit(0, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x48() {
    bit(1, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x49() {
    bit(1, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x4a() {
    bit(1, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x4b() {
    bit(1, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x4c() {
    bit(1, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x4d() {
    bit(1, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x4e() {
    bit(1, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x4f() {
    bit(1, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x50() {
    bit(2, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x51() {
    bit(2, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x52() {
    bit(2, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x53() {
    bit(2, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x54() {
    bit(2, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x55() {
    bit(2, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x56() {
    bit(2, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x57() {
    bit(2, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x58() {
    bit(3, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x59() {
    bit(3, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x5a() {
    bit(3, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x5b() {
    bit(3, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x5c() {
    bit(3, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x5d() {
    bit(3, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x5e() {
    bit(3, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x5f() {
    bit(3, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x60() {
    bit(4, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x61() {
    bit(4, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x62() {
    bit(4, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x63() {
    bit(4, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x64() {
    bit(4, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x65() {
    bit(4, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x66() {
    bit(4, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x67() {
    bit(4, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x68() {
    bit(5, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x69() {
    bit(5, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x6a() {
    bit(5, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x6b() {
    bit(5, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x6c() {
    bit(5, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x6d() {
    bit(5, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x6e() {
    bit(5, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x6f() {
    bit(5, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x70() {
    bit(6, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x71() {
    bit(6, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x72() {
    bit(6, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x73() {
    bit(6, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x74() {
    bit(6, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x75() {
    bit(6, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x76() {
    bit(6, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x77() {
    bit(6, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x78() {
    bit(7, regs.b());
    return 8;
}

uint8_t CPU::op_cb_0x79() {
    bit(7, regs.c());
    return 8;
}

uint8_t CPU::op_cb_0x7a() {
    bit(7, regs.d());
    return 8;
}

uint8_t CPU::op_cb_0x7b() {
    bit(7, regs.e());
    return 8;
}

uint8_t CPU::op_cb_0x7c() {
    bit(7, regs.h());
    return 8;
}

uint8_t CPU::op_cb_0x7d() {
    bit(7, regs.l());
    return 8;
}

uint8_t CPU::op_cb_0x7e() {
    bit(7, mmu->read(regs.hl()));
    return 12;
}

uint8_t CPU::op_cb_0x7f() {
    bit(7, regs.a());
    return 8;
}

uint8_t CPU::op_cb_0x80() {
    regs.set_b(res(0, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x81() {
    regs.set_c(res(0, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x82() {
    regs.set_d(res(0, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x83() {
    regs.set_e(res(0, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x84() {
    regs.set_h(res(0, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x85() {
    regs.set_l(res(0, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x86() {
    mmu->write(regs.hl(), res(0, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x87() {
    regs.set_a(res(0, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x88() {
    regs.set_b(res(1, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x89() {
    regs.set_c(res(1, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x8a() {
    regs.set_d(res(1, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x8b() {
    regs.set_e(res(1, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x8c() {
    regs.set_h(res(1, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x8d() {
    regs.set_l(res(1, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x8e() {
    mmu->write(regs.hl(), res(1, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x8f() {
    regs.set_a(res(1, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x90() {
    regs.set_b(res(2, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x91() {
    regs.set_c(res(2, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x92() {
    regs.set_d(res(2, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x93() {
    regs.set_e(res(2, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x94() {
    regs.set_h(res(2, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x95() {
    regs.set_l(res(2, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x96() {
    mmu->write(regs.hl(), res(2, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x97() {
    regs.set_a(res(2, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0x98() {
    regs.set_b(res(3, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0x99() {
    regs.set_c(res(3, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0x9a() {
    regs.set_d(res(3, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0x9b() {
    regs.set_e(res(3, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0x9c() {
    regs.set_h(res(3, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0x9d() {
    regs.set_l(res(3, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0x9e() {
    mmu->write(regs.hl(), res(3, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0x9f() {
    regs.set_a(res(3, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xa0() {
    regs.set_b(res(4, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xa1() {
    regs.set_c(res(4, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xa2() {
    regs.set_d(res(4, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xa3() {
    regs.set_e(res(4, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xa4() {
    regs.set_h(res(4, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xa5() {
    regs.set_l(res(4, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xa6() {
    mmu->write(regs.hl(), res(4, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xa7() {
    regs.set_a(res(4, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xa8() {
    regs.set_b(res(5, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xa9() {
    regs.set_c(res(5, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xaa() {
    regs.set_d(res(5, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xab() {
    regs.set_e(res(5, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xac() {
    regs.set_h(res(5, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xad() {
    regs.set_l(res(5, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xae() {
    mmu->write(regs.hl(), res(5, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xaf() {
    regs.set_a(res(5, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xb0() {
    regs.set_b(res(6, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xb1() {
    regs.set_c(res(6, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xb2() {
    regs.set_d(res(6, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xb3() {
    regs.set_e(res(6, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xb4() {
    regs.set_h(res(6, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xb5() {
    regs.set_l(res(6, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xb6() {
    mmu->write(regs.hl(), res(6, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xb7() {
    regs.set_a(res(6, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xb8() {
    regs.set_b(res(7, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xb9() {
    regs.set_c(res(7, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xba() {
    regs.set_d(res(7, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xbb() {
    regs.set_e(res(7, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xbc() {
    regs.set_h(res(7, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xbd() {
    regs.set_l(res(7, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xbe() {
    mmu->write(regs.hl(), res(7, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xbf() {
    regs.set_a(res(7, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xc0() {
    regs.set_b(set(0, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xc1() {
    regs.set_c(set(0, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xc2() {
    regs.set_d(set(0, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xc3() {
    regs.set_e(set(0, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xc4() {
    regs.set_h(set(0, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xc5() {
    regs.set_l(set(0, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xc6() {
    mmu->write(regs.hl(), set(0, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xc7() {
    regs.set_a(set(0, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xc8() {
    regs.set_b(set(1, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xc9() {
    regs.set_c(set(1, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xca() {
    regs.set_d(set(1, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xcb() {
    regs.set_e(set(1, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xcc() {
    regs.set_h(set(1, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xcd() {
    regs.set_l(set(1, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xce() {
    mmu->write(regs.hl(), set(1, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xcf() {
    regs.set_a(set(1, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xd0() {
    regs.set_b(set(2, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xd1() {
    regs.set_c(set(2, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xd2() {
    regs.set_d(set(2, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xd3() {
    regs.set_e(set(2, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xd4() {
    regs.set_h(set(2, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xd5() {
    regs.set_l(set(2, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xd6() {
    mmu->write(regs.hl(), set(2, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xd7() {
    regs.set_a(set(2, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xd8() {
    regs.set_b(set(3, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xd9() {
    regs.set_c(set(3, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xda() {
    regs.set_d(set(3, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xdb() {
    regs.set_e(set(3, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xdc() {
    regs.set_h(set(3, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xdd() {
    regs.set_l(set(3, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xde() {
    mmu->write(regs.hl(), set(3, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xdf() {
    regs.set_a(set(3, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xe0() {
    regs.set_b(set(4, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xe1() {
    regs.set_c(set(4, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xe2() {
    regs.set_d(set(4, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xe3() {
    regs.set_e(set(4, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xe4() {
    regs.set_h(set(4, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xe5() {
    regs.set_l(set(4, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xe6() {
    mmu->write(regs.hl(), set(4, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xe7() {
    regs.set_a(set(4, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xe8() {
    regs.set_b(set(5, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xe9() {
    regs.set_c(set(5, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xea() {
    regs.set_d(set(5, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xeb() {
    regs.set_e(set(5, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xec() {
    regs.set_h(set(5, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xed() {
    regs.set_l(set(5, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xee() {
    mmu->write(regs.hl(), set(5, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xef() {
    regs.set_a(set(5, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xf0() {
    regs.set_b(set(6, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xf1() {
    regs.set_c(set(6, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xf2() {
    regs.set_d(set(6, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xf3() {
    regs.set_e(set(6, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xf4() {
    regs.set_h(set(6, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xf5() {
    regs.set_l(set(6, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xf6() {
    mmu->write(regs.hl(), set(6, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xf7() {
    regs.set_a(set(6, regs.a()));
    return 8;
}

uint8_t CPU::op_cb_0xf8() {
    regs.set_b(set(7, regs.b()));
    return 8;
}

uint8_t CPU::op_cb_0xf9() {
    regs.set_c(set(7, regs.c()));
    return 8;
}

uint8_t CPU::op_cb_0xfa() {
    regs.set_d(set(7, regs.d()));
    return 8;
}

uint8_t CPU::op_cb_0xfb() {
    regs.set_e(set(7, regs.e()));
    return 8;
}

uint8_t CPU::op_cb_0xfc() {
    regs.set_h(set(7, regs.h()));
    return 8;
}

uint8_t CPU::op_cb_0xfd() {
    regs.set_l(set(7, regs.l()));
    return 8;
}

uint8_t CPU::op_cb_0xfe() {
    mmu->write(regs.hl(), set(7, mmu->read(regs.hl())));
    return 16;
}

uint8_t CPU::op_cb_0xff() {
    regs.set_a(set(7, regs.a()));
    return 8;
}