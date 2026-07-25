#include "vdmg.hpp"
#include "constants.hpp"

#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::cerr;
using std::exception;

int main(int argc, char* argv[]) {
    string rom_path = "";
    string sav_path = "";

    if (argc == 2) {
        rom_path = argv[1];

        size_t ext_i = rom_path.rfind('.');
        sav_path = (ext_i != string::npos) ? rom_path.substr(0, ext_i) : rom_path;
        sav_path += ".sav";

    } else if (argc == 3) {
        rom_path = argv[1];
        sav_path = argv[2];

    } else {
        cerr << "Usage: " << argv[0] << " <rom_path> [sav_path]\n";
        return 1;
    }

    try {
        VDMG vdmg(rom_path, sav_path);
        vdmg.run();

    } catch (const exception& e) {
        cerr << "Crashed: " << e.what() << '\n';
        return 1;
    }

    return 0;
}