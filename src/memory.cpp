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
        
        if (mode() == 3) {
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

        if (mode() >= 2) {
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

// void Memory::write(uint16_t addr, uint8_t val) {
//     if (addr <= 0x7fff) {

//         if (addr <= 0x3fff) {
//             return rom[addr];
//         }
//         return rom[(addr - 0x4000) + (rom_bank * 0x4000)];

//     } else if (addr <= 0x9fff) {
        
//         if (mode() == 3) {
//             return 0xff;
//         }
//         return vram[(addr - 0x8000) + (vram_bank * 0x2000)];

//     } else if (addr <= 0xbfff) {

//         if (!ram_enabled) {
//             return 0xff;
//         }
//         return sram[(addr - 0xa000) + (sram_bank * 0x2000)];

//     } else if (addr <= 0xdfff) {

//         if (addr <= 0xcfff) {
//             return wram[addr - 0xc000];
//         }
//         return wram[(addr - 0xd000) + (wram_bank * 0x1000)];

//     } else if (addr <= 0xfdff) {

//         cerr << "Echo RAM written to. (" << hex << addr << dec << ")" << endl;
//         return read(addr - 0x2000);

//     } else if (addr <= 0xfe9f) {

//         if (mode() >= 2) {
//             return 0xff;
//         }
//         return oam[addr - 0xfe00];

//     } else if (addr <= 0xfeff) {

//         cerr << "Unusable RAM written to. (" << hex << addr << dec << ")" << endl;
//         return 0xff;

//     } else if (addr <= 0xff7f) {
//         // NOTE: Some io registers are write only
//         return io[addr - 0xff00];

//     } else if (addr <= 0xfffe) {

//         return hram[addr - 0xff80];

//     } else {

//         return ie;
//     }
// }

void Memory::write(uint16_t addr, uint16_t val) {
    
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

    cout << "Loaded ROM. (" << size << " bytes)" << endl;
}

uint8_t Memory::mode() const {
    uint8_t curr_mode = io[0x41] & 0b11;

    switch (curr_mode) {
        case 0b00: return 0; // H-blank
        case 0b01: return 1; // V-blank
        case 0b10: return 2; // OAM search
        case 0b11: return 3; // Pixel transfer
        default: return 0;
    }
}