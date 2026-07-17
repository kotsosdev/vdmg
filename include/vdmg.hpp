#pragma once

#include "./cpu.hpp"
#include "./mmu.hpp"

#include <string>
#include <cstdint>

class VDMG {
    public:
        void run();

    private:
        CPU cpu{};
        MMU mmu{};
};