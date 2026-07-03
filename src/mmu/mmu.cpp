#include "../../include/mmu/mmu.hpp"

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
using std::streampos;

void MMU::load_rom(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    
    if (file.is_open()) {
        streampos size = file.tellg();
    }

    // TODO
}

uint8_t MMU::read(uint16_t addr) const {
    if (addr <= 0x3fff) {
        return mem.rom0[addr];
    } else if (addr <= 0x7fff) {
        return mem.romx[addr-0x4000];
    } else if (addr <= 0x9fff) {
        return mem.vram[addr-0x8000];
    } else if (addr <= 0xbfff) {
        return mem.sram[addr-0xa000];
    } else if (addr <= 0xdfff) {
        return mem.wram[addr-0xc000];
    } else if (addr <= 0xfdff) {
        return mem.wram[addr-0xe000];
    } else if (addr <= 0xfe9f) {
        return mem.oam[addr-0xfe00];
    } else if (addr <= 0xfeff) {
        cerr << "Attempted to read prohibited address: " << hex << addr << dec << endl;
        return 0x00;
    } else if (addr <= 0xff7f) {
        return mem.io[addr-0xff00];
    } else if (addr <= 0xffff) {
        return mem.hram[addr-0xff80];
    } else {
        cerr << "Attempted to read out of bounds address: " << hex << addr << dec << endl;
    }
}

void MMU::write(uint8_t byte) {

}