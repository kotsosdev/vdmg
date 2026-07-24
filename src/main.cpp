#include "vdmg.hpp"

#include "constants.hpp"

#include <SDL.h>
#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::cerr;
using std::exception;

// TODO: Move SDL initiation and destruction logic into VDMG (RAII)
int main(int argc, char* argv[]) {
    string rom_path = "";
    if (argc > 1) rom_path = argv[1];

    SDL_Window* root = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Failed to initialize SDL: " << SDL_GetError() << '\n'; 
        return 1;
    }

    root = SDL_CreateWindow(
        "vdmg",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        constants::SCREEN_WIDTH * constants::SCREEN_SCALE, constants::SCREEN_HEIGHT * constants::SCREEN_SCALE,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (root == nullptr) {
        cerr << "Failed to initialize SDL window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        root,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr) {
        cerr << "Failed to initialize SDL renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(root);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        constants::SCREEN_WIDTH,
        constants::SCREEN_HEIGHT
    );

    if (texture == nullptr) {
        cerr << "Failed to initialize SDL texture: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(root);
        SDL_Quit();
        return 1;
    }

    try {
        VDMG vdmg(
            rom_path,
            renderer,
            texture
        );

        // TODO: Edit the window here

        vdmg.run();

    } catch (const exception& e) {
        cerr << "Emulator crashed: " << e.what() << '\n';
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(root);
        SDL_Quit();
        return 1;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(root);
    SDL_Quit();

    return 0;
}