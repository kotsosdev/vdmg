#include "../../include/cpu/cpu.hpp"

uint8_t CPU::op_00() {
    d8();
    return 4;
}

uint8_t CPU::op_01() {
    regs.set_bc(d16());
    return 12;
}

uint8_t CPU::op_02() {
    bus->write(regs.bc(), regs.a());
    return 8;
}

uint8_t CPU::op_03() {
    regs.set_bc(regs.bc() + 1);
    return 8;
}

uint8_t CPU::op_04() {
    return 4;
}

uint8_t CPU::op_05() {
    return 4;
}

uint8_t CPU::op_06() {
    regs.set_b(d8());
    return 8;
}

uint8_t CPU::op_07() {
    return 4;
}

uint8_t CPU::op_08() {
    bus->write(a16(), regs.sp());
    return 20;
}

uint8_t CPU::op_09() {
    return 8;
}

uint8_t CPU::op_0a() {
    regs.set_a(bus->read(regs.bc()));
    return 8;
}

uint8_t CPU::op_0b() {
    regs.set_bc(regs.bc() - 1);
    return 8;
}

uint8_t CPU::op_0c() {
    return 4;
}

uint8_t CPU::op_0d() {
    return 4;
}

uint8_t CPU::op_0e() {
    regs.set_c(d8());
    return 8;
}

uint8_t CPU::op_0f() {
    return 4;
}

uint8_t CPU::op_10() {
    d8();
    stopped = true;
    return 4;
}

uint8_t CPU::op_11() {
    regs.set_de(d16());
    return 12;
}

uint8_t CPU::op_12() {
    bus->write(regs.de(), regs.a());
    return 8;
}

uint8_t CPU::op_13() {
    regs.set_de(regs.de() + 1);
    return 8;
}

uint8_t CPU::op_14() {
    return 4;
}

uint8_t CPU::op_15() {
    return 4;
}

uint8_t CPU::op_16() {
    regs.set_d(d8());
    return 8;
}

uint8_t CPU::op_17() {
    return 4;
}

uint8_t CPU::op_18() {
    
    return 12;
}

uint8_t CPU::op_19() {
    return 8;
}

uint8_t CPU::op_1a() {
    return 8;
}

uint8_t CPU::op_1b() {
    return 8;
}

uint8_t CPU::op_1c() {
    return 4;
}

uint8_t CPU::op_1d() {
    return 4;
}

uint8_t CPU::op_1e() {
    return 8;
}

uint8_t CPU::op_1f() {
    return 4;
}

uint8_t CPU::op_20() {
    return 12 / 8;
}

uint8_t CPU::op_21() {
    return 12;
}

uint8_t CPU::op_22() {
    return 8;
}

uint8_t CPU::op_23() {
    return 8;
}

uint8_t CPU::op_24() {
    return 4;
}

uint8_t CPU::op_25() {
    return 4;
}

uint8_t CPU::op_26() {
    return 8;
}

uint8_t CPU::op_27() {
    return 4;
}

uint8_t CPU::op_28() {
    return 12 / 8;
}

uint8_t CPU::op_29() {
    return 8;
}

uint8_t CPU::op_2a() {
    return 8;
}

uint8_t CPU::op_2b() {
    return 8;
}

uint8_t CPU::op_2c() {
    return 4;
}

uint8_t CPU::op_2d() {
    return 4;
}

uint8_t CPU::op_2e() {
    return 8;
}

uint8_t CPU::op_2f() {
    return 4;
}

uint8_t CPU::op_30() {
    return 12 / 8;
}

uint8_t CPU::op_31() {
    return 12;
}

uint8_t CPU::op_32() {
    return 8;
}

uint8_t CPU::op_33() {
    return 8;
}

uint8_t CPU::op_34() {
    return 12;
}

uint8_t CPU::op_35() {
    return 12;
}

uint8_t CPU::op_36() {
    return 12;
}

uint8_t CPU::op_37() {
    return 4;
}

uint8_t CPU::op_38() {
    return 12 / 8;
}

uint8_t CPU::op_39() {
    return 8;
}

uint8_t CPU::op_3a() {
    return 8;
}

uint8_t CPU::op_3b() {
    return 8;
}

uint8_t CPU::op_3c() {
    return 4;
}

uint8_t CPU::op_3d() {
    return 4;
}

uint8_t CPU::op_3e() {
    return 8;
}

uint8_t CPU::op_3f() {
    return 4;
}

uint8_t CPU::op_40() {}

uint8_t CPU::op_41() {}

uint8_t CPU::op_42() {}

uint8_t CPU::op_43() {}

uint8_t CPU::op_44() {}

uint8_t CPU::op_45() {}

uint8_t CPU::op_46() {}

uint8_t CPU::op_47() {}

uint8_t CPU::op_48() {}

uint8_t CPU::op_49() {}

uint8_t CPU::op_4a() {}

uint8_t CPU::op_4b() {}

uint8_t CPU::op_4c() {}

uint8_t CPU::op_4d() {}

uint8_t CPU::op_4e() {}

uint8_t CPU::op_4f() {}

uint8_t CPU::op_50() {}

uint8_t CPU::op_51() {}

uint8_t CPU::op_52() {}

uint8_t CPU::op_53() {}

uint8_t CPU::op_54() {}

uint8_t CPU::op_55() {}

uint8_t CPU::op_56() {}

uint8_t CPU::op_57() {}

uint8_t CPU::op_58() {}

uint8_t CPU::op_59() {}

uint8_t CPU::op_5a() {}

uint8_t CPU::op_5b() {}

uint8_t CPU::op_5c() {}

uint8_t CPU::op_5d() {}

uint8_t CPU::op_5e() {}

uint8_t CPU::op_5f() {}

uint8_t CPU::op_60() {}

uint8_t CPU::op_61() {}

uint8_t CPU::op_62() {}

uint8_t CPU::op_63() {}

uint8_t CPU::op_64() {}

uint8_t CPU::op_65() {}

uint8_t CPU::op_66() {}

uint8_t CPU::op_67() {}

uint8_t CPU::op_68() {}

uint8_t CPU::op_69() {}

uint8_t CPU::op_6a() {}

uint8_t CPU::op_6b() {}

uint8_t CPU::op_6c() {}

uint8_t CPU::op_6d() {}

uint8_t CPU::op_6e() {}

uint8_t CPU::op_6f() {}

uint8_t CPU::op_70() {}

uint8_t CPU::op_71() {}

uint8_t CPU::op_72() {}

uint8_t CPU::op_73() {}

uint8_t CPU::op_74() {}

uint8_t CPU::op_75() {}

uint8_t CPU::op_76() {}

uint8_t CPU::op_77() {}

uint8_t CPU::op_78() {}

uint8_t CPU::op_79() {}

uint8_t CPU::op_7a() {}

uint8_t CPU::op_7b() {}

uint8_t CPU::op_7c() {}

uint8_t CPU::op_7d() {}

uint8_t CPU::op_7e() {}

uint8_t CPU::op_7f() {}

uint8_t CPU::op_80() {}

uint8_t CPU::op_81() {}

uint8_t CPU::op_82() {}

uint8_t CPU::op_83() {}

uint8_t CPU::op_84() {}

uint8_t CPU::op_85() {}

uint8_t CPU::op_86() {}

uint8_t CPU::op_87() {}

uint8_t CPU::op_88() {}

uint8_t CPU::op_89() {}

uint8_t CPU::op_8a() {}

uint8_t CPU::op_8b() {}

uint8_t CPU::op_8c() {}

uint8_t CPU::op_8d() {}

uint8_t CPU::op_8e() {}

uint8_t CPU::op_8f() {}

uint8_t CPU::op_90() {}

uint8_t CPU::op_91() {}

uint8_t CPU::op_92() {}

uint8_t CPU::op_93() {}

uint8_t CPU::op_94() {}

uint8_t CPU::op_95() {}

uint8_t CPU::op_96() {}

uint8_t CPU::op_97() {}

uint8_t CPU::op_98() {}

uint8_t CPU::op_99() {}

uint8_t CPU::op_9a() {}

uint8_t CPU::op_9b() {}

uint8_t CPU::op_9c() {}

uint8_t CPU::op_9d() {}

uint8_t CPU::op_9e() {}

uint8_t CPU::op_9f() {}

uint8_t CPU::op_a0() {}

uint8_t CPU::op_a1() {}

uint8_t CPU::op_a2() {}

uint8_t CPU::op_a3() {}

uint8_t CPU::op_a4() {}

uint8_t CPU::op_a5() {}

uint8_t CPU::op_a6() {}

uint8_t CPU::op_a7() {}

uint8_t CPU::op_a8() {}

uint8_t CPU::op_a9() {}

uint8_t CPU::op_aa() {}

uint8_t CPU::op_ab() {}

uint8_t CPU::op_ac() {}

uint8_t CPU::op_ad() {}

uint8_t CPU::op_ae() {}

uint8_t CPU::op_af() {}

uint8_t CPU::op_b0() {}

uint8_t CPU::op_b1() {}

uint8_t CPU::op_b2() {}

uint8_t CPU::op_b3() {}

uint8_t CPU::op_b4() {}

uint8_t CPU::op_b5() {}

uint8_t CPU::op_b6() {}

uint8_t CPU::op_b7() {}

uint8_t CPU::op_b8() {}

uint8_t CPU::op_b9() {}

uint8_t CPU::op_ba() {}

uint8_t CPU::op_bb() {}

uint8_t CPU::op_bc() {}

uint8_t CPU::op_bd() {}

uint8_t CPU::op_be() {}

uint8_t CPU::op_bf() {}

uint8_t CPU::op_c0() {}

uint8_t CPU::op_c1() {}

uint8_t CPU::op_c2() {}

uint8_t CPU::op_c3() {}

uint8_t CPU::op_c4() {}

uint8_t CPU::op_c5() {}

uint8_t CPU::op_c6() {}

uint8_t CPU::op_c7() {}

uint8_t CPU::op_c8() {}

uint8_t CPU::op_c9() {}

uint8_t CPU::op_ca() {}

uint8_t CPU::op_cb() {}

uint8_t CPU::op_cc() {}

uint8_t CPU::op_cd() {}

uint8_t CPU::op_ce() {}

uint8_t CPU::op_cf() {}

uint8_t CPU::op_d0() {}

uint8_t CPU::op_d1() {}

uint8_t CPU::op_d2() {}

uint8_t CPU::op_d3() {}

uint8_t CPU::op_d4() {}

uint8_t CPU::op_d5() {}

uint8_t CPU::op_d6() {}

uint8_t CPU::op_d7() {}

uint8_t CPU::op_d8() {}

uint8_t CPU::op_d9() {}

uint8_t CPU::op_da() {}

uint8_t CPU::op_db() {}

uint8_t CPU::op_dc() {}

uint8_t CPU::op_dd() {}

uint8_t CPU::op_de() {}

uint8_t CPU::op_df() {}

uint8_t CPU::op_e0() {}

uint8_t CPU::op_e1() {}

uint8_t CPU::op_e2() {}

uint8_t CPU::op_e3() {}

uint8_t CPU::op_e4() {}

uint8_t CPU::op_e5() {}

uint8_t CPU::op_e6() {}

uint8_t CPU::op_e7() {}

uint8_t CPU::op_e8() {}

uint8_t CPU::op_e9() {}

uint8_t CPU::op_ea() {}

uint8_t CPU::op_eb() {}

uint8_t CPU::op_ec() {}

uint8_t CPU::op_ed() {}

uint8_t CPU::op_ee() {}

uint8_t CPU::op_ef() {}

uint8_t CPU::op_f0() {}

uint8_t CPU::op_f1() {}

uint8_t CPU::op_f2() {}

uint8_t CPU::op_f3() {}

uint8_t CPU::op_f4() {}

uint8_t CPU::op_f5() {}

uint8_t CPU::op_f6() {}

uint8_t CPU::op_f7() {}

uint8_t CPU::op_f8() {}

uint8_t CPU::op_f9() {}

uint8_t CPU::op_fa() {}

uint8_t CPU::op_fb() {}

uint8_t CPU::op_fc() {}

uint8_t CPU::op_fd() {}

uint8_t CPU::op_fe() {}

uint8_t CPU::op_ff() {}