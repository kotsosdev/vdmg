#pragma once

#include <cstdint>

class Registers {
    public:
        uint16_t pc() const {return pc_reg;}
        uint16_t sp() const {return sp_reg;}
        uint16_t af() const {return af_reg;}
        uint16_t bc() const {return bc_reg;}
        uint16_t de() const {return de_reg;}
        uint16_t hl() const {return hl_reg;}
        uint8_t a() const {return af_reg >> 8;}
        uint8_t f() const {return af_reg & F_MASK;}
        uint8_t b() const {return bc_reg >> 8;}
        uint8_t c() const {return bc_reg & LO_MASK;}
        uint8_t d() const {return de_reg >> 8;}
        uint8_t e() const {return de_reg & LO_MASK;}
        uint8_t h() const {return hl_reg >> 8;}
        uint8_t l() const {return hl_reg & LO_MASK;}

        void set_pc(uint16_t pc) {pc_reg = pc;}
        void set_sp(uint16_t sp) {sp_reg = sp;}
        void set_af(uint16_t af) {af_reg = af & AF_MASK;}
        void set_bc(uint16_t bc) {bc_reg = bc;}
        void set_de(uint16_t de) {de_reg = de;}
        void set_hl(uint16_t hl) {hl_reg = hl;}
        void set_a(uint8_t a) {af_reg = (a << 8) | (af_reg & F_MASK);}
        void set_f(uint8_t f) {af_reg = (af_reg & HI_MASK) | (f & F_MASK);}
        void set_f(bool z, bool n, bool h, bool c) {set_f((z << 7) | (n << 6) | (h << 5) | (c << 4));} // Manually set flags
        void set_b(uint8_t b) {bc_reg = (b << 8) | (bc_reg & LO_MASK);}
        void set_c(uint8_t c) {bc_reg = (bc_reg & HI_MASK) | c;}
        void set_d(uint8_t d) {de_reg = (d << 8) | (de_reg & LO_MASK);}
        void set_e(uint8_t e) {de_reg = (de_reg & HI_MASK) | e;}
        void set_h(uint8_t h) {hl_reg = (h << 8) | (hl_reg & LO_MASK);}
        void set_l(uint8_t l) {hl_reg = (hl_reg & HI_MASK) | l;}

        void inc_pc() {pc_reg++;}
        void inc_sp() {sp_reg++;}

        void dec_pc() {pc_reg--;}
        void dec_sp() {sp_reg--;}

        void add_pc(uint16_t val) {pc_reg += val;}
        void add_sp(uint16_t val) {sp_reg += val;}

        void sub_pc(uint16_t val) {pc_reg -= val;}
        void sub_sp(uint16_t val) {sp_reg -= val;}

    private:
        static constexpr uint16_t HI_MASK{0xff00};
        static constexpr uint16_t LO_MASK{0x00ff};
        static constexpr uint16_t F_MASK{0x00f0};
        static constexpr uint16_t AF_MASK{0xfff0};

        uint16_t pc_reg{0x0100};
        uint16_t sp_reg{0xfffe};
        uint16_t af_reg{0x01b0};
        uint16_t bc_reg{0x0013};
        uint16_t de_reg{0x00d8};
        uint16_t hl_reg{0x014d};
};