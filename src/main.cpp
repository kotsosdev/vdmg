#include "../include/vdmg.hpp"

#include <iostream>

int main() {
    VDMG vdmg;
    vdmg.load_rom("roms\\interrupt_time.gb");
    vdmg.run();
}