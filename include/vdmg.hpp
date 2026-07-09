#pragma once

#include "./memory.hpp"
#include "./cpu/cpu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    public:

    private:
        Memory memory{};
        CPU cpu{};
};