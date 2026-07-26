#include "apu.hpp"

#include <SDL.h>

void APU::push_audio() {
    SDL_QueueAudio(audio_device, sample_buffer.data(), sample_buffer.size() * sizeof(*sample_buffer.data()));
    sample_buffer.clear();
}