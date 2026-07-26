#pragma once

#include "mmu.hpp"

#include <SDL.h>
#include <cstdint>
#include <vector>

class APU {
    public:
        void sync_apu(int cycles);
        void push_audio();

        void set_mmu(MMU* mmu) {this->mmu = mmu;}
        void set_audio_device(SDL_AudioDeviceID audio_device) {this->audio_device = audio_device;}

    private:
        MMU* mmu{};

        SDL_AudioDeviceID audio_device{};

        bool muted{};

        int running_apu_cycles;

        std::vector<int16_t> sample_buffer{};

        uint8_t get_ch1_amp();
        uint8_t get_ch2_amp();
        uint8_t get_ch3_amp();
        uint8_t get_ch4_amp();
};