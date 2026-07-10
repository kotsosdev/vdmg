#include "../include/memory.hpp"

#include <string>
#include <iostream>
#include <fstream>

using std::string;

using std::cout;
using std::cerr;
using std::endl;
using std::hex;
using std::dec;

using std::ifstream;
using std::ios;

uint8_t Memory::read(uint16_t addr) const {
    if (addr <= 0x7fff) {

        if (addr <= 0x3fff) {
            return rom[addr];
        }
        return rom[(addr - 0x4000) + (rom_bank * 0x4000)];

    } else if (addr <= 0x9fff) {
        
        if (ppu_mode() == 3) {
            return 0xff;
        }
        return vram[(addr - 0x8000) + (vram_bank * 0x2000)];

    } else if (addr <= 0xbfff) {

        if (!ram_enabled) {
            return 0xff;
        }
        return sram[(addr - 0xa000) + (sram_bank * 0x2000)];

    } else if (addr <= 0xdfff) {

        if (addr <= 0xcfff) {
            return wram[addr - 0xc000];
        }
        return wram[(addr - 0xd000) + (wram_bank * 0x1000)];

    } else if (addr <= 0xfdff) {

        cerr << "Echo RAM read. (" << hex << addr << dec << ")" << endl;
        return read(addr - 0x2000);

    } else if (addr <= 0xfe9f) {

        if (ppu_mode() >= 2) {
            return 0xff;
        }
        return oam[addr - 0xfe00];

    } else if (addr <= 0xfeff) {

        cerr << "Unusable RAM read. (" << hex << addr << dec << ")" << endl;
        return 0xff;

    } else if (addr <= 0xff7f) {
        // NOTE: Some io registers are write only
        return io[addr - 0xff00];

    } else if (addr <= 0xfffe) {

        return hram[addr - 0xff80];

    } else {

        return ie;
    }
}

void Memory::write(uint16_t addr, uint8_t val) {
    if (addr <= 0x7fff) {

        mbc_intercept(addr, val);

    } else if (addr <= 0x9fff) {
        
        if (ppu_mode() == 3) {
            return;
        }
        vram[(addr - 0x8000) + (vram_bank * 0x2000)] = val;

    } else if (addr <= 0xbfff) {

        if (!ram_enabled) {
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

        cerr << "Echo RAM written to. (" << hex << addr << dec << ")" << endl;
        write(addr - 0x2000, val);

    } else if (addr <= 0xfe9f) {

        if (ppu_mode() >= 2) {
            return;
        }
        oam[addr - 0xfe00] = val;

    } else if (addr <= 0xfeff) {

        cerr << "Unusable RAM written to. (" << hex << addr << dec << ")" << endl;

    } else if (addr <= 0xff7f) {
        // NOTE: Some io registers are read only
        io[addr - 0xff00] = val;

    } else if (addr <= 0xfffe) {

        hram[addr - 0xff80] = val;

    } else {

        ie = val;
    }
}

void Memory::write(uint16_t addr, uint16_t val) {
    uint8_t lo = val & 0x00ff;
    uint8_t hi = val >> 8;
    
    write(addr, lo);
    write(addr + 1, hi);
}

void Memory::load_rom(const std::string& filename) {
    ifstream file(filename, ios::binary | ios::ate);

    if (!file) {
        cerr << "Failed to open ROM." << endl;
        return;
    }
    
    size_t size = static_cast<size_t>(file.tellg());
    rom.resize(size);
    
    file.clear();
    file.seekg(0);

    file.read(reinterpret_cast<char*>(rom.data()), size);
    if (!file) {
        cerr << "Failed to read ROM." << endl;
        rom.clear();
        return;
    }

    read_header();

    cout << "Loaded ROM. (" << size << " bytes)" << endl;
}

void Memory::read_header() {
    header.game_title = reinterpret_cast<const char*>(&rom[0x0134]);
    header.cgb_flag = rom[0x0143];
    header.sgb_flag = rom[0x0146];
    header.cart_type = rom[0x0147];
    header.header_cs = rom[0x014d];
    header.global_cs = (rom[0x014f] << 8) | rom[0x014e];
}

void Memory::mbc_intercept(uint16_t addr, uint8_t val) {
    if (header.cart_type == 0x00) {
        return; // ROM

    } else if (0x01 <= header.cart_type && header.cart_type <= 0x03) {
        // MBC1

    } else if (0x05 <= header.cart_type && header.cart_type <= 0x06) {
        // MBC2

    } else if (0x08 <= header.cart_type && header.cart_type <= 0x09) {
        return; // ROM

    } else if (0x0f <= header.cart_type && header.cart_type <= 0x13) {
        // MBC3

    } else if (0x19 <= header.cart_type && header.cart_type <= 0x1e) {
        // MBC5
        
    } else {
        cerr << "Unimplemented cartridge type. (" << hex << header.cart_type << dec << ")";
        return;
    }
}

uint8_t Memory::ppu_mode() const {
    uint8_t curr_mode = read(0xff41) & 0b11;

    switch (curr_mode) {
        case 0b00: return 0; // H-blank
        case 0b01: return 1; // V-blank
        case 0b10: return 2; // OAM search
        case 0b11: return 3; // Pixel transfer
        default: return 0;
    }
}