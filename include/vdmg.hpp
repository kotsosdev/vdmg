#pragma once

#include "constants.hpp"
#include "apu.hpp"
#include "cpu.hpp"
#include "mmu.hpp"
#include "ppu.hpp"

#include <SDL.h>
#include <cstdint>
#include <string>
#include <chrono>

class VDMG {
    public:
        VDMG(const std::string& rom_path, SDL_Renderer* renderer, SDL_Texture* texture);
        ~VDMG();

        void load_rom(const std::string& rom_path);
        void run();

    private:
        APU apu{};
        CPU cpu{};
        MMU mmu{};
        PPU ppu{};

        std::chrono::duration<double, std::milli> frame_time{constants::FRAME_TIME_MS};
        int cycles_per_frame{constants::CYCLES_PER_FRAME};
        int curr_frame_cycles{};
};