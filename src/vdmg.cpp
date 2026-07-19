#include "../include/vdmg.hpp"

#include <chrono>
#include <thread>
#include <print>

using std::chrono::high_resolution_clock;
using std::this_thread::sleep_for;

VDMG::VDMG() {
    cpu.set_mmu(&mmu);
    ppu.set_mmu(&mmu);
    reset();
}

void VDMG::load_rom(const std::string& filename) {
    mmu.load_rom(filename);
}

void VDMG::reset() {
    mmu.reset();
}

void VDMG::run() {
    auto frame_start_time = high_resolution_clock::now();

    while (true) {
        curr_frame_cycles -= cycles_per_frame;

        while (curr_frame_cycles < cycles_per_frame) {
            int cycles = cpu.step();

            mmu.sync_timers(cycles);
            ppu.sync_ppu(cycles);
            // sync_apu(cycles);

            curr_frame_cycles += cycles;
        }

        // read_joypad();
        // push_video();
        // push_audio();

        auto frame_end_time = high_resolution_clock::now();
        auto time_elapsed = frame_end_time - frame_start_time;
        
        if (time_elapsed < target_frame_time) {
            sleep_for(target_frame_time - time_elapsed);
        }

        frame_start_time = high_resolution_clock::now();
    }
}