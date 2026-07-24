#pragma once

#include "constants.hpp"
#include "mmu.hpp"

#include <SDL.h>
#include <cstdint>
#include <array>

struct Sprite {
    uint8_t y;
    uint8_t x;
    uint8_t tile_i;
    uint8_t attrs;
    uint8_t oam_i;
};

class PPU {
    public:
        void sync_ppu(int cycles);
        bool read_input();
        void push_video();
        
        void set_mmu(MMU* mmu) {this->mmu = mmu;}
        void set_renderer(SDL_Renderer* renderer) {this->renderer = renderer;}
        void set_texture(SDL_Texture* texture) {this->texture = texture;}
        void set_headless(bool headless) {this->headless = headless;}
        void set_palette(int i, uint32_t rgba) {this->palette.at(i) = rgba;}
        void set_palette(std::array<uint32_t, 4> palette) {this->palette = palette;}
        
        bool is_headless() const {return headless;}

    private:
        MMU* mmu{};

        SDL_Renderer* renderer{};
        SDL_Texture* texture{};

        bool headless{};
        int running_ppu_cycles{};

        int running_window_line{};

        std::array<uint32_t, constants::SCREEN_WIDTH * constants::SCREEN_HEIGHT> rgba_buffer{};
        std::array<uint8_t, constants::SCREEN_WIDTH * constants::SCREEN_HEIGHT> bgw_pixel_buffer{};

        std::array<uint32_t, constants::PALETTE.size()> palette{constants::PALETTE};

        std::vector<Sprite> sprite_buffer{};

        void oam_scan();
        void draw_pixels();
        void lyc_coincidence();
};