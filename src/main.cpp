#include "../include/vdmg.hpp"

#include <iostream>
#include <print>
#include <string>

using std::cin;

using std::print;
using std::println;

using std::string;

int main() {
    VDMG vdmg;

    string filename;
    print("ROM filename: ");
    cin >> filename;
    println();

    vdmg.load_rom(filename);
    vdmg.run();
}