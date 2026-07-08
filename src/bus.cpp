#include "../include/bus.hpp"

#include "../include/cartridge/cartridge.hpp"
#include "../include/apu/apu.hpp"
#include "../include/cpu/cpu.hpp"
#include "../include/ppu/ppu.hpp"

#include <cstdint>
#include <iostream>

using std::cerr;
using std::hex;
using std::dec;
using std::endl;

Bus::Bus(Cartridge* cart, APU* apu, CPU* cpu, PPU* ppu) :
    cart{cart},
    apu{apu},
    cpu{cpu},
    ppu{ppu}
{}

// TODO: Handle side effects
uint8_t Bus::read(uint16_t addr) {
    if (addr <= 0x7fff) {
        return cart->read(addr);

    } else if (addr <= 0x9fff) {
        return ppu->read(addr);

    } else if (addr <= 0xbfff) {
        return cart->read(addr);

    } else if (addr <= 0xdfff) {
        return wram[addr - 0xc000];

    } else if (addr <= 0xfdff) {
        return wram[(addr - 0xc000) - 0x2000];

    } else if (addr <= 0xfe9f) {
        return ppu->read(addr);

    } else if (addr <= 0xfeff) {
        cerr << "Attempted to read unusable memory (" << hex << addr << dec << ")" << endl;
        return 0xff;

    } else if (addr <= 0xff7f) {
        
        if (addr <= 0xff0f) {
            return io[addr - 0xff00];

        } else if (addr <= 0xff26) {
            return apu->read(addr);

        } else if (addr <= 0xff29) {
            cerr << "Attempted to read unusable memory (" << hex << addr << dec << ")" << endl;
            return 0xff;

        } else if (addr <= 0xff3f) {
            return apu->read(addr);
        
        } else if (addr <= 0xff45) {
            return ppu->read(addr);

        } else if (addr == 0xff46) {
            return dma;

        } else if (addr <= 0xff4b) {
            return ppu->read(addr);

        } else if (addr <= 0xff4f) {
            cerr << "Attempted to read unusable memory (" << hex << addr << dec << ")" << endl;
            return 0xff;

        } else if (addr == 0xff50) {
            return boot;
        
        } else if (addr <= 0xff7f) {
            cerr << "Attempted to read unusable memory (" << hex << addr << dec << ")" << endl;
            return 0xff;
        }

    } else if (addr <= 0xfffe) {
        return hram[addr - 0xff80];
    
    } else if (addr == 0xffff) {
        return ie;
    }

    return 0xff;
}

void Bus::write(uint16_t addr, uint8_t val) {
    if (addr <= 0x7fff) {
        cart->write(addr, val);

    } else if (addr <= 0x9fff) {
        ppu->write(addr, val);

    } else if (addr <= 0xbfff) {
        cart->write(addr, val);

    } else if (addr <= 0xdfff) {
        wram[addr - 0xc000] = val;

    } else if (addr <= 0xfdff) {
        wram[(addr - 0xc000) - 0x2000] = val;

    } else if (addr <= 0xfe9f) {
        ppu->write(addr, val);

    } else if (addr <= 0xfeff) {
        cerr << "Attempted to write to unusable memory (" << hex << addr << dec << ")" << endl;

    } else if (addr <= 0xff7f) {
        
        if (addr <= 0xff0f) {
            io[addr - 0xff00] = val;

        } else if (addr <= 0xff26) {
            apu->write(addr, val);

        } else if (addr <= 0xff29) {
            cerr << "Attempted to write to unusable memory (" << hex << addr << dec << ")" << endl;

        } else if (addr <= 0xff3f) {
            apu->write(addr, val);
        
        } else if (addr <= 0xff45) {
            ppu->write(addr, val);

        } else if (addr == 0xff46) {
            dma = val;

        } else if (addr <= 0xff4b) {
            ppu->write(addr, val);

        } else if (addr <= 0xff4f) {
            cerr << "Attempted to write to unusable memory (" << hex << addr << dec << ")" << endl;

        } else if (addr == 0xff50) {
            boot = val;
        
        } else if (addr <= 0xff7f) {
            cerr << "Attempted to write to unusable memory (" << hex << addr << dec << ")" << endl;
        }

    } else if (addr <= 0xfffe) {
        hram[addr - 0xff80] = val;
    
    } else if (addr == 0xffff) {
        ie = val;
    }
}

// TODO: Implement 16 bit write
void Bus::write(uint16_t addr, uint16_t val) {

}