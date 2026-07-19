#pragma once

#include "./mmu.hpp"

#include <cstdint>
#include <array>

struct Sprite {
    uint8_t y;      /// y position
    uint8_t x;      /// x position
    uint8_t tile_i; /// Tile index
    uint8_t attrs;  /// Attributes
    uint8_t oam_i;  /// Object attribute memory index
};

class PPU {
    public:
        void sync_ppu(int cycles);
        void set_mmu(MMU* mmu);
        
        bool is_headless() const {return headless;}

    private:
        MMU* mmu{};

        std::array<uint8_t, 160 * 144> frame_buffer{};  /// Frame buffer: (LY * 160) + x
        std::vector<Sprite> sprite_buffer{};            /// Sprites for current LY

        bool headless{};
        int running_ppu_cycles{0};

        void oam_scan();
        void draw_pixels();
        void lyc_coincidence();
};