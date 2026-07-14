#include "../include/mmu.hpp"

#include <print>
#include <cstdio>
#include <string>
#include <fstream>

using std::println;

using std::string;

using std::ifstream;
using std::ios;

uint8_t MMU::read(uint16_t addr) const {
    if (addr <= 0x7fff) {

        if (addr <= 0x3fff) {
            return rom[addr];
        }
        return rom[(addr - 0x4000) + (rom_bank * 0x4000)];

    } else if (addr <= 0x9fff) {
        
        if ((read(0xff41) & 0x03) == 3) {
            return 0xff;
        }
        return vram[(addr - 0x8000) + (vram_bank * 0x2000)];

    } else if (addr <= 0xbfff) {

        if (!sram_enabled) {
            println(stderr, "SRAM read while disabled");
            return 0xff;
        }
        return sram[(addr - 0xa000) + (sram_bank * 0x2000)];

    } else if (addr <= 0xdfff) {

        if (addr <= 0xcfff) {
            return wram[addr - 0xc000];
        }
        return wram[(addr - 0xd000) + (wram_bank * 0x1000)];

    } else if (addr <= 0xfdff) {
        println(stderr, "Echo RAM read");
        return read(addr - 0x2000);

    } else if (addr <= 0xfe9f) {

        if ((read(0xff41) & 0x03) >= 2) {
            return 0xff;
        }
        return oam[addr - 0xfe00];

    } else if (addr <= 0xfeff) {
        println(stderr, "Unusable RAM read");
        return 0xff;

    // NOTE: Some io registers are write only, abstract in a func
    } else if (addr <= 0xff7f) {
        return io[addr - 0xff00];

    } else if (addr <= 0xfffe) {
        return hram[addr - 0xff80];

    } else {
        return ie;
    }
}

void MMU::write(uint16_t addr, uint8_t val) {
    if (addr <= 0x7fff) {
        write_intercept(addr, val);

    } else if (addr <= 0x9fff) {
        
        if ((read(0xff41) & 0x03) == 3) {
            return;
        }
        vram[(addr - 0x8000) + (vram_bank * 0x2000)] = val;

    } else if (addr <= 0xbfff) {

        if (!sram_enabled) {
            println(stderr, "SRAM written to while disabled");
            return;
        }
        sram[(addr - 0xa000) + (sram_bank * 0x2000)] = val;

    } else if (addr <= 0xdfff) {

        if (addr <= 0xcfff) {
            wram[addr - 0xc000] = val;
            return;
        }
        wram[(addr - 0xd000) + (wram_bank * 0x1000)] = val;

    } else if (addr <= 0xfdff) {
        println(stderr, "Echo RAM written to");
        write(addr - 0x2000, val);

    } else if (addr <= 0xfe9f) {

        if ((read(0xff41) & 0x03) >= 2) {
            return;
        }
        oam[addr - 0xfe00] = val;

    } else if (addr <= 0xfeff) {
        println(stderr, "Unusable RAM written to");

    // NOTE: Some io registers are read only, abstract in a func
    } else if (addr <= 0xff7f) {
        io[addr - 0xff00] = val;

    } else if (addr <= 0xfffe) {
        hram[addr - 0xff80] = val;

    } else {
        ie = val;
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
    
    size_t size = static_cast<size_t>(file.tellg());
    rom.resize(size);
    
    file.clear();
    file.seekg(0);

    file.read(reinterpret_cast<char*>(rom.data()), size);
    if (!file) {
        println(stderr, "Failed to read ROM");
        rom.clear();
        return;
    }

    read_header();

    println("Loaded ROM");
}

void MMU::read_header() {
    header.game_title = string(reinterpret_cast<const char*>(&rom[0x0134]), 16);
    header.cgb_flag = rom[0x0143];
    header.sgb_flag = rom[0x0146];
    header.cart_type = rom[0x0147];
    header.header_cs = rom[0x014d];
    header.global_cs = (rom[0x014f] << 8) | rom[0x014e];
}

void MMU::write_intercept(uint16_t addr, uint8_t val) {
    // ROM
    if (header.cart_type == 0x00 || (0x08 <= header.cart_type && header.cart_type <= 0x09)) {
        // No intercept

    // MBC1
    // } else if (0x01 <= header.cart_type && header.cart_type <= 0x03) {
    
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
            println(stderr, "Unusable ROM written to"); 
        }

    } else {
        println(stderr, "Unimplemented cartridge type");
    }
}