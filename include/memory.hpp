#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <string>

struct Header {
    std::string game_title{}; /// 0x0134 - 0x0142
    uint8_t cgb_flag{}; /// 0x0143
    uint8_t sgb_flag{}; /// 0x0146
    uint8_t cart_type{}; /// 0x0147
    uint8_t header_cs{}; /// 0x014d
    uint16_t global_cs{}; /// 0x014e - 0x014f
};

class Memory {
    public:
        uint8_t read(uint16_t addr) const;
        void write(uint16_t addr, uint8_t val);
        void write(uint16_t addr, uint16_t val);

        void load_rom(const std::string& filename);

    private:
        std::vector<uint8_t> rom{}; /// 0x0000 - 0x7fff (0x4000 * n banks)
        std::array<uint8_t, 0x2000 * 2> vram{}; /// 0x8000 - 0x9fff (0x2000 * 2 banks)
        std::vector<uint8_t> sram{}; /// 0xa000 - 0xbfff (0x2000 * n banks)
        std::array<uint8_t, 0x1000 * 8> wram{}; /// 0xc000 - 0xdfff (0x1000 * 8 banks)
        std::array<uint8_t, 0xa0> oam{}; /// 0xfe00 - 0xfe9f
        std::array<uint8_t, 0x80> io{}; /// 0xff00 - 0xff7f
        std::array<uint8_t, 0x7f> hram{}; /// 0xff80 - 0xfffe
        uint8_t ie{}; /// 0xffff

        uint16_t rom_bank{1}; /// 1 - n
        uint8_t sram_bank{0}; /// 0 - n
        uint8_t vram_bank{0}; /// 0 - 1
        uint8_t wram_bank{1}; /// 1 - 7

        bool ram_enabled{};

        Header header;
        void read_header();

        void mbc_intercept(uint16_t addr, uint8_t val);
        uint8_t ppu_mode() const;
};