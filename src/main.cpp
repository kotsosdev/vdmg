#include "../include/vdmg.hpp"

#include <string>

using std::string;

int main(int argc, char* argv[]) {
    string filename = "";
    if (argc > 1 && argv[1] != nullptr) filename = argv[1];

    VDMG vdmg;
    vdmg.load_rom(filename);
    vdmg.run();
}