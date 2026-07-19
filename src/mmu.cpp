#include "../include/mmu.hpp"

#include <print>
#include <cstdio>
#include <cstdint>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <algorithm>

#include <iostream>

using std::println;
using std::print;

using std::string;

using std::ifstream;
using std::ios;

using std::array;

using std::fill;

void MMU::sync_timers(int cycles) {
    running_div_cycles += cycles;
    running_tima_cycles += cycles;

    uint8_t div = direct_read(0xff04);
    uint8_t tima = direct_read(0xff05);
    uint8_t tma = direct_read(0xff06);
    uint8_t tac = direct_read(0xff07);

    while (running_div_cycles >= 256) {
        direct_write(0xff04, ++div);
        running_div_cycles -= 256;
    }

    if (tac & 0x04) {
        int cycle_threshold = 0;
        switch (tac & 0x03) {
            case 0: cycle_threshold = 1024; break;  // 4096 Hz
            case 1: cycle_threshold = 16; break;    // 262144 Hz
            case 2: cycle_threshold = 64; break;    // 65536 Hz
            case 3: cycle_threshold = 256; break;   // 16384 Hz
        }

        while (running_tima_cycles >= cycle_threshold) {
            ++tima;
            running_tima_cycles -= cycle_threshold;

            if (!tima) {
                tima = tma;
                direct_write(0xff0f, static_cast<uint8_t>(direct_read(0xff0f) | 0x04));
            }
        }

        direct_write(0xff05, tima);

    } else {
        running_tima_cycles = 0;
    }
}

uint8_t MMU::read(uint16_t addr) const {
    uint8_t ppu_mode = direct_read(0xff41) & 0x03;

    if (0x8000 <= addr && addr <= 0x9fff) {
        if (ppu_mode == 3) return 0xff;
        return direct_read(addr);

    } else if (0xa000 <= addr && addr <= 0xbfff) {
        if (!sram_enabled) return 0xff;
        return direct_read(addr);

    } else if (0xe000 <= addr && addr <= 0xfdff) {
        // println(stderr, "Echo RAM read");
        return direct_read(addr - 0x2000);

    } else if (0xfe00 <= addr && addr <= 0xfe9f) {
        if (ppu_mode >= 2) return 0xff;
        return direct_read(addr);

    } else if (0xfea0 <= addr && addr <= 0xfeff) {
        // println(stderr, "Unusable RAM read");
        return 0xff;

    } else if (0xff00 <= addr && addr <= 0xff7f) {
        return read_io(addr);

    } else {
        return direct_read(addr);
    }
}

void MMU::write(uint16_t addr, uint8_t val) {
    uint8_t ppu_mode = direct_read(0xff41) & 0x03;

    if (addr <= 0x7fff) {
        mbc_intercept(addr, val);

    } else if (0x8000 <= addr && addr <= 0x9fff) {
        if (ppu_mode == 3) return;
        direct_write(addr, val);

    } else if (0xa000 <= addr && addr <= 0xbfff) {
        if (!sram_enabled) return;
        direct_write(addr, val);

    } else if (0xe000 <= addr && addr <= 0xfdff) {
        // println(stderr, "Echo RAM written to");
        direct_write(addr - 0x2000, val);

    } else if (0xfe00 <= addr && addr <= 0xfe9f) {
        if (ppu_mode >= 2) return;
        direct_write(addr, val);

    } else if (0xfea0 <= addr && addr <= 0xfeff) {
        // println(stderr, "Unusable RAM written to");

    } else if (0xff00 <= addr && addr <= 0xff7f) {
        write_io(addr, val);

    } else {
        direct_write(addr, val);
    }
}

void MMU::write(uint16_t addr, uint16_t val) {
    write(addr, static_cast<uint8_t>(val & 0x00ff));
    write(static_cast<uint16_t>(addr + 0x01), static_cast<uint8_t>(val >> 8));
}

void MMU::load_rom(const std::string& filename) {
    ifstream file(filename, ios::binary | ios::ate);

    if (!file) {
        println(stderr, "Failed to open ROM");
        return;
    }
    
    size_t rom_size = static_cast<size_t>(file.tellg());
    rom.resize(rom_size);
    
    file.clear();
    file.seekg(0);

    file.read(reinterpret_cast<char*>(rom.data()), rom_size);
    if (!file) {
        println(stderr, "Failed to read ROM");
        rom.clear();
        return;
    }

    read_header();

    if (!verify_rom()) {
        println(stderr, "Failed to verify ROM");
        rom.clear();
        return;
    }

    array<size_t, 6> sram_sizes = {0x0000, 0x0800, 0x2000, 0x8000, 0x20000, 0x10000};
    size_t sram_size = sram_sizes[header.sram_size];
    sram.resize(sram_size);

    println("Loaded ROM: '{}'", header.title);
}

void MMU::reset() {
    fill(vram.begin(), vram.end(), 0x00);
    fill(sram.begin(), sram.end(), 0x00);
    fill(wram.begin(), wram.end(), 0x00);
    fill(oam.begin(), oam.end(), 0x00);
    fill(io.begin(), io.end(), 0x00);
    fill(hram.begin(), hram.end(), 0x00);

    direct_write(0xff00, 0xcf);  // JOYP
    direct_write(0xff01, 0x00);  // SB
    direct_write(0xff02, 0x7e);  // SC
    
    direct_write(0xff04, 0xab);  // DIV
    direct_write(0xff05, 0x00);  // TIMA
    direct_write(0xff06, 0x00);  // TMA
    direct_write(0xff07, 0xf8);  // TAC

    direct_write(0xff0d, 0x7e);  // KEY1
    direct_write(0xff0f, 0xe1);  // IF
    
    direct_write(0xff40, 0x91);  // LCDC
    direct_write(0xff41, 0x85);  // STAT
    direct_write(0xff42, 0x00);  // SCY
    direct_write(0xff43, 0x00);  // SCX
    direct_write(0xff44, 0x00);  // LY
    direct_write(0xff45, 0x00);  // LYC
    direct_write(0xff47, 0xfc);  // BGP
    direct_write(0xff48, 0xff);  // OBP0
    direct_write(0xff49, 0xff);  // OBP1
    direct_write(0xff4a, 0x00);  // WY
    direct_write(0xff4b, 0x00);  // WX
    
    direct_write(0xff70, 0x01);  // SVBK 

    direct_write(0xffff, 0x00);  // IE register
}

uint8_t MMU::direct_read(uint16_t addr) const {
    if (addr <= 0x7fff) {
        size_t i = (addr <= 0x3fff) ? addr : ((addr - 0x4000) + (rom_bank * 0x4000));
        return (i < rom.size()) ? rom[i] : 0xff;

    } else if (addr <= 0x9fff) {
        return vram[(addr - 0x8000) + (vram_bank * 0x2000)];

    } else if (addr <= 0xbfff) {
        size_t i = (addr - 0xa000) + (sram_bank * 0x2000);
        return (i < sram.size()) ? sram[i] : 0xff;

    } else if (addr <= 0xdfff) {

        if (addr <= 0xcfff) {
            return wram[addr - 0xc000];
        }
        return wram[(addr - 0xd000) + (wram_bank * 0x1000)];

    } else if (addr <= 0xfdff) {
        // println(stderr, "Echo RAM directly read");
        return direct_read(addr - 0x2000);

    } else if (addr <= 0xfe9f) {
        return oam[addr - 0xfe00];

    } else if (addr <= 0xfeff) {
        // println(stderr, "Unusable RAM directly read");
        return 0xff;

    } else if (addr <= 0xff7f) {
        return io[addr - 0xff00];

    } else if (addr <= 0xfffe) {
        return hram[addr - 0xff80];

    } else {
        return ie;
    }
}

void MMU::direct_write(uint16_t addr, uint8_t val) {
    if (addr <= 0x7fff) {
        // println(stderr, "ROM directly written to");

    } else if (addr <= 0x9fff) {
        vram[(addr - 0x8000) + (vram_bank * 0x2000)] = val;

    } else if (addr <= 0xbfff) {
        sram[(addr - 0xa000) + (sram_bank * 0x2000)] = val;

    } else if (addr <= 0xdfff) {

        if (addr <= 0xcfff) {
            wram[addr - 0xc000] = val;
            return;
        }
        wram[(addr - 0xd000) + (wram_bank * 0x1000)] = val;

    } else if (addr <= 0xfdff) {
        // println(stderr, "Echo RAM directly written to");
        direct_write(addr - 0x2000, val);

    } else if (addr <= 0xfe9f) {
        oam[addr - 0xfe00] = val;

    } else if (addr <= 0xfeff) {
        // println(stderr, "Unusable RAM directly written to");

    } else if (addr <= 0xff7f) {
        io[addr - 0xff00] = val;

    } else if (addr <= 0xfffe) {
        hram[addr - 0xff80] = val;

    } else {
        ie = val;
    }
}

uint8_t MMU::read_io(uint16_t addr) const {
    switch (addr) {
        case 0xff00: {
            uint8_t val = direct_read(addr);
            bool read_buttons = (val & 0x20) == 0x00;
            bool read_dpad = (val & 0x10) == 0x00;

            return (
                0xc0 | (val & 0x30) |
                ((read_buttons ? buttons_state : 0x0f) &
                (read_dpad ? dpad_state : 0x0f))
            );
        }
        // case 0xff07: return 0xf8 | direct_read(addr);
        case 0xff0f: return 0xe0 | direct_read(addr);

        default: return direct_read(addr);
    }
}

void MMU::write_io(uint16_t addr, uint8_t val) {
    switch (addr) {
        // case 0xff00: direct_write(addr, val & 0x30); break;
        case 0xff02: {
            if (val == 0x81) {
                print("{}", static_cast<char>(read(0xff01)));
                direct_write(addr, 0x01);
            } else {
                direct_write(addr, val);
            }
        } break;
        // case 0xff04: direct_write(addr, 0x00); break;
        // case 0xff07: direct_write(addr, val & 0x07); break;
        // case 0xff0f: direct_write(addr, val & 0x1f); break;

        default: direct_write(addr, val);
    }
}

void MMU::read_header() {
    header.title = string(reinterpret_cast<const char*>(&rom[0x0134]), 16);
    header.cgb_flag = rom[0x0143];
    header.sgb_flag = rom[0x0146];
    header.cart_type = rom[0x0147];
    header.rom_size = rom[0x0148];
    header.sram_size = rom[0x0149];
    header.header_checksum = rom[0x014d];
    header.global_checksum = (rom[0x014e] << 8) | rom[0x014f];
}

bool MMU::verify_rom() {
    array<uint8_t, 48> logo = {
        0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
        0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
        0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63,
        0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e
    };
    bool logo_passed = true;
    for (size_t i = 0; i < logo.size(); ++i) {
        if (rom[0x0104 + i] != logo[i]) {
            logo_passed = false;
            break;
        }
    }

    uint8_t header_checksum = 0;
    for (size_t i = 0x0134; i <= 0x014c; ++i) {
        header_checksum = header_checksum - rom[i] - 1;
    }
    bool header_checksum_passed = header.header_checksum == header_checksum;

    uint16_t global_checksum = 0;
    for (size_t i = 0x0000; i < rom.size(); ++i) {
        if (i == 0x014e || i == 0x014f) continue;
        global_checksum += rom[i];
    }
    bool global_checksum_passed = header.global_checksum == global_checksum;

    println("Logo*: {}", logo_passed ? "OK" : "Failed");
    println("Header checksum*: {}", header_checksum_passed ? "OK" : "Failed");
    println("Global checksum: {}", global_checksum_passed ? "OK" : "Failed");

    return (
        logo_passed &&
        header_checksum_passed
    );
}

void MMU::mbc_intercept(uint16_t addr, uint8_t val) {
    // ROM
    if (header.cart_type == 0x00 || (0x08 <= header.cart_type && header.cart_type <= 0x09)) {
        // No intercept

    // MBC1
    } else if (0x01 <= header.cart_type && header.cart_type <= 0x03) {
    
        if (addr <= 0x1fff) {
            sram_enabled = (val & 0x0f) == 0x0a;
            return;

        } else if (addr <= 0x3fff) {
            bank_reg1 = val & 0x1f;

        } else if (addr <= 0x5fff) {
            bank_reg2 = val & 0x03;

        } else {
            banking_mode = val & 0x01;
        }

        sync_rom_bank();
        sync_sram_bank();

    // MBC2
    // } else if (0x05 <= header.cart_type && header.cart_type <= 0x06) {

    // MBC3
    // } else if (0x0f <= header.cart_type && header.cart_type <= 0x13) {

    // MBC5
    } else if (0x19 <= header.cart_type && header.cart_type <= 0x1e) {
        
        if (addr <= 0x1fff) {
            sram_enabled = (val & 0x0f) == 0x0a;

        } else if (addr <= 0x2fff) {
            size_t rom_banks = rom.size() >> 14;
            rom_bank = ((rom_bank & 0x0100) | val) & (rom_banks - 0x01);

        } else if (addr <= 0x3fff) {
            size_t rom_banks = rom.size() >> 14;
            rom_bank = (((val & 0x01) << 8) | (rom_bank & 0x0ff)) & (rom_banks - 0x01);
        
        } else if (addr <= 0x5fff) {
            size_t sram_banks = sram.size() >> 13;
            sram_bank = sram_banks > 0 ? ((val & 0x0f) & (sram_banks - 0x01)) : 0;

        } else {
            // println(stderr, "Unusable ROM written to"); 
        }

    } else {
        // println(stderr, "Unimplemented cartridge type");
    }
}

void MMU::sync_rom_bank() {
    size_t rom_banks = rom.size() >> 14;
    uint16_t bank = banking_mode ? bank_reg1 : ((bank_reg2 << 5) | bank_reg1);
    bank = bank > 0 ? bank : 1;

    rom_bank = bank & (rom_banks - 0x01);
}

void MMU::sync_sram_bank() {
    sram_bank = banking_mode ? bank_reg2 : 0;
}