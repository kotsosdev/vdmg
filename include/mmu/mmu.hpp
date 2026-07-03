#pragma once

#include <cstdint>
#include <vector>
#include <string>

class MMU {
    private:
        struct Memory {
            uint8_t rom0[0x4000]; 
            uint8_t romx[0x4000];
            uint8_t vram[0x2000];
            uint8_t sram[0x2000];
            uint8_t wram[0x2000];
            // uint8_t echo[0x1e00];
            uint8_t oam[0xa0];
            // uint8_t unused[0x60];
            uint8_t io[0x80];
            uint8_t hram[0x80];
        };

        Memory mem;
        std::vector<uint8_t> rom_data;
        uint64_t curr_bank{1};
    public:
        void load_rom(const std::string& filename);

        uint8_t read(uint16_t addr) const;
        void write(uint8_t byte);
};