#include "ppu.hpp"

#include "constants.hpp"

#include <SDL.h>

void PPU::push_video() {
    SDL_UpdateTexture(
        texture,
        nullptr,
        rgba_buffer.data(),
        constants::SCREEN_WIDTH * sizeof(uint32_t)
    );
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}