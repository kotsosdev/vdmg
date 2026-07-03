#include "../include/vdmg.hpp"

VDMG::VDMG() {
    bus.apu = &apu;
    bus.cpu = &cpu;
    bus.mmu = &mmu;
    bus.ppu = &ppu;
}