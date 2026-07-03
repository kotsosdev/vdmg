#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Cartridge {
    private:
        uint8_t sram[0x2000];
        std::vector<uint8_t> rom_data;
        uint64_t curr_bank{1};

    public:
        void load_rom(const std::string& filename);
};