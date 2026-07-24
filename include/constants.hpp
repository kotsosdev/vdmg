#pragma once

#include <cstdint>
#include <array>

namespace constants {
    // Display config
    inline constexpr int SCREEN_SCALE = 5;
    inline constexpr std::array<uint32_t, 4> PALETTE = {
        0xffffffff,
        0xc0c0c0ff,
        0x606060ff,
        0x000000ff
    };

    // Specs
    inline constexpr int SCREEN_WIDTH = 160;
    inline constexpr int SCREEN_HEIGHT = 144;
    inline constexpr uint32_t CPU_CLOCK_HZ = 4194304;
    inline constexpr double FPS = 59.7275;
    inline constexpr double FRAME_TIME_MS = 1000.0 / FPS;
    inline constexpr uint32_t CYCLES_PER_FRAME = static_cast<uint32_t>(CPU_CLOCK_HZ / FPS);
}