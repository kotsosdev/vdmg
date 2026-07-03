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

void Cartridge::load_rom(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);

    if (!file) {
        cerr << "Failed to open ROM." << endl;
        return;
    }
    
    size_t size = static_cast<size_t>(file.tellg());
    rom_data.resize(size);

    file.clear();
    file.seekg(0);

    file.read(reinterpret_cast<char*>(rom_data.data()), size);
    if (!file) {
        cerr << "Failed to read ROM." << endl;
        rom_data.clear();
        return;
    }
}