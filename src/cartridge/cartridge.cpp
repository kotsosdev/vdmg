#include "../../include/cartridge/cartridge.hpp"

#include <string>
#include <iostream>
#include <fstream>

using std::string;

using std::cerr;
using std::endl;
using std::hex;
using std::dec;

using std::ifstream;
using std::ios;

uint8_t Cartridge::read(uint16_t addr) {

}

void Cartridge::write(uint16_t addr, uint8_t val) {
    
}

void Cartridge::load_rom(const string& filename) {
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
}