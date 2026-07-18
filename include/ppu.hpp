#pragma once

#include "./mmu.hpp"

#include <cstdint>
#include <array>

class PPU {
    public:
        void sync_ppu(int cycles);
        void set_mmu(MMU* mmu);

    private:
        MMU* mmu{};

        std::array<uint8_t, 160 * 144> frame{}; /// Frame buffer: (LY * 160) + x

        int running_ppu_cycles{0};

        void oam_scan();
        void draw_pixels();
        void lyc_coincidence();
};