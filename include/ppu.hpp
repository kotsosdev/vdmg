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
        
        void set_mmu(MMU* mmu) {this->mmu = mmu;}
        void set_headless(bool headless) {this->headless = headless;}
        
        bool is_headless() const {return headless;}

    private:
        MMU* mmu{};

        std::array<uint32_t, 160 * 144> rgba_buffer{};
        std::array<uint8_t, 160 * 144> bgw_pixel_buffer{};
        std::array<uint32_t, 4> palette{
            0xffffffff,
            0xc0c0c0ff,
            0x606060ff,
            0x000000ff
        };

        std::vector<Sprite> sprite_buffer{};            /// Sprites for current LY

        bool headless{};
        int running_ppu_cycles{0};

        void oam_scan();
        void draw_pixels();
        void lyc_coincidence();
};