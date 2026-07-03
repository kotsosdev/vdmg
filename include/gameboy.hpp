#pragma once

#include "./registers.hpp"

#include <string>
#include <cstdint>
#include <vector>

class GameBoy {
    private:
        uint16_t pc{0x0100};
        uint16_t sp{0xFFFE};

        Registers regs;

        uint8_t memory[65536];
        std::vector<uint8_t> rom_data;

        uint64_t curr_bank{1};

        uint16_t div{0};
        uint16_t tima{0};

        bool ime{false};
        bool halted{false};

    public:
        GameBoy();

        void load_rom(const std::string& filename);
};