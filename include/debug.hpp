#pragma once

#include <string_view>
#include <iostream>
#include <cstdint>

inline void log(std::string_view msg) {
    std::cerr << msg << '\n';
}

inline void log(std::string_view msg, uint16_t val) {
    std::cerr << msg << " (0x" << std::hex << val << std::dec << ")\n";
}

inline void print(std::string_view msg) {
    std::cout << msg << std::endl;
}

inline void print(std::string_view msg, uint16_t val) {
    std::cout << msg << " (0x" << std::hex << val << std::dec << ")\n";
}