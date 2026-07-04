#include "../include/vdmg.hpp"

VDMG::VDMG() {
    bus.apu = &apu;
    bus.cpu = &cpu;
    bus.ppu = &ppu;
}