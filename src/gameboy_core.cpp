#include "../include/gameboy.hpp"

#include <string>
#include <iostream>
#include <fstream>

using std::string;

using std::cout;
using std::cerr;

using std::ifstream;
using std::ios;
using std::streampos;

GameBoy::GameBoy() {

}

void GameBoy::load_rom(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    
    if (file.is_open()) {
        streampos size = file.tellg();
    }
}