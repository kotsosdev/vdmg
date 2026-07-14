#include "../../include/cpu.hpp"

#include <print>
#include <cstdio>

using std::println;

uint8_t CPU::step() {
    uint8_t op = next_u8();

    switch (op) {
        case 0x00: return op_0x00();
        case 0x01: return op_0x01();
        case 0x02: return op_0x02();
        case 0x03: return op_0x03();
        case 0x04: return op_0x04();
        case 0x05: return op_0x05();
        case 0x06: return op_0x06();
        case 0x07: return op_0x07();
        case 0x08: return op_0x08();
        case 0x09: return op_0x09();
        case 0x0a: return op_0x0a();
        case 0x0b: return op_0x0b();
        case 0x0c: return op_0x0c();
        case 0x0d: return op_0x0d();
        case 0x0e: return op_0x0e();
        case 0x0f: return op_0x0f();

        case 0x10: return op_0x10();
        case 0x11: return op_0x11();
        case 0x12: return op_0x12();
        case 0x13: return op_0x13();
        case 0x14: return op_0x14();
        case 0x15: return op_0x15();
        case 0x16: return op_0x16();
        case 0x17: return op_0x17();
        case 0x18: return op_0x18();
        case 0x19: return op_0x19();
        case 0x1a: return op_0x1a();
        case 0x1b: return op_0x1b();
        case 0x1c: return op_0x1c();
        case 0x1d: return op_0x1d();
        case 0x1e: return op_0x1e();
        case 0x1f: return op_0x1f();

        case 0x20: return op_0x20();
        case 0x21: return op_0x21();
        case 0x22: return op_0x22();
        case 0x23: return op_0x23();
        case 0x24: return op_0x24();
        case 0x25: return op_0x25();
        case 0x26: return op_0x26();
        case 0x27: return op_0x27();
        case 0x28: return op_0x28();
        case 0x29: return op_0x29();
        case 0x2a: return op_0x2a();
        case 0x2b: return op_0x2b();
        case 0x2c: return op_0x2c();
        case 0x2d: return op_0x2d();
        case 0x2e: return op_0x2e();
        case 0x2f: return op_0x2f();

        case 0x30: return op_0x30();
        case 0x31: return op_0x31();
        case 0x32: return op_0x32();
        case 0x33: return op_0x33();
        case 0x34: return op_0x34();
        case 0x35: return op_0x35();
        case 0x36: return op_0x36();
        case 0x37: return op_0x37();
        case 0x38: return op_0x38();
        case 0x39: return op_0x39();
        case 0x3a: return op_0x3a();
        case 0x3b: return op_0x3b();
        case 0x3c: return op_0x3c();
        case 0x3d: return op_0x3d();
        case 0x3e: return op_0x3e();
        case 0x3f: return op_0x3f();

        case 0x40: return op_0x40();
        case 0x41: return op_0x41();
        case 0x42: return op_0x42();
        case 0x43: return op_0x43();
        case 0x44: return op_0x44();
        case 0x45: return op_0x45();
        case 0x46: return op_0x46();
        case 0x47: return op_0x47();
        case 0x48: return op_0x48();
        case 0x49: return op_0x49();
        case 0x4a: return op_0x4a();
        case 0x4b: return op_0x4b();
        case 0x4c: return op_0x4c();
        case 0x4d: return op_0x4d();
        case 0x4e: return op_0x4e();
        case 0x4f: return op_0x4f();

        case 0x50: return op_0x50();
        case 0x51: return op_0x51();
        case 0x52: return op_0x52();
        case 0x53: return op_0x53();
        case 0x54: return op_0x54();
        case 0x55: return op_0x55();
        case 0x56: return op_0x56();
        case 0x57: return op_0x57();
        case 0x58: return op_0x58();
        case 0x59: return op_0x59();
        case 0x5a: return op_0x5a();
        case 0x5b: return op_0x5b();
        case 0x5c: return op_0x5c();
        case 0x5d: return op_0x5d();
        case 0x5e: return op_0x5e();
        case 0x5f: return op_0x5f();

        case 0x60: return op_0x60();
        case 0x61: return op_0x61();
        case 0x62: return op_0x62();
        case 0x63: return op_0x63();
        case 0x64: return op_0x64();
        case 0x65: return op_0x65();
        case 0x66: return op_0x66();
        case 0x67: return op_0x67();
        case 0x68: return op_0x68();
        case 0x69: return op_0x69();
        case 0x6a: return op_0x6a();
        case 0x6b: return op_0x6b();
        case 0x6c: return op_0x6c();
        case 0x6d: return op_0x6d();
        case 0x6e: return op_0x6e();
        case 0x6f: return op_0x6f();

        case 0x70: return op_0x70();
        case 0x71: return op_0x71();
        case 0x72: return op_0x72();
        case 0x73: return op_0x73();
        case 0x74: return op_0x74();
        case 0x75: return op_0x75();
        case 0x76: return op_0x76();
        case 0x77: return op_0x77();
        case 0x78: return op_0x78();
        case 0x79: return op_0x79();
        case 0x7a: return op_0x7a();
        case 0x7b: return op_0x7b();
        case 0x7c: return op_0x7c();
        case 0x7d: return op_0x7d();
        case 0x7e: return op_0x7e();
        case 0x7f: return op_0x7f();

        case 0x80: return op_0x80();
        case 0x81: return op_0x81();
        case 0x82: return op_0x82();
        case 0x83: return op_0x83();
        case 0x84: return op_0x84();
        case 0x85: return op_0x85();
        case 0x86: return op_0x86();
        case 0x87: return op_0x87();
        case 0x88: return op_0x88();
        case 0x89: return op_0x89();
        case 0x8a: return op_0x8a();
        case 0x8b: return op_0x8b();
        case 0x8c: return op_0x8c();
        case 0x8d: return op_0x8d();
        case 0x8e: return op_0x8e();
        case 0x8f: return op_0x8f();

        case 0x90: return op_0x90();
        case 0x91: return op_0x91();
        case 0x92: return op_0x92();
        case 0x93: return op_0x93();
        case 0x94: return op_0x94();
        case 0x95: return op_0x95();
        case 0x96: return op_0x96();
        case 0x97: return op_0x97();
        case 0x98: return op_0x98();
        case 0x99: return op_0x99();
        case 0x9a: return op_0x9a();
        case 0x9b: return op_0x9b();
        case 0x9c: return op_0x9c();
        case 0x9d: return op_0x9d();
        case 0x9e: return op_0x9e();
        case 0x9f: return op_0x9f();

        case 0xa0: return op_0xa0();
        case 0xa1: return op_0xa1();
        case 0xa2: return op_0xa2();
        case 0xa3: return op_0xa3();
        case 0xa4: return op_0xa4();
        case 0xa5: return op_0xa5();
        case 0xa6: return op_0xa6();
        case 0xa7: return op_0xa7();
        case 0xa8: return op_0xa8();
        case 0xa9: return op_0xa9();
        case 0xaa: return op_0xaa();
        case 0xab: return op_0xab();
        case 0xac: return op_0xac();
        case 0xad: return op_0xad();
        case 0xae: return op_0xae();
        case 0xaf: return op_0xaf();

        case 0xb0: return op_0xb0();
        case 0xb1: return op_0xb1();
        case 0xb2: return op_0xb2();
        case 0xb3: return op_0xb3();
        case 0xb4: return op_0xb4();
        case 0xb5: return op_0xb5();
        case 0xb6: return op_0xb6();
        case 0xb7: return op_0xb7();
        case 0xb8: return op_0xb8();
        case 0xb9: return op_0xb9();
        case 0xba: return op_0xba();
        case 0xbb: return op_0xbb();
        case 0xbc: return op_0xbc();
        case 0xbd: return op_0xbd();
        case 0xbe: return op_0xbe();
        case 0xbf: return op_0xbf();

        case 0xc0: return op_0xc0();
        case 0xc1: return op_0xc1();
        case 0xc2: return op_0xc2();
        case 0xc3: return op_0xc3();
        case 0xc4: return op_0xc4();
        case 0xc5: return op_0xc5();
        case 0xc6: return op_0xc6();
        case 0xc7: return op_0xc7();
        case 0xc8: return op_0xc8();
        case 0xc9: return op_0xc9();
        case 0xca: return op_0xca();

        case 0xcb: {
            uint8_t op_cb = next_u8();

            switch (op_cb) {
                case 0x00: return op_cb_0x00();
                case 0x01: return op_cb_0x01();
                case 0x02: return op_cb_0x02();
                case 0x03: return op_cb_0x03();
                case 0x04: return op_cb_0x04();
                case 0x05: return op_cb_0x05();
                case 0x06: return op_cb_0x06();
                case 0x07: return op_cb_0x07();
                case 0x08: return op_cb_0x08();
                case 0x09: return op_cb_0x09();
                case 0x0a: return op_cb_0x0a();
                case 0x0b: return op_cb_0x0b();
                case 0x0c: return op_cb_0x0c();
                case 0x0d: return op_cb_0x0d();
                case 0x0e: return op_cb_0x0e();
                case 0x0f: return op_cb_0x0f();

                case 0x10: return op_cb_0x10();
                case 0x11: return op_cb_0x11();
                case 0x12: return op_cb_0x12();
                case 0x13: return op_cb_0x13();
                case 0x14: return op_cb_0x14();
                case 0x15: return op_cb_0x15();
                case 0x16: return op_cb_0x16();
                case 0x17: return op_cb_0x17();
                case 0x18: return op_cb_0x18();
                case 0x19: return op_cb_0x19();
                case 0x1a: return op_cb_0x1a();
                case 0x1b: return op_cb_0x1b();
                case 0x1c: return op_cb_0x1c();
                case 0x1d: return op_cb_0x1d();
                case 0x1e: return op_cb_0x1e();
                case 0x1f: return op_cb_0x1f();

                case 0x20: return op_cb_0x20();
                case 0x21: return op_cb_0x21();
                case 0x22: return op_cb_0x22();
                case 0x23: return op_cb_0x23();
                case 0x24: return op_cb_0x24();
                case 0x25: return op_cb_0x25();
                case 0x26: return op_cb_0x26();
                case 0x27: return op_cb_0x27();
                case 0x28: return op_cb_0x28();
                case 0x29: return op_cb_0x29();
                case 0x2a: return op_cb_0x2a();
                case 0x2b: return op_cb_0x2b();
                case 0x2c: return op_cb_0x2c();
                case 0x2d: return op_cb_0x2d();
                case 0x2e: return op_cb_0x2e();
                case 0x2f: return op_cb_0x2f();

                case 0x30: return op_cb_0x30();
                case 0x31: return op_cb_0x31();
                case 0x32: return op_cb_0x32();
                case 0x33: return op_cb_0x33();
                case 0x34: return op_cb_0x34();
                case 0x35: return op_cb_0x35();
                case 0x36: return op_cb_0x36();
                case 0x37: return op_cb_0x37();
                case 0x38: return op_cb_0x38();
                case 0x39: return op_cb_0x39();
                case 0x3a: return op_cb_0x3a();
                case 0x3b: return op_cb_0x3b();
                case 0x3c: return op_cb_0x3c();
                case 0x3d: return op_cb_0x3d();
                case 0x3e: return op_cb_0x3e();
                case 0x3f: return op_cb_0x3f();

                case 0x40: return op_cb_0x40();
                case 0x41: return op_cb_0x41();
                case 0x42: return op_cb_0x42();
                case 0x43: return op_cb_0x43();
                case 0x44: return op_cb_0x44();
                case 0x45: return op_cb_0x45();
                case 0x46: return op_cb_0x46();
                case 0x47: return op_cb_0x47();
                case 0x48: return op_cb_0x48();
                case 0x49: return op_cb_0x49();
                case 0x4a: return op_cb_0x4a();
                case 0x4b: return op_cb_0x4b();
                case 0x4c: return op_cb_0x4c();
                case 0x4d: return op_cb_0x4d();
                case 0x4e: return op_cb_0x4e();
                case 0x4f: return op_cb_0x4f();

                case 0x50: return op_cb_0x50();
                case 0x51: return op_cb_0x51();
                case 0x52: return op_cb_0x52();
                case 0x53: return op_cb_0x53();
                case 0x54: return op_cb_0x54();
                case 0x55: return op_cb_0x55();
                case 0x56: return op_cb_0x56();
                case 0x57: return op_cb_0x57();
                case 0x58: return op_cb_0x58();
                case 0x59: return op_cb_0x59();
                case 0x5a: return op_cb_0x5a();
                case 0x5b: return op_cb_0x5b();
                case 0x5c: return op_cb_0x5c();
                case 0x5d: return op_cb_0x5d();
                case 0x5e: return op_cb_0x5e();
                case 0x5f: return op_cb_0x5f();

                case 0x60: return op_cb_0x60();
                case 0x61: return op_cb_0x61();
                case 0x62: return op_cb_0x62();
                case 0x63: return op_cb_0x63();
                case 0x64: return op_cb_0x64();
                case 0x65: return op_cb_0x65();
                case 0x66: return op_cb_0x66();
                case 0x67: return op_cb_0x67();
                case 0x68: return op_cb_0x68();
                case 0x69: return op_cb_0x69();
                case 0x6a: return op_cb_0x6a();
                case 0x6b: return op_cb_0x6b();
                case 0x6c: return op_cb_0x6c();
                case 0x6d: return op_cb_0x6d();
                case 0x6e: return op_cb_0x6e();
                case 0x6f: return op_cb_0x6f();

                case 0x70: return op_cb_0x70();
                case 0x71: return op_cb_0x71();
                case 0x72: return op_cb_0x72();
                case 0x73: return op_cb_0x73();
                case 0x74: return op_cb_0x74();
                case 0x75: return op_cb_0x75();
                case 0x76: return op_cb_0x76();
                case 0x77: return op_cb_0x77();
                case 0x78: return op_cb_0x78();
                case 0x79: return op_cb_0x79();
                case 0x7a: return op_cb_0x7a();
                case 0x7b: return op_cb_0x7b();
                case 0x7c: return op_cb_0x7c();
                case 0x7d: return op_cb_0x7d();
                case 0x7e: return op_cb_0x7e();
                case 0x7f: return op_cb_0x7f();

                case 0x80: return op_cb_0x80();
                case 0x81: return op_cb_0x81();
                case 0x82: return op_cb_0x82();
                case 0x83: return op_cb_0x83();
                case 0x84: return op_cb_0x84();
                case 0x85: return op_cb_0x85();
                case 0x86: return op_cb_0x86();
                case 0x87: return op_cb_0x87();
                case 0x88: return op_cb_0x88();
                case 0x89: return op_cb_0x89();
                case 0x8a: return op_cb_0x8a();
                case 0x8b: return op_cb_0x8b();
                case 0x8c: return op_cb_0x8c();
                case 0x8d: return op_cb_0x8d();
                case 0x8e: return op_cb_0x8e();
                case 0x8f: return op_cb_0x8f();

                case 0x90: return op_cb_0x90();
                case 0x91: return op_cb_0x91();
                case 0x92: return op_cb_0x92();
                case 0x93: return op_cb_0x93();
                case 0x94: return op_cb_0x94();
                case 0x95: return op_cb_0x95();
                case 0x96: return op_cb_0x96();
                case 0x97: return op_cb_0x97();
                case 0x98: return op_cb_0x98();
                case 0x99: return op_cb_0x99();
                case 0x9a: return op_cb_0x9a();
                case 0x9b: return op_cb_0x9b();
                case 0x9c: return op_cb_0x9c();
                case 0x9d: return op_cb_0x9d();
                case 0x9e: return op_cb_0x9e();
                case 0x9f: return op_cb_0x9f();

                case 0xa0: return op_cb_0xa0();
                case 0xa1: return op_cb_0xa1();
                case 0xa2: return op_cb_0xa2();
                case 0xa3: return op_cb_0xa3();
                case 0xa4: return op_cb_0xa4();
                case 0xa5: return op_cb_0xa5();
                case 0xa6: return op_cb_0xa6();
                case 0xa7: return op_cb_0xa7();
                case 0xa8: return op_cb_0xa8();
                case 0xa9: return op_cb_0xa9();
                case 0xaa: return op_cb_0xaa();
                case 0xab: return op_cb_0xab();
                case 0xac: return op_cb_0xac();
                case 0xad: return op_cb_0xad();
                case 0xae: return op_cb_0xae();
                case 0xaf: return op_cb_0xaf();

                case 0xb0: return op_cb_0xb0();
                case 0xb1: return op_cb_0xb1();
                case 0xb2: return op_cb_0xb2();
                case 0xb3: return op_cb_0xb3();
                case 0xb4: return op_cb_0xb4();
                case 0xb5: return op_cb_0xb5();
                case 0xb6: return op_cb_0xb6();
                case 0xb7: return op_cb_0xb7();
                case 0xb8: return op_cb_0xb8();
                case 0xb9: return op_cb_0xb9();
                case 0xba: return op_cb_0xba();
                case 0xbb: return op_cb_0xbb();
                case 0xbc: return op_cb_0xbc();
                case 0xbd: return op_cb_0xbd();
                case 0xbe: return op_cb_0xbe();
                case 0xbf: return op_cb_0xbf();

                case 0xc0: return op_cb_0xc0();
                case 0xc1: return op_cb_0xc1();
                case 0xc2: return op_cb_0xc2();
                case 0xc3: return op_cb_0xc3();
                case 0xc4: return op_cb_0xc4();
                case 0xc5: return op_cb_0xc5();
                case 0xc6: return op_cb_0xc6();
                case 0xc7: return op_cb_0xc7();
                case 0xc8: return op_cb_0xc8();
                case 0xc9: return op_cb_0xc9();
                case 0xca: return op_cb_0xca();
                case 0xcb: return op_cb_0xcb();
                case 0xcc: return op_cb_0xcc();
                case 0xcd: return op_cb_0xcd();
                case 0xce: return op_cb_0xce();
                case 0xcf: return op_cb_0xcf();

                case 0xd0: return op_cb_0xd0();
                case 0xd1: return op_cb_0xd1();
                case 0xd2: return op_cb_0xd2();
                case 0xd3: return op_cb_0xd3();
                case 0xd4: return op_cb_0xd4();
                case 0xd5: return op_cb_0xd5();
                case 0xd6: return op_cb_0xd6();
                case 0xd7: return op_cb_0xd7();
                case 0xd8: return op_cb_0xd8();
                case 0xd9: return op_cb_0xd9();
                case 0xda: return op_cb_0xda();
                case 0xdb: return op_cb_0xdb();
                case 0xdc: return op_cb_0xdc();
                case 0xdd: return op_cb_0xdd();
                case 0xde: return op_cb_0xde();
                case 0xdf: return op_cb_0xdf();

                case 0xe0: return op_cb_0xe0();
                case 0xe1: return op_cb_0xe1();
                case 0xe2: return op_cb_0xe2();
                case 0xe3: return op_cb_0xe3();
                case 0xe4: return op_cb_0xe4();
                case 0xe5: return op_cb_0xe5();
                case 0xe6: return op_cb_0xe6();
                case 0xe7: return op_cb_0xe7();
                case 0xe8: return op_cb_0xe8();
                case 0xe9: return op_cb_0xe9();
                case 0xea: return op_cb_0xea();
                case 0xeb: return op_cb_0xeb();
                case 0xec: return op_cb_0xec();
                case 0xed: return op_cb_0xed();
                case 0xee: return op_cb_0xee();
                case 0xef: return op_cb_0xef();

                case 0xf0: return op_cb_0xf0();
                case 0xf1: return op_cb_0xf1();
                case 0xf2: return op_cb_0xf2();
                case 0xf3: return op_cb_0xf3();
                case 0xf4: return op_cb_0xf4();
                case 0xf5: return op_cb_0xf5();
                case 0xf6: return op_cb_0xf6();
                case 0xf7: return op_cb_0xf7();
                case 0xf8: return op_cb_0xf8();
                case 0xf9: return op_cb_0xf9();
                case 0xfa: return op_cb_0xfa();
                case 0xfb: return op_cb_0xfb();
                case 0xfc: return op_cb_0xfc();
                case 0xfd: return op_cb_0xfd();
                case 0xfe: return op_cb_0xfe();
                case 0xff: return op_cb_0xff();

                default: println(stderr, "Unimplemented cb opcode"); return 0;
            }
        }

        case 0xcc: return op_0xcc();
        case 0xcd: return op_0xcd();
        case 0xce: return op_0xce();
        case 0xcf: return op_0xcf();

        case 0xd0: return op_0xd0();
        case 0xd1: return op_0xd1();
        case 0xd2: return op_0xd2();
        case 0xd3: return op_0xd3(); // Unused
        case 0xd4: return op_0xd4();
        case 0xd5: return op_0xd5();
        case 0xd6: return op_0xd6();
        case 0xd7: return op_0xd7();
        case 0xd8: return op_0xd8();
        case 0xd9: return op_0xd9();
        case 0xda: return op_0xda();
        case 0xdb: return op_0xdb(); // Unused
        case 0xdc: return op_0xdc();
        case 0xdd: return op_0xdd(); // Unused
        case 0xde: return op_0xde();
        case 0xdf: return op_0xdf();

        case 0xe0: return op_0xe0();
        case 0xe1: return op_0xe1();
        case 0xe2: return op_0xe2();
        case 0xe3: return op_0xe3(); // Unused
        case 0xe4: return op_0xe4(); // Unused
        case 0xe5: return op_0xe5();
        case 0xe6: return op_0xe6();
        case 0xe7: return op_0xe7();
        case 0xe8: return op_0xe8();
        case 0xe9: return op_0xe9();
        case 0xea: return op_0xea();
        case 0xeb: return op_0xeb(); // Unused
        case 0xec: return op_0xec(); // Unused
        case 0xed: return op_0xed(); // Unused
        case 0xee: return op_0xee();
        case 0xef: return op_0xef();

        case 0xf0: return op_0xf0();
        case 0xf1: return op_0xf1();
        case 0xf2: return op_0xf2();
        case 0xf3: return op_0xf3();
        case 0xf4: return op_0xf4(); // Unused
        case 0xf5: return op_0xf5();
        case 0xf6: return op_0xf6();
        case 0xf7: return op_0xf7();
        case 0xf8: return op_0xf8();
        case 0xf9: return op_0xf9();
        case 0xfa: return op_0xfa();
        case 0xfb: return op_0xfb();
        case 0xfc: return op_0xfc(); // Unused
        case 0xfd: return op_0xfd(); // Unused
        case 0xfe: return op_0xfe();
        case 0xff: return op_0xff();
        
        default: println(stderr, "Unimplemented opcode"); return 0;
    }
}