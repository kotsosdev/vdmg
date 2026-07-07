#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Cartridge {
    private:
        // 0x0000 - 0x7fff (Bank switching)
        std::vector<uint8_t> rom{};
        uint16_t curr_rom_bank{};

        // 0xa000 - 0xbfff (Bank switching)
        std::vector<uint8_t> sram{};
        uint16_t curr_sram_bank{};

    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);

        void load_rom(const std::string& filename);
};