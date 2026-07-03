#pragma once

#include "./registers.hpp"

class CPU {
    private:
        Registers regs;

        bool ime{false};
        bool stopped{false};
        bool halted{false};

        void ld(uint8_t& dest, uint8_t src);
        void add(uint8_t& dest, uint8_t src);
        void adc(uint8_t& dest, uint8_t src);
        void sub(uint8_t& dest, uint8_t src);
        void sbc(uint8_t& dest, uint8_t src);
        void inc(uint8_t& dest);
        void dec(uint8_t& dest);
        void and_(uint8_t& dest, uint8_t src);
        void or_(uint8_t& dest, uint8_t src);
        void xor_(uint8_t& dest, uint8_t src);
        void cp(uint8_t& dest, uint8_t src);
        void jp(uint8_t& dest);
        void jr(uint8_t& dest);
        void call(uint8_t& dest);
        void ret(uint8_t& dest);
        void bit(uint8_t a, uint8_t b);
        void set(uint8_t a, uint8_t& dest);
        void res(uint8_t a, uint8_t& dest);
        void rlc(uint8_t& dest);
        void rrc(uint8_t& dest);
        void rl(uint8_t& dest);
        void rr(uint8_t& dest);
        void push(uint16_t& val);
        uint16_t pop();

        // Operands
        uint8_t d8(); uint16_t d16();
        uint8_t a8(); uint16_t a16();
        uint8_t r8();

        // Opcode handlers
        uint8_t op_00(); uint8_t op_01(); uint8_t op_02(); uint8_t op_03(); uint8_t op_04(); uint8_t op_05(); uint8_t op_06(); uint8_t op_07(); uint8_t op_08(); uint8_t op_09(); uint8_t op_0a(); uint8_t op_0b(); uint8_t op_0c(); uint8_t op_0d(); uint8_t op_0e(); uint8_t op_0f();
        uint8_t op_10(); uint8_t op_11(); uint8_t op_12(); uint8_t op_13(); uint8_t op_14(); uint8_t op_15(); uint8_t op_16(); uint8_t op_17(); uint8_t op_18(); uint8_t op_19(); uint8_t op_1a(); uint8_t op_1b(); uint8_t op_1c(); uint8_t op_1d(); uint8_t op_1e(); uint8_t op_1f();
        uint8_t op_20(); uint8_t op_21(); uint8_t op_22(); uint8_t op_23(); uint8_t op_24(); uint8_t op_25(); uint8_t op_26(); uint8_t op_27(); uint8_t op_28(); uint8_t op_29(); uint8_t op_2a(); uint8_t op_2b(); uint8_t op_2c(); uint8_t op_2d(); uint8_t op_2e(); uint8_t op_2f();
        uint8_t op_30(); uint8_t op_31(); uint8_t op_32(); uint8_t op_33(); uint8_t op_34(); uint8_t op_35(); uint8_t op_36(); uint8_t op_37(); uint8_t op_38(); uint8_t op_39(); uint8_t op_3a(); uint8_t op_3b(); uint8_t op_3c(); uint8_t op_3d(); uint8_t op_3e(); uint8_t op_3f();
        uint8_t op_40(); uint8_t op_41(); uint8_t op_42(); uint8_t op_43(); uint8_t op_44(); uint8_t op_45(); uint8_t op_46(); uint8_t op_47(); uint8_t op_48(); uint8_t op_49(); uint8_t op_4a(); uint8_t op_4b(); uint8_t op_4c(); uint8_t op_4d(); uint8_t op_4e(); uint8_t op_4f();
        uint8_t op_50(); uint8_t op_51(); uint8_t op_52(); uint8_t op_53(); uint8_t op_54(); uint8_t op_55(); uint8_t op_56(); uint8_t op_57(); uint8_t op_58(); uint8_t op_59(); uint8_t op_5a(); uint8_t op_5b(); uint8_t op_5c(); uint8_t op_5d(); uint8_t op_5e(); uint8_t op_5f();
        uint8_t op_60(); uint8_t op_61(); uint8_t op_62(); uint8_t op_63(); uint8_t op_64(); uint8_t op_65(); uint8_t op_66(); uint8_t op_67(); uint8_t op_68(); uint8_t op_69(); uint8_t op_6a(); uint8_t op_6b(); uint8_t op_6c(); uint8_t op_6d(); uint8_t op_6e(); uint8_t op_6f();
        uint8_t op_70(); uint8_t op_71(); uint8_t op_72(); uint8_t op_73(); uint8_t op_74(); uint8_t op_75(); uint8_t op_76(); uint8_t op_77(); uint8_t op_78(); uint8_t op_79(); uint8_t op_7a(); uint8_t op_7b(); uint8_t op_7c(); uint8_t op_7d(); uint8_t op_7e(); uint8_t op_7f();
        uint8_t op_80(); uint8_t op_81(); uint8_t op_82(); uint8_t op_83(); uint8_t op_84(); uint8_t op_85(); uint8_t op_86(); uint8_t op_87(); uint8_t op_88(); uint8_t op_89(); uint8_t op_8a(); uint8_t op_8b(); uint8_t op_8c(); uint8_t op_8d(); uint8_t op_8e(); uint8_t op_8f();
        uint8_t op_90(); uint8_t op_91(); uint8_t op_92(); uint8_t op_93(); uint8_t op_94(); uint8_t op_95(); uint8_t op_96(); uint8_t op_97(); uint8_t op_98(); uint8_t op_99(); uint8_t op_9a(); uint8_t op_9b(); uint8_t op_9c(); uint8_t op_9d(); uint8_t op_9e(); uint8_t op_9f();
        uint8_t op_a0(); uint8_t op_a1(); uint8_t op_a2(); uint8_t op_a3(); uint8_t op_a4(); uint8_t op_a5(); uint8_t op_a6(); uint8_t op_a7(); uint8_t op_a8(); uint8_t op_a9(); uint8_t op_aa(); uint8_t op_ab(); uint8_t op_ac(); uint8_t op_ad(); uint8_t op_ae(); uint8_t op_af();
        uint8_t op_b0(); uint8_t op_b1(); uint8_t op_b2(); uint8_t op_b3(); uint8_t op_b4(); uint8_t op_b5(); uint8_t op_b6(); uint8_t op_b7(); uint8_t op_b8(); uint8_t op_b9(); uint8_t op_ba(); uint8_t op_bb(); uint8_t op_bc(); uint8_t op_bd(); uint8_t op_be(); uint8_t op_bf();
        uint8_t op_c0(); uint8_t op_c1(); uint8_t op_c2(); uint8_t op_c3(); uint8_t op_c4(); uint8_t op_c5(); uint8_t op_c6(); uint8_t op_c7(); uint8_t op_c8(); uint8_t op_c9(); uint8_t op_ca(); uint8_t op_cb(); uint8_t op_cc(); uint8_t op_cd(); uint8_t op_ce(); uint8_t op_cf();
        uint8_t op_d0(); uint8_t op_d1(); uint8_t op_d2(); uint8_t op_d3(); uint8_t op_d4(); uint8_t op_d5(); uint8_t op_d6(); uint8_t op_d7(); uint8_t op_d8(); uint8_t op_d9(); uint8_t op_da(); uint8_t op_db(); uint8_t op_dc(); uint8_t op_dd(); uint8_t op_de(); uint8_t op_df();
        uint8_t op_e0(); uint8_t op_e1(); uint8_t op_e2(); uint8_t op_e3(); uint8_t op_e4(); uint8_t op_e5(); uint8_t op_e6(); uint8_t op_e7(); uint8_t op_e8(); uint8_t op_e9(); uint8_t op_ea(); uint8_t op_eb(); uint8_t op_ec(); uint8_t op_ed(); uint8_t op_ee(); uint8_t op_ef();
        uint8_t op_f0(); uint8_t op_f1(); uint8_t op_f2(); uint8_t op_f3(); uint8_t op_f4(); uint8_t op_f5(); uint8_t op_f6(); uint8_t op_f7(); uint8_t op_f8(); uint8_t op_f9(); uint8_t op_fa(); uint8_t op_fb(); uint8_t op_fc(); uint8_t op_fd(); uint8_t op_fe(); uint8_t op_ff();

    public:

};