#include "ppu.hpp"

#include "config.hpp"
#include <SDL.h>

using namespace config;

void PPU::push_video() {
    SDL_UpdateTexture(
        texture,
        nullptr,
        rgba_buffer.data(),
        SCREEN_WIDTH * sizeof(uint32_t)
    );
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}