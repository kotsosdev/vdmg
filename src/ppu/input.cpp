#include "ppu.hpp"

#include <SDL.h>

bool PPU::read_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;

        if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
            uint8_t b = mmu->get_buttons_state();
            uint8_t d = mmu->get_dpad_state();
            uint8_t new_state = event.type == SDL_KEYUP;

            switch (event.key.keysym.sym) {
                case SDLK_x: mmu->set_buttons_state((b & 0b1110) | new_state); break;               // A
                case SDLK_z: mmu->set_buttons_state((b & 0b1101) | (new_state << 1)); break;        // B
                case SDLK_RSHIFT: mmu->set_buttons_state((b & 0b1011) | (new_state << 2)); break;   // Select
                case SDLK_RETURN: mmu->set_buttons_state((b & 0b0111) | (new_state << 3)); break;   // Start
                
                case SDLK_RIGHT: mmu->set_dpad_state((d & 0b1110) | new_state); break;              // Right
                case SDLK_LEFT: mmu->set_dpad_state((d & 0b1101) | (new_state << 1)); break;        // Left
                case SDLK_UP: mmu->set_dpad_state((d & 0b1011) | (new_state << 2)); break;          // Up
                case SDLK_DOWN: mmu->set_dpad_state((d & 0b0111) | (new_state << 3)); break;        // Down
            }
        }
    }

    return true;
}