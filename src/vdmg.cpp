#include "vdmg.hpp"

#include <iostream>
#include <string>
#include <SDL.h>
#include <chrono>
#include <thread>

using std::cerr;
using std::string;
using std::chrono::high_resolution_clock;
using std::this_thread::sleep_for;

VDMG::VDMG(const string& rom_path, const string& sav_path) :
    rom_path{rom_path},
    sav_path{sav_path}
{
    cpu.set_mmu(&mmu);
    ppu.set_mmu(&mmu);
    apu.set_mmu(&mmu);
    mmu.set_apu(&apu);

    mmu.load_rom(rom_path);
    mmu.load_sav(sav_path);

    cpu.skip_boot();
    mmu.skip_boot();

    init_media();
}

VDMG::~VDMG() {
    mmu.save_sav(sav_path);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(audio_device);
    SDL_Quit();
}

void VDMG::run() {
    auto frame_start_time = high_resolution_clock::now();

    while (true) {
        while (curr_frame_cycles < cycles_per_frame) {
            int cycles = cpu.step();

            mmu.sync_timers(cycles);
            ppu.sync_ppu(cycles);
            apu.sync_apu(cycles);

            curr_frame_cycles += cycles;
        }

        curr_frame_cycles -= cycles_per_frame;

        if (!ppu.read_input()) break;
        ppu.push_video();
        apu.push_audio();

        auto frame_end_time = high_resolution_clock::now();
        auto time_elapsed = frame_end_time - frame_start_time;
        // HACK: Busy wait
        while (high_resolution_clock::now() - frame_start_time < frame_time) {}

        frame_start_time = high_resolution_clock::now();
    }
}

// TODO: Throw exception or flip a bool on failure
void VDMG::init_media() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cerr << "Failed to initialize SDL: " << SDL_GetError() << '\n'; 
        return;
    }

    window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        constants::SCREEN_WIDTH * constants::SCREEN_SCALE, constants::SCREEN_HEIGHT * constants::SCREEN_SCALE,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (window == nullptr) {
        cerr << "Failed to initialize SDL window: " << SDL_GetError() << '\n';
        return;
    }

    SDL_SetWindowTitle(window, mmu.get_header().title.c_str());

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (renderer == nullptr) {
        cerr << "Failed to initialize SDL renderer: " << SDL_GetError() << '\n';
        return;
    }

    ppu.set_renderer(renderer);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        constants::SCREEN_WIDTH,
        constants::SCREEN_HEIGHT
    );
    if (texture == nullptr) {
        cerr << "Failed to initialize SDL texture: " << SDL_GetError() << '\n';
        return;
    }

    ppu.set_texture(texture);

    SDL_AudioSpec desired{};
    SDL_AudioSpec obtained{};
    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = 2048;

    audio_device = SDL_OpenAudioDevice(
        nullptr,
        0,
        &desired,
        &obtained,
        0
    );
    if (audio_device == 0) {
        cerr << "Failed to initialize SDL audio device: " << SDL_GetError() << '\n';
        return;
    }

    SDL_PauseAudioDevice(audio_device, 0);

    apu.set_audio_device(audio_device);

    return;
}