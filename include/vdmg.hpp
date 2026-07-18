#pragma once

#include "./cpu.hpp"
#include "./mmu.hpp"

#include <string>
#include <cstdint>
#include <chrono>

class VDMG {
    public:
        VDMG();

        void load_rom(const std::string& filename);
        void reset();
        void run();

    private:
        CPU cpu{};
        MMU mmu{};

        std::chrono::duration<double, std::milli> target_frame_time{16.7427};
        int cycles_per_frame{70224};
        int curr_frame_cycles{};
};