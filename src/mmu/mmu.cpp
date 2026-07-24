#include "constants.hpp"
#include "mmu.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <algorithm>

using std::cerr;
using std::cout;
using std::hex;
using std::dec;
using std::string;
using std::ifstream;
using std::ios;
using std::array;
using std::fill;
using std::remove;
using std::isprint;

void MMU::sync_timers(int cycles) {
    running_div_cycles += cycles;
    running_tima_cycles += cycles;

    uint8_t div = direct_read(0xff04);
    uint8_t tima = direct_read(0xff05);
    uint8_t tma = direct_read(0xff06);
    uint8_t tac = direct_read(0xff07);

    if (running_div_cycles >= 256) {
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

uint8_t MMU::read(uint16_t addr) {
    uint8_t ppu_mode = direct_read(0xff41) & 0x03;

    if (0x8000 <= addr && addr <= 0x9fff) {
        if (ppu_mode == 3) return 0xff;
        return direct_read(addr);

    } else if (0xa000 <= addr && addr <= 0xbfff) {
        if (!sram_enabled) return 0xff;
        else if (rtc.is_enabled()) return rtc.read();
        else return direct_read(addr);

    } else if (0xe000 <= addr && addr <= 0xfdff) {
        // cerr << "Echo RAM read\n";
        return direct_read(addr - 0x2000);

    } else if (0xfe00 <= addr && addr <= 0xfe9f) {
        if (ppu_mode >= 2) return 0xff;
        return direct_read(addr);

    } else if (0xfea0 <= addr && addr <= 0xfeff) {
        // cerr << "Unusable RAM read\n";
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
        else if (rtc.is_enabled()) rtc.write(val);
        else direct_write(addr, val);

    } else if (0xe000 <= addr && addr <= 0xfdff) {
        // cerr << "Echo RAM written to\n";
        direct_write(addr - 0x2000, val);

    } else if (0xfe00 <= addr && addr <= 0xfe9f) {
        if (ppu_mode >= 2) return;
        direct_write(addr, val);

    } else if (0xfea0 <= addr && addr <= 0xfeff) {
        // cerr << "Unusable RAM written to\n";

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
        // cerr << "Echo RAM directly read\n";
        return direct_read(addr - 0x2000);

    } else if (addr <= 0xfe9f) {
        return oam[addr - 0xfe00];

    } else if (addr <= 0xfeff) {
        // cerr << "Unusable RAM directly read\n";
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
        // cerr << "ROM directly written to\n";

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
        // cerr << "Echo RAM directly written to\n";
        direct_write(addr - 0x2000, val);

    } else if (addr <= 0xfe9f) {
        oam[addr - 0xfe00] = val;

    } else if (addr <= 0xfeff) {
        // cerr << "Unusable RAM directly written to\n";

    } else if (addr <= 0xff7f) {
        io[addr - 0xff00] = val;

    } else if (addr <= 0xfffe) {
        hram[addr - 0xff80] = val;

    } else {
        ie = val;
    }
}

void MMU::load_rom(const std::string& rom_path) {
    ifstream file(rom_path, ios::binary | ios::ate);

    if (!file) {
        cerr << "Failed to open ROM\n";
        return;
    }
    
    size_t rom_size = static_cast<size_t>(file.tellg());
    rom.resize(rom_size);
    
    file.clear();
    file.seekg(0);

    file.read(reinterpret_cast<char*>(rom.data()), rom_size);
    if (!file) {
        cerr << "Failed to read ROM\n";
        rom.clear();
        return;
    }

    read_header();

    if (!verify_rom()) {
        cerr << "Failed to verify ROM\n";
        rom.clear();
        return;
    }

    array<size_t, 6> sram_sizes = {0x0000, 0x0800, 0x2000, 0x8000, 0x20000, 0x10000};
    size_t sram_size = sram_sizes[header.sram_size];
    sram.resize(sram_size);

    cout << "Loaded ROM: '" << header.title << "'\n";
    cout << "Cartridge type: 0x" << hex << static_cast<int>(header.cart_type) << dec << '\n';
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

void MMU::read_header() {
    header.title = string(reinterpret_cast<const char*>(&rom[0x0134]), 16);
    header.title.erase(
        remove_if(
            header.title.begin(), header.title.end(),
            [](unsigned char c) {return !isprint(c);}
        ),
        header.title.end()
    );

    header.cgb_flag = rom[0x0143];
    header.sgb_flag = rom[0x0146];
    header.cart_type = rom[0x0147];
    header.rom_size = rom[0x0148];
    header.sram_size = rom[0x0149];
    header.header_checksum = rom[0x014d];
    header.global_checksum = (rom[0x014e] << 8) | rom[0x014f];
}

bool MMU::verify_rom() {
    bool logo_passed = true;
    for (size_t i = 0; i < constants::LOGO.size(); ++i) {
        if (rom[0x0104 + i] != constants::LOGO[i]) {
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

    cout << "Logo*: " << (logo_passed ? "OK" : "Failed") << '\n';
    cout << "Header checksum*: " << (header_checksum_passed ? "OK" : "Failed") << '\n';
    cout << "Global checksum: " << (global_checksum_passed ? "OK" : "Failed") << '\n';

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

        size_t rom_banks = rom.size() >> 14;
        uint8_t bank = banking_mode ? bank_reg1 : ((bank_reg2 << 5) | bank_reg1);
        bank = bank > 0 ? bank : 1;

        rom_bank = bank & (rom_banks - 0x01);
        sram_bank = banking_mode ? bank_reg2 : 0;

    // MBC2
    // } else if (0x05 <= header.cart_type && header.cart_type <= 0x06) {

    // MBC3
    } else if (0x0f <= header.cart_type && header.cart_type <= 0x13) {

        if (addr <= 0x1fff) {
            sram_enabled = (val & 0x0f) == 0x0a;

        } else if (addr <= 0x3fff) {
            size_t rom_banks = rom.size() >> 14;
            uint8_t bank = val;
            bank = bank > 0 ? bank : 1;
            rom_bank = bank & (rom_banks - 0x01);

        } else if (addr <= 0x5fff) {

            if (val <= 0x03) {
                rtc.set_enabled(false);
                sram_bank = val;

            } else if (0x08 <= val && val <= 0x0c) {
                rtc.set_enabled(true);
                rtc.set_bank(val);
            }

        } else {
            
            if (val == 0x00) {
                rtc.set_latched(false);
                rtc.set_latch_armed(true);

            } else if (val == 0x01 && rtc.is_latch_armed()) {
                rtc.set_latched(true);
                rtc.set_latch_armed(false);
                rtc.latch();

            } else {
                rtc.set_latch_armed(false);
            }
        }

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
            // cerr << "Unusable ROM written to\n"; 
        }

    } else {
        // cerr << "Unimplemented cartridge type\n";
    }
}

// TODO
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
        case 0xff0f: return 0xe0 | direct_read(addr);

        default: return direct_read(addr);
    }
}

// TODO
void MMU::write_io(uint16_t addr, uint8_t val) {
    switch (addr) {
        case 0xff00: direct_write(addr, (direct_read(addr) & 0xcf) | (val & 0x30)); break;
        case 0xff02: {
            if (val == 0x81) {
                cout << static_cast<char>(read(0xff01));
                direct_write(addr, 0x01);
            } else {
                direct_write(addr, val);
            }
        } break;
        case 0xff44: direct_write(addr, 0x00);
        case 0xff46: { // HACK: 0 cycles
            uint16_t source_addr = static_cast<uint16_t>(val) << 8;
            for (int i = 0; i < 160; ++i) write(0xfe00 + i, read(source_addr + i));
        }

        default: direct_write(addr, val);
    }
}