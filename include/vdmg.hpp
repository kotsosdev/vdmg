#pragma once

#include "./cpu.hpp"
#include "./mmu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    public:

    private:
        CPU cpu{};
        MMU mmu{};
};