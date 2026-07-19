#pragma once

#include "./mmu.hpp"

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
        uint8_t f() const {return af_reg & 0x00f0;}
        uint8_t b() const {return bc_reg >> 8;}
        uint8_t c() const {return bc_reg & 0x00ff;}
        uint8_t d() const {return de_reg >> 8;}
        uint8_t e() const {return de_reg & 0x00ff;}
        uint8_t h() const {return hl_reg >> 8;}
        uint8_t l() const {return hl_reg & 0x00ff;}

        bool z_flag() const {return (af_reg >> 7) & 0x01;}
        bool n_flag() const {return (af_reg >> 6) & 0x01;}
        bool h_flag() const {return (af_reg >> 5) & 0x01;}
        bool c_flag() const {return (af_reg >> 4) & 0x01;}

        void set_pc(uint16_t pc) {pc_reg = pc;}
        void set_sp(uint16_t sp) {sp_reg = sp;}
        void set_af(uint16_t af) {af_reg = af & 0xfff0;}
        void set_bc(uint16_t bc) {bc_reg = bc;}
        void set_de(uint16_t de) {de_reg = de;}
        void set_hl(uint16_t hl) {hl_reg = hl;}
        void set_a(uint8_t a) {af_reg = (a << 8) | (af_reg & 0x00f0);}
        void set_f(uint8_t f) {af_reg = (af_reg & 0xff00) | (f & 0x00f0);}
        void set_b(uint8_t b) {bc_reg = (b << 8) | (bc_reg & 0x00ff);}
        void set_c(uint8_t c) {bc_reg = (bc_reg & 0xff00) | c;}
        void set_d(uint8_t d) {de_reg = (d << 8) | (de_reg & 0x00ff);}
        void set_e(uint8_t e) {de_reg = (de_reg & 0xff00) | e;}
        void set_h(uint8_t h) {hl_reg = (h << 8) | (hl_reg & 0x00ff);}
        void set_l(uint8_t l) {hl_reg = (hl_reg & 0xff00) | l;}

        void set_z_flag(bool z) {af_reg = (af_reg & ~0x80) | (z << 7);}
        void set_n_flag(bool n) {af_reg = (af_reg & ~0x40) | (n << 6);}
        void set_h_flag(bool h) {af_reg = (af_reg & ~0x20) | (h << 5);}
        void set_c_flag(bool c) {af_reg = (af_reg & ~0x10) | (c << 4);}

    private:
        uint16_t pc_reg{0x0100};
        uint16_t sp_reg{0xfffe};
        uint16_t af_reg{0x01b0};
        uint16_t bc_reg{0x0013};
        uint16_t de_reg{0x00d8};
        uint16_t hl_reg{0x014d};
};

class CPU {
    public:
        uint8_t step();
        void set_mmu(MMU* mmu);

    private:
        MMU* mmu{};
        Registers regs{};

        bool ime{};
        uint8_t ime_pending{};

        bool stopped{};

        bool halted{};
        bool halt_bug_flag{};

        uint8_t pending_interrupts() const;
        void exec_interrupt();

        uint8_t next_u8();      /// Read 8 bits unsigned
        int8_t next_i8();       /// Read 8 bits signed
        uint16_t next_u16();    /// Read 16 bits unsigned

        uint16_t sp_offset(int8_t offset);  /// Offset SP
        uint8_t prefix(uint8_t op_cb);      /// Prefix switch
        void push(uint16_t val);            /// Push to stack
        uint16_t pop();                     /// Pop from stack
        uint8_t add(uint8_t val);           /// Add to A (1 byte)
        uint16_t add(uint16_t val);         /// Add to HL (2 bytes)
        uint8_t adc(uint8_t val);           /// Add with carry
        uint8_t inc(uint8_t val);           /// Increment (1 byte)
        uint16_t inc(uint16_t val);         /// Increment (2 bytes)
        uint8_t sub(uint8_t val);           /// Subtract
        uint8_t sbc(uint8_t val);           /// Subtract with carry
        uint8_t dec(uint8_t val);           /// Decrement (1 byte)
        uint16_t dec(uint16_t val);         /// Decrement (2 bytes)
        uint8_t bit_and(uint8_t val);       /// Bitwise AND
        uint8_t bit_or(uint8_t val);        /// Bitwise OR
        uint8_t bit_xor(uint8_t val);       /// Bitwise XOR
        void cp(uint8_t val);               /// Compare
        void jr(int8_t offset);             /// Jump relative
        void jp(uint16_t addr);             /// Jump
        void call(uint16_t addr);           /// Call
        void rst(uint8_t addr);             /// Reset
        void ret();                         /// Return
        uint8_t cpl();                      /// Complement accumulator
        uint8_t rlca();                     /// Rotate A left
        uint8_t rrca();                     /// Rotate A right
        void stop();                        /// Stop CPU and oscillator
        uint8_t rla();                      /// Rotate A left through carry
        uint8_t rra();                      /// Rotate A right through carry
        uint8_t daa();                      /// Decimal adjust A
        void scf();                         /// Set carry flag
        void ccf();                         /// Toggle carry flag
        void halt();                        /// Halt CPU until interrupt
        void reti();                        /// Return from interrupt
        void di();                          /// Disable interrupts
        void ei();                          /// Enable interrupts
        void unused(uint8_t op);            /// Log unused opcode

        void bit(uint8_t bit, uint8_t val);     /// Bit test
        uint8_t res(uint8_t bit, uint8_t val);  /// Bit reset
        uint8_t set(uint8_t bit, uint8_t val);  /// Bit set
        uint8_t rlc(uint8_t val);               /// Bit rotate left circular
        uint8_t rrc(uint8_t val);               /// Bit rotate right circular
        uint8_t rl(uint8_t val);                /// Bit rotate left through carry
        uint8_t rr(uint8_t val);                /// Bit rotate right through carry
        uint8_t sla(uint8_t val);               /// Bit shift left arithmetic
        uint8_t sra(uint8_t val);               /// Bit shift right arithmetic
        uint8_t srl(uint8_t val);               /// Bit shift right logical
        uint8_t swap(uint8_t val);              /// Nibble swap

        uint8_t op_0x00(); /// NOP
        uint8_t op_0x01(); /// LD BC, d16
        uint8_t op_0x02(); /// LD (BC), A
        uint8_t op_0x03(); /// INC BC
        uint8_t op_0x04(); /// INC B
        uint8_t op_0x05(); /// DEC B
        uint8_t op_0x06(); /// LD B, d8
        uint8_t op_0x07(); /// RLCA
        uint8_t op_0x08(); /// LD (a16), SP
        uint8_t op_0x09(); /// ADD HL, BC
        uint8_t op_0x0a(); /// LD A, (BC)
        uint8_t op_0x0b(); /// DEC BC
        uint8_t op_0x0c(); /// INC C
        uint8_t op_0x0d(); /// DEC C
        uint8_t op_0x0e(); /// LD C, d8
        uint8_t op_0x0f(); /// RRCA

        uint8_t op_0x10(); /// STOP 0
        uint8_t op_0x11(); /// LD DE, d16
        uint8_t op_0x12(); /// LD (DE), A
        uint8_t op_0x13(); /// INC DE
        uint8_t op_0x14(); /// INC D
        uint8_t op_0x15(); /// DEC D
        uint8_t op_0x16(); /// LD D, d8
        uint8_t op_0x17(); /// RLA
        uint8_t op_0x18(); /// JR r8
        uint8_t op_0x19(); /// ADD HL, DE
        uint8_t op_0x1a(); /// LD A, (DE)
        uint8_t op_0x1b(); /// DEC DE
        uint8_t op_0x1c(); /// INC E
        uint8_t op_0x1d(); /// DEC E
        uint8_t op_0x1e(); /// LD E, d8
        uint8_t op_0x1f(); /// RRA

        uint8_t op_0x20(); /// JR NZ, r8
        uint8_t op_0x21(); /// LD HL, d16
        uint8_t op_0x22(); /// LD (HL+), A
        uint8_t op_0x23(); /// INC HL
        uint8_t op_0x24(); /// INC H
        uint8_t op_0x25(); /// DEC H
        uint8_t op_0x26(); /// LD H, d8
        uint8_t op_0x27(); /// DAA
        uint8_t op_0x28(); /// JR Z, r8
        uint8_t op_0x29(); /// ADD HL, HL
        uint8_t op_0x2a(); /// LD A, (HL+)
        uint8_t op_0x2b(); /// DEC HL
        uint8_t op_0x2c(); /// INC L
        uint8_t op_0x2d(); /// DEC L
        uint8_t op_0x2e(); /// LD L, d8
        uint8_t op_0x2f(); /// CPL

        uint8_t op_0x30(); /// JR NC, r8
        uint8_t op_0x31(); /// LD SP, d16
        uint8_t op_0x32(); /// LD (HL-), A
        uint8_t op_0x33(); /// INC SP
        uint8_t op_0x34(); /// INC (HL)
        uint8_t op_0x35(); /// DEC (HL)
        uint8_t op_0x36(); /// LD (HL), d8
        uint8_t op_0x37(); /// SCF
        uint8_t op_0x38(); /// JR C, r8
        uint8_t op_0x39(); /// ADD HL, SP
        uint8_t op_0x3a(); /// LD A, (HL-)
        uint8_t op_0x3b(); /// DEC SP
        uint8_t op_0x3c(); /// INC A
        uint8_t op_0x3d(); /// DEC A
        uint8_t op_0x3e(); /// LD A, d8
        uint8_t op_0x3f(); /// CCF

        uint8_t op_0x40(); /// LD B, B
        uint8_t op_0x41(); /// LD B, C
        uint8_t op_0x42(); /// LD B, D
        uint8_t op_0x43(); /// LD B, E
        uint8_t op_0x44(); /// LD B, H
        uint8_t op_0x45(); /// LD B, L
        uint8_t op_0x46(); /// LD B, (HL)
        uint8_t op_0x47(); /// LD B, A
        uint8_t op_0x48(); /// LD C, B
        uint8_t op_0x49(); /// LD C, C
        uint8_t op_0x4a(); /// LD C, D
        uint8_t op_0x4b(); /// LD C, E
        uint8_t op_0x4c(); /// LD C, H
        uint8_t op_0x4d(); /// LD C, L
        uint8_t op_0x4e(); /// LD C, (HL)
        uint8_t op_0x4f(); /// LD C, A

        uint8_t op_0x50(); /// LD D, B
        uint8_t op_0x51(); /// LD D, C
        uint8_t op_0x52(); /// LD D, D
        uint8_t op_0x53(); /// LD D, E
        uint8_t op_0x54(); /// LD D, H
        uint8_t op_0x55(); /// LD D, L
        uint8_t op_0x56(); /// LD D, (HL)
        uint8_t op_0x57(); /// LD D, A
        uint8_t op_0x58(); /// LD E, B
        uint8_t op_0x59(); /// LD E, C
        uint8_t op_0x5a(); /// LD E, D
        uint8_t op_0x5b(); /// LD E, E
        uint8_t op_0x5c(); /// LD E, H
        uint8_t op_0x5d(); /// LD E, L
        uint8_t op_0x5e(); /// LD E, (HL)
        uint8_t op_0x5f(); /// LD E, A

        uint8_t op_0x60(); /// LD H, B
        uint8_t op_0x61(); /// LD H, C
        uint8_t op_0x62(); /// LD H, D
        uint8_t op_0x63(); /// LD H, E
        uint8_t op_0x64(); /// LD H, H
        uint8_t op_0x65(); /// LD H, L
        uint8_t op_0x66(); /// LD H, (HL)
        uint8_t op_0x67(); /// LD H, A
        uint8_t op_0x68(); /// LD L, B
        uint8_t op_0x69(); /// LD L, C
        uint8_t op_0x6a(); /// LD L, D
        uint8_t op_0x6b(); /// LD L, E
        uint8_t op_0x6c(); /// LD L, H
        uint8_t op_0x6d(); /// LD L, L
        uint8_t op_0x6e(); /// LD L, (HL)
        uint8_t op_0x6f(); /// LD L, A

        uint8_t op_0x70(); /// LD (HL), B
        uint8_t op_0x71(); /// LD (HL), C
        uint8_t op_0x72(); /// LD (HL), D
        uint8_t op_0x73(); /// LD (HL), E
        uint8_t op_0x74(); /// LD (HL), H
        uint8_t op_0x75(); /// LD (HL), L
        uint8_t op_0x76(); /// HALT
        uint8_t op_0x77(); /// LD (HL), A
        uint8_t op_0x78(); /// LD A, B
        uint8_t op_0x79(); /// LD A, C
        uint8_t op_0x7a(); /// LD A, D
        uint8_t op_0x7b(); /// LD A, E
        uint8_t op_0x7c(); /// LD A, H
        uint8_t op_0x7d(); /// LD A, L
        uint8_t op_0x7e(); /// LD A, (HL)
        uint8_t op_0x7f(); /// LD A, A

        uint8_t op_0x80(); /// ADD A, B
        uint8_t op_0x81(); /// ADD A, C
        uint8_t op_0x82(); /// ADD A, D
        uint8_t op_0x83(); /// ADD A, E
        uint8_t op_0x84(); /// ADD A, H
        uint8_t op_0x85(); /// ADD A, L
        uint8_t op_0x86(); /// ADD A, (HL)
        uint8_t op_0x87(); /// ADD A, A
        uint8_t op_0x88(); /// ADC A, B
        uint8_t op_0x89(); /// ADC A, C
        uint8_t op_0x8a(); /// ADC A, D
        uint8_t op_0x8b(); /// ADC A, E
        uint8_t op_0x8c(); /// ADC A, H
        uint8_t op_0x8d(); /// ADC A, L
        uint8_t op_0x8e(); /// ADC A, (HL)
        uint8_t op_0x8f(); /// ADC A, A

        uint8_t op_0x90(); /// SUB B
        uint8_t op_0x91(); /// SUB C
        uint8_t op_0x92(); /// SUB D
        uint8_t op_0x93(); /// SUB E
        uint8_t op_0x94(); /// SUB H
        uint8_t op_0x95(); /// SUB L
        uint8_t op_0x96(); /// SUB (HL)
        uint8_t op_0x97(); /// SUB A
        uint8_t op_0x98(); /// SBC A, B
        uint8_t op_0x99(); /// SBC A, C
        uint8_t op_0x9a(); /// SBC A, D
        uint8_t op_0x9b(); /// SBC A, E
        uint8_t op_0x9c(); /// SBC A, H
        uint8_t op_0x9d(); /// SBC A, L
        uint8_t op_0x9e(); /// SBC A, (HL)
        uint8_t op_0x9f(); /// SBC A, A

        uint8_t op_0xa0(); /// AND B
        uint8_t op_0xa1(); /// AND C
        uint8_t op_0xa2(); /// AND D
        uint8_t op_0xa3(); /// AND E
        uint8_t op_0xa4(); /// AND H
        uint8_t op_0xa5(); /// AND L
        uint8_t op_0xa6(); /// AND (HL)
        uint8_t op_0xa7(); /// AND A
        uint8_t op_0xa8(); /// XOR B
        uint8_t op_0xa9(); /// XOR C
        uint8_t op_0xaa(); /// XOR D
        uint8_t op_0xab(); /// XOR E
        uint8_t op_0xac(); /// XOR H
        uint8_t op_0xad(); /// XOR L
        uint8_t op_0xae(); /// XOR (HL)
        uint8_t op_0xaf(); /// XOR A

        uint8_t op_0xb0(); /// OR B
        uint8_t op_0xb1(); /// OR C
        uint8_t op_0xb2(); /// OR D
        uint8_t op_0xb3(); /// OR E
        uint8_t op_0xb4(); /// OR H
        uint8_t op_0xb5(); /// OR L
        uint8_t op_0xb6(); /// OR (HL)
        uint8_t op_0xb7(); /// OR A
        uint8_t op_0xb8(); /// CP B
        uint8_t op_0xb9(); /// CP C
        uint8_t op_0xba(); /// CP D
        uint8_t op_0xbb(); /// CP E
        uint8_t op_0xbc(); /// CP H
        uint8_t op_0xbd(); /// CP L
        uint8_t op_0xbe(); /// CP (HL)
        uint8_t op_0xbf(); /// CP A

        uint8_t op_0xc0(); /// RET NZ
        uint8_t op_0xc1(); /// POP BC
        uint8_t op_0xc2(); /// JP NZ, a16
        uint8_t op_0xc3(); /// JP a16
        uint8_t op_0xc4(); /// CALL NZ, a16
        uint8_t op_0xc5(); /// PUSH BC
        uint8_t op_0xc6(); /// ADD A, d8
        uint8_t op_0xc7(); /// RST 00H
        uint8_t op_0xc8(); /// RET Z
        uint8_t op_0xc9(); /// RET
        uint8_t op_0xca(); /// JP Z, a16
        uint8_t op_0xcc(); /// CALL Z, a16
        uint8_t op_0xcd(); /// CALL a16
        uint8_t op_0xce(); /// ADC A, d8
        uint8_t op_0xcf(); /// RST 08H

        uint8_t op_0xd0(); /// RET NC
        uint8_t op_0xd1(); /// POP DE
        uint8_t op_0xd2(); /// JP NC, a16
        uint8_t op_0xd3(); /// Unused
        uint8_t op_0xd4(); /// CALL NC, a16
        uint8_t op_0xd5(); /// PUSH DE
        uint8_t op_0xd6(); /// SUB d8
        uint8_t op_0xd7(); /// RST 10H
        uint8_t op_0xd8(); /// RET C
        uint8_t op_0xd9(); /// RETI
        uint8_t op_0xda(); /// JP C, a16
        uint8_t op_0xdb(); /// Unused
        uint8_t op_0xdc(); /// CALL C, a16
        uint8_t op_0xdd(); /// Unused
        uint8_t op_0xde(); /// SBC A, d8
        uint8_t op_0xdf(); /// RST 18H

        uint8_t op_0xe0(); /// LDH (a8), A
        uint8_t op_0xe1(); /// POP HL
        uint8_t op_0xe2(); /// LD (C), A
        uint8_t op_0xe3(); /// Unused
        uint8_t op_0xe4(); /// Unused
        uint8_t op_0xe5(); /// PUSH HL
        uint8_t op_0xe6(); /// AND d8
        uint8_t op_0xe7(); /// RST 20H
        uint8_t op_0xe8(); /// ADD SP, r8
        uint8_t op_0xe9(); /// JP (HL)
        uint8_t op_0xea(); /// LD (a16), A
        uint8_t op_0xeb(); /// Unused
        uint8_t op_0xec(); /// Unused
        uint8_t op_0xed(); /// Unused
        uint8_t op_0xee(); /// XOR d8
        uint8_t op_0xef(); /// RST 28H

        uint8_t op_0xf0(); /// LDH A, (a8)
        uint8_t op_0xf1(); /// POP AF
        uint8_t op_0xf2(); /// LD A, (C)
        uint8_t op_0xf3(); /// DI
        uint8_t op_0xf4(); /// Unused
        uint8_t op_0xf5(); /// PUSH AF
        uint8_t op_0xf6(); /// OR d8
        uint8_t op_0xf7(); /// RST 30H
        uint8_t op_0xf8(); /// LD HL, SP+r8
        uint8_t op_0xf9(); /// LD SP, HL
        uint8_t op_0xfa(); /// LD A, (a16)
        uint8_t op_0xfb(); /// EI
        uint8_t op_0xfc(); /// Unused
        uint8_t op_0xfd(); /// Unused
        uint8_t op_0xfe(); /// CP d8
        uint8_t op_0xff(); /// RST 38H

        uint8_t op_cb_0x00(); /// RLC B
        uint8_t op_cb_0x01(); /// RLC C
        uint8_t op_cb_0x02(); /// RLC D
        uint8_t op_cb_0x03(); /// RLC E
        uint8_t op_cb_0x04(); /// RLC H
        uint8_t op_cb_0x05(); /// RLC L
        uint8_t op_cb_0x06(); /// RLC (HL)
        uint8_t op_cb_0x07(); /// RLC A
        uint8_t op_cb_0x08(); /// RRC B
        uint8_t op_cb_0x09(); /// RRC C
        uint8_t op_cb_0x0a(); /// RRC D
        uint8_t op_cb_0x0b(); /// RRC E
        uint8_t op_cb_0x0c(); /// RRC H
        uint8_t op_cb_0x0d(); /// RRC L
        uint8_t op_cb_0x0e(); /// RRC (HL)
        uint8_t op_cb_0x0f(); /// RRC A

        uint8_t op_cb_0x10(); /// RL B
        uint8_t op_cb_0x11(); /// RL C
        uint8_t op_cb_0x12(); /// RL D
        uint8_t op_cb_0x13(); /// RL E
        uint8_t op_cb_0x14(); /// RL H
        uint8_t op_cb_0x15(); /// RL L
        uint8_t op_cb_0x16(); /// RL (HL)
        uint8_t op_cb_0x17(); /// RL A
        uint8_t op_cb_0x18(); /// RR B
        uint8_t op_cb_0x19(); /// RR C
        uint8_t op_cb_0x1a(); /// RR D
        uint8_t op_cb_0x1b(); /// RR E
        uint8_t op_cb_0x1c(); /// RR H
        uint8_t op_cb_0x1d(); /// RR L
        uint8_t op_cb_0x1e(); /// RR (HL)
        uint8_t op_cb_0x1f(); /// RR A

        uint8_t op_cb_0x20(); /// SLA B
        uint8_t op_cb_0x21(); /// SLA C
        uint8_t op_cb_0x22(); /// SLA D
        uint8_t op_cb_0x23(); /// SLA E
        uint8_t op_cb_0x24(); /// SLA H
        uint8_t op_cb_0x25(); /// SLA L
        uint8_t op_cb_0x26(); /// SLA (HL)
        uint8_t op_cb_0x27(); /// SLA A
        uint8_t op_cb_0x28(); /// SRA B
        uint8_t op_cb_0x29(); /// SRA C
        uint8_t op_cb_0x2a(); /// SRA D
        uint8_t op_cb_0x2b(); /// SRA E
        uint8_t op_cb_0x2c(); /// SRA H
        uint8_t op_cb_0x2d(); /// SRA L
        uint8_t op_cb_0x2e(); /// SRA (HL)
        uint8_t op_cb_0x2f(); /// SRA A

        uint8_t op_cb_0x30(); /// SWAP B
        uint8_t op_cb_0x31(); /// SWAP C
        uint8_t op_cb_0x32(); /// SWAP D
        uint8_t op_cb_0x33(); /// SWAP E
        uint8_t op_cb_0x34(); /// SWAP H
        uint8_t op_cb_0x35(); /// SWAP L
        uint8_t op_cb_0x36(); /// SWAP (HL)
        uint8_t op_cb_0x37(); /// SWAP A
        uint8_t op_cb_0x38(); /// SRL B
        uint8_t op_cb_0x39(); /// SRL C
        uint8_t op_cb_0x3a(); /// SRL D
        uint8_t op_cb_0x3b(); /// SRL E
        uint8_t op_cb_0x3c(); /// SRL H
        uint8_t op_cb_0x3d(); /// SRL L
        uint8_t op_cb_0x3e(); /// SRL (HL)
        uint8_t op_cb_0x3f(); /// SRL A

        uint8_t op_cb_0x40(); /// BIT 0, B
        uint8_t op_cb_0x41(); /// BIT 0, C
        uint8_t op_cb_0x42(); /// BIT 0, D
        uint8_t op_cb_0x43(); /// BIT 0, E
        uint8_t op_cb_0x44(); /// BIT 0, H
        uint8_t op_cb_0x45(); /// BIT 0, L
        uint8_t op_cb_0x46(); /// BIT 0, (HL)
        uint8_t op_cb_0x47(); /// BIT 0, A
        uint8_t op_cb_0x48(); /// BIT 1, B
        uint8_t op_cb_0x49(); /// BIT 1, C
        uint8_t op_cb_0x4a(); /// BIT 1, D
        uint8_t op_cb_0x4b(); /// BIT 1, E
        uint8_t op_cb_0x4c(); /// BIT 1, H
        uint8_t op_cb_0x4d(); /// BIT 1, L
        uint8_t op_cb_0x4e(); /// BIT 1, (HL)
        uint8_t op_cb_0x4f(); /// BIT 1, A

        uint8_t op_cb_0x50(); /// BIT 2, B
        uint8_t op_cb_0x51(); /// BIT 2, C
        uint8_t op_cb_0x52(); /// BIT 2, D
        uint8_t op_cb_0x53(); /// BIT 2, E
        uint8_t op_cb_0x54(); /// BIT 2, H
        uint8_t op_cb_0x55(); /// BIT 2, L
        uint8_t op_cb_0x56(); /// BIT 2, (HL)
        uint8_t op_cb_0x57(); /// BIT 2, A
        uint8_t op_cb_0x58(); /// BIT 3, B
        uint8_t op_cb_0x59(); /// BIT 3, C
        uint8_t op_cb_0x5a(); /// BIT 3, D
        uint8_t op_cb_0x5b(); /// BIT 3, E
        uint8_t op_cb_0x5c(); /// BIT 3, H
        uint8_t op_cb_0x5d(); /// BIT 3, L
        uint8_t op_cb_0x5e(); /// BIT 3, (HL)
        uint8_t op_cb_0x5f(); /// BIT 3, A

        uint8_t op_cb_0x60(); /// BIT 4, B
        uint8_t op_cb_0x61(); /// BIT 4, C
        uint8_t op_cb_0x62(); /// BIT 4, D
        uint8_t op_cb_0x63(); /// BIT 4, E
        uint8_t op_cb_0x64(); /// BIT 4, H
        uint8_t op_cb_0x65(); /// BIT 4, L
        uint8_t op_cb_0x66(); /// BIT 4, (HL)
        uint8_t op_cb_0x67(); /// BIT 4, A
        uint8_t op_cb_0x68(); /// BIT 5, B
        uint8_t op_cb_0x69(); /// BIT 5, C
        uint8_t op_cb_0x6a(); /// BIT 5, D
        uint8_t op_cb_0x6b(); /// BIT 5, E
        uint8_t op_cb_0x6c(); /// BIT 5, H
        uint8_t op_cb_0x6d(); /// BIT 5, L
        uint8_t op_cb_0x6e(); /// BIT 5, (HL)
        uint8_t op_cb_0x6f(); /// BIT 5, A

        uint8_t op_cb_0x70(); /// BIT 6, B
        uint8_t op_cb_0x71(); /// BIT 6, C
        uint8_t op_cb_0x72(); /// BIT 6, D
        uint8_t op_cb_0x73(); /// BIT 6, E
        uint8_t op_cb_0x74(); /// BIT 6, H
        uint8_t op_cb_0x75(); /// BIT 6, L
        uint8_t op_cb_0x76(); /// BIT 6, (HL)
        uint8_t op_cb_0x77(); /// BIT 6, A
        uint8_t op_cb_0x78(); /// BIT 7, B
        uint8_t op_cb_0x79(); /// BIT 7, C
        uint8_t op_cb_0x7a(); /// BIT 7, D
        uint8_t op_cb_0x7b(); /// BIT 7, E
        uint8_t op_cb_0x7c(); /// BIT 7, H
        uint8_t op_cb_0x7d(); /// BIT 7, L
        uint8_t op_cb_0x7e(); /// BIT 7, (HL)
        uint8_t op_cb_0x7f(); /// BIT 7, A

        uint8_t op_cb_0x80(); /// RES 0, B
        uint8_t op_cb_0x81(); /// RES 0, C
        uint8_t op_cb_0x82(); /// RES 0, D
        uint8_t op_cb_0x83(); /// RES 0, E
        uint8_t op_cb_0x84(); /// RES 0, H
        uint8_t op_cb_0x85(); /// RES 0, L
        uint8_t op_cb_0x86(); /// RES 0, (HL)
        uint8_t op_cb_0x87(); /// RES 0, A
        uint8_t op_cb_0x88(); /// RES 1, B
        uint8_t op_cb_0x89(); /// RES 1, C
        uint8_t op_cb_0x8a(); /// RES 1, D
        uint8_t op_cb_0x8b(); /// RES 1, E
        uint8_t op_cb_0x8c(); /// RES 1, H
        uint8_t op_cb_0x8d(); /// RES 1, L
        uint8_t op_cb_0x8e(); /// RES 1, (HL)
        uint8_t op_cb_0x8f(); /// RES 1, A

        uint8_t op_cb_0x90(); /// RES 2, B
        uint8_t op_cb_0x91(); /// RES 2, C
        uint8_t op_cb_0x92(); /// RES 2, D
        uint8_t op_cb_0x93(); /// RES 2, E
        uint8_t op_cb_0x94(); /// RES 2, H
        uint8_t op_cb_0x95(); /// RES 2, L
        uint8_t op_cb_0x96(); /// RES 2, (HL)
        uint8_t op_cb_0x97(); /// RES 2, A
        uint8_t op_cb_0x98(); /// RES 3, B
        uint8_t op_cb_0x99(); /// RES 3, C
        uint8_t op_cb_0x9a(); /// RES 3, D
        uint8_t op_cb_0x9b(); /// RES 3, E
        uint8_t op_cb_0x9c(); /// RES 3, H
        uint8_t op_cb_0x9d(); /// RES 3, L
        uint8_t op_cb_0x9e(); /// RES 3, (HL)
        uint8_t op_cb_0x9f(); /// RES 3, A

        uint8_t op_cb_0xa0(); /// RES 4, B
        uint8_t op_cb_0xa1(); /// RES 4, C
        uint8_t op_cb_0xa2(); /// RES 4, D
        uint8_t op_cb_0xa3(); /// RES 4, E
        uint8_t op_cb_0xa4(); /// RES 4, H
        uint8_t op_cb_0xa5(); /// RES 4, L
        uint8_t op_cb_0xa6(); /// RES 4, (HL)
        uint8_t op_cb_0xa7(); /// RES 4, A
        uint8_t op_cb_0xa8(); /// RES 5, B
        uint8_t op_cb_0xa9(); /// RES 5, C
        uint8_t op_cb_0xaa(); /// RES 5, D
        uint8_t op_cb_0xab(); /// RES 5, E
        uint8_t op_cb_0xac(); /// RES 5, H
        uint8_t op_cb_0xad(); /// RES 5, L
        uint8_t op_cb_0xae(); /// RES 5, (HL)
        uint8_t op_cb_0xaf(); /// RES 5, A

        uint8_t op_cb_0xb0(); /// RES 6, B
        uint8_t op_cb_0xb1(); /// RES 6, C
        uint8_t op_cb_0xb2(); /// RES 6, D
        uint8_t op_cb_0xb3(); /// RES 6, E
        uint8_t op_cb_0xb4(); /// RES 6, H
        uint8_t op_cb_0xb5(); /// RES 6, L
        uint8_t op_cb_0xb6(); /// RES 6, (HL)
        uint8_t op_cb_0xb7(); /// RES 6, A
        uint8_t op_cb_0xb8(); /// RES 7, B
        uint8_t op_cb_0xb9(); /// RES 7, C
        uint8_t op_cb_0xba(); /// RES 7, D
        uint8_t op_cb_0xbb(); /// RES 7, E
        uint8_t op_cb_0xbc(); /// RES 7, H
        uint8_t op_cb_0xbd(); /// RES 7, L
        uint8_t op_cb_0xbe(); /// RES 7, (HL)
        uint8_t op_cb_0xbf(); /// RES 7, A

        uint8_t op_cb_0xc0(); /// SET 0, B
        uint8_t op_cb_0xc1(); /// SET 0, C
        uint8_t op_cb_0xc2(); /// SET 0, D
        uint8_t op_cb_0xc3(); /// SET 0, E
        uint8_t op_cb_0xc4(); /// SET 0, H
        uint8_t op_cb_0xc5(); /// SET 0, L
        uint8_t op_cb_0xc6(); /// SET 0, (HL)
        uint8_t op_cb_0xc7(); /// SET 0, A
        uint8_t op_cb_0xc8(); /// SET 1, B
        uint8_t op_cb_0xc9(); /// SET 1, C
        uint8_t op_cb_0xca(); /// SET 1, D
        uint8_t op_cb_0xcb(); /// SET 1, E
        uint8_t op_cb_0xcc(); /// SET 1, H
        uint8_t op_cb_0xcd(); /// SET 1, L
        uint8_t op_cb_0xce(); /// SET 1, (HL)
        uint8_t op_cb_0xcf(); /// SET 1, A

        uint8_t op_cb_0xd0(); /// SET 2, B
        uint8_t op_cb_0xd1(); /// SET 2, C
        uint8_t op_cb_0xd2(); /// SET 2, D
        uint8_t op_cb_0xd3(); /// SET 2, E
        uint8_t op_cb_0xd4(); /// SET 2, H
        uint8_t op_cb_0xd5(); /// SET 2, L
        uint8_t op_cb_0xd6(); /// SET 2, (HL)
        uint8_t op_cb_0xd7(); /// SET 2, A
        uint8_t op_cb_0xd8(); /// SET 3, B
        uint8_t op_cb_0xd9(); /// SET 3, C
        uint8_t op_cb_0xda(); /// SET 3, D
        uint8_t op_cb_0xdb(); /// SET 3, E
        uint8_t op_cb_0xdc(); /// SET 3, H
        uint8_t op_cb_0xdd(); /// SET 3, L
        uint8_t op_cb_0xde(); /// SET 3, (HL)
        uint8_t op_cb_0xdf(); /// SET 3, A

        uint8_t op_cb_0xe0(); /// SET 4, B
        uint8_t op_cb_0xe1(); /// SET 4, C
        uint8_t op_cb_0xe2(); /// SET 4, D
        uint8_t op_cb_0xe3(); /// SET 4, E
        uint8_t op_cb_0xe4(); /// SET 4, H
        uint8_t op_cb_0xe5(); /// SET 4, L
        uint8_t op_cb_0xe6(); /// SET 4, (HL)
        uint8_t op_cb_0xe7(); /// SET 4, A
        uint8_t op_cb_0xe8(); /// SET 5, B
        uint8_t op_cb_0xe9(); /// SET 5, C
        uint8_t op_cb_0xea(); /// SET 5, D
        uint8_t op_cb_0xeb(); /// SET 5, E
        uint8_t op_cb_0xec(); /// SET 5, H
        uint8_t op_cb_0xed(); /// SET 5, L
        uint8_t op_cb_0xee(); /// SET 5, (HL)
        uint8_t op_cb_0xef(); /// SET 5, A

        uint8_t op_cb_0xf0(); /// SET 6, B
        uint8_t op_cb_0xf1(); /// SET 6, C
        uint8_t op_cb_0xf2(); /// SET 6, D
        uint8_t op_cb_0xf3(); /// SET 6, E
        uint8_t op_cb_0xf4(); /// SET 6, H
        uint8_t op_cb_0xf5(); /// SET 6, L
        uint8_t op_cb_0xf6(); /// SET 6, (HL)
        uint8_t op_cb_0xf7(); /// SET 6, A
        uint8_t op_cb_0xf8(); /// SET 7, B
        uint8_t op_cb_0xf9(); /// SET 7, C
        uint8_t op_cb_0xfa(); /// SET 7, D
        uint8_t op_cb_0xfb(); /// SET 7, E
        uint8_t op_cb_0xfc(); /// SET 7, H
        uint8_t op_cb_0xfd(); /// SET 7, L
        uint8_t op_cb_0xfe(); /// SET 7, (HL)
        uint8_t op_cb_0xff(); /// SET 7, A
};