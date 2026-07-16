#pragma once

#include "./cpu.hpp"
#include "./mmu.hpp"

#include <string>
#include <cstdint>

class vdmg {
    public:

    private:
        CPU cpu{};
        MMU mmu{};
};