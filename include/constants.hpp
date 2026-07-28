#pragma once

#include <cstdint>
#include <array>

namespace constants {
    // Config audio
    inline constexpr int VOLUME_SCALE = 500; // 0 - 618

    // Config video
    inline constexpr int SCREEN_SCALE = 5;
    inline constexpr std::array<uint32_t, 4> PALETTE = {
        0xffffffff, 0xc0c0c0ff, 0x606060ff, 0x000000ff   // Monochrome gray
    };

    // Hardware
    inline constexpr int SCREEN_WIDTH = 160;
    inline constexpr int SCREEN_HEIGHT = 144;
    inline constexpr int CPU_CLOCK_HZ = 4194304;
    inline constexpr int CYCLES_PER_FRAME = 70224; 
    inline constexpr double FPS = static_cast<double>(CPU_CLOCK_HZ) / CYCLES_PER_FRAME;
    inline constexpr double FRAME_TIME_MS = 1000.0 / FPS;
    inline constexpr std::array<bool, 32> duty_table = {
        0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0
    };

    // Misc
    inline constexpr std::array<uint8_t, 48> LOGO = {
        0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
        0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
        0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63,
        0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e
    };
}