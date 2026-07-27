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

        int running_apu_cycles{};
        
        int frame_seq_cycles{};
        int frame_seq{};

        int ch1_freq_timer{};
        int ch2_freq_timer{};
        int ch3_freq_timer{};
        int ch4_freq_timer{};

        int ch1_duty_cycle{};
        int ch2_duty_cycle{};
        int ch1_duty_step{};
        int ch2_duty_step{};

        std::vector<int16_t> sample_buffer{};

        uint8_t get_ch1_amp();
        uint8_t get_ch2_amp();
        uint8_t get_ch3_amp();
        uint8_t get_ch4_amp();
};