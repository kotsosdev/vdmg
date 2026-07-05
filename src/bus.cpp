#include "../include/bus.hpp"

Bus::Bus(Cartridge* cart, APU* apu, CPU* cpu, PPU* ppu) :
    cart{cart},
    apu{apu},
    cpu{cpu},
    ppu{ppu}
{}

uint8_t Bus::read(uint16_t addr) {

}

void Bus::write(uint16_t addr, uint8_t val) {

}

void Bus::write(uint16_t addr, uint16_t val) {

}