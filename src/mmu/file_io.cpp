#include "constants.hpp"
#include "mmu.hpp"

#include <cstdint>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <cctype>
#include <algorithm>

using std::cerr;
using std::cout;
using std::hex;
using std::dec;
using std::string;
using std::array;
using std::ifstream;
using std::ios;
using std::isprint;
using std::remove_if;

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