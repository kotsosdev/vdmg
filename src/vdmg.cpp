#include "vdmg.hpp"

#include <SDL.h>
#include <chrono>
#include <thread>

using std::chrono::high_resolution_clock;
using std::this_thread::sleep_for;

VDMG::VDMG(const std::string& rom_path, SDL_Renderer* renderer, SDL_Texture* texture) {
    cpu.set_mmu(&mmu);
    
    mmu.load_rom(rom_path);

    ppu.set_mmu(&mmu);
    ppu.set_headless(false);
    ppu.set_renderer(renderer);
    ppu.set_texture(texture);

    cpu.skip_boot();
    mmu.skip_boot();
}

void VDMG::load_rom(const std::string& rom_path) {
    mmu.load_rom(rom_path);
}

void VDMG::run() {
    auto frame_start_time = high_resolution_clock::now();

    while (true) {
        while (curr_frame_cycles < cycles_per_frame) {
            int cycles = cpu.step();

            mmu.sync_timers(cycles);
            ppu.sync_ppu(cycles);
            // sync_apu(cycles);

            curr_frame_cycles += cycles;
        }

        curr_frame_cycles -= cycles_per_frame;

        if (!ppu.read_input()) break;
        ppu.push_video();
        // push_audio();

        auto frame_end_time = high_resolution_clock::now();
        auto time_elapsed = frame_end_time - frame_start_time;
        
        if (time_elapsed < frame_time) {
            sleep_for(frame_time - time_elapsed);
        }

        frame_start_time = high_resolution_clock::now();
    }
}