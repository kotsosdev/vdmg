#pragma once

#include "apu.hpp"
#include "cpu.hpp"
#include "mmu.hpp"
#include "ppu.hpp"

#include <SDL.h>
#include <string>
#include <cstdint>
#include <chrono>

class VDMG {
    public:
        VDMG(const std::string& rom_path, SDL_Renderer* renderer, SDL_Texture* texture);

        void load_rom(const std::string& rom_path);
        void reset();
        void run();

    private:
        CPU cpu{};
        MMU mmu{};
        PPU ppu{};

        std::chrono::duration<double, std::milli> target_frame_time{16.7427};
        int cycles_per_frame{70224};
        int curr_frame_cycles{};
};