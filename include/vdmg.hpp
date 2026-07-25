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
        VDMG(const std::string& rom_path, const std::string& sav_path);
        ~VDMG();

        void run();

    private:
        bool init{};

        APU apu{};
        CPU cpu{};
        MMU mmu{};
        PPU ppu{};

        std::string rom_path{};
        std::string sav_path{};

        SDL_Window* window{};
        SDL_Renderer* renderer{};
        SDL_Texture* texture{};

        std::chrono::duration<double, std::milli> frame_time{constants::FRAME_TIME_MS};
        int cycles_per_frame{constants::CYCLES_PER_FRAME};
        int curr_frame_cycles{};

        void init_media();
};