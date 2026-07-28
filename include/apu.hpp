#pragma once

#include "mmu.hpp"

#include <SDL.h>
#include <cstdint>
#include <vector>

struct Channel {
    // All channels
    bool enabled{};
    uint8_t length_timer{};
    int freq_cycles{};
    int period{};

    // Channels 1 and 2
    uint8_t duty_cycle{};
    uint8_t duty_step{};

    // Channel 3
    uint8_t wave_step{};

    // Channel 4
    uint16_t lfsr{};
};

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

        int sample_cycles{};
        
        int frame_counter_cycles{};
        int frame_counter{};

        Channel ch1{};
        Channel ch2{};
        Channel ch3{};
        Channel ch4{};

        std::vector<int16_t> sample_buffer{};

        void sync_length_counters();    /// 256 Hz
        void sync_freq_sweep();         /// 128 Hz
        void sync_volume_envelopes();   /// 65 Hz

        int16_t get_ch1_sample();
        int16_t get_ch2_sample();
        int16_t get_ch3_sample();
        int16_t get_ch4_sample();
};