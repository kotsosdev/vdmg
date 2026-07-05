#include "../include/vdmg.hpp"

VDMG::VDMG() :
    bus{&cart, &apu, &cpu, &ppu}
{
    cpu.set_bus(&bus);
}