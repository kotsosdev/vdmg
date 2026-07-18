#include "../include/vdmg.hpp"

#include <iostream>

int main() {
    VDMG vdmg;
    vdmg.load_rom("roms\\cpu_instrs.gb");
    vdmg.run();
}