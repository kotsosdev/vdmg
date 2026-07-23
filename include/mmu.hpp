#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <chrono>

class RTC {
    public:
        uint8_t read();             /// Read latch or live clock
        void write(uint8_t val);    /// Write to live clock
        void latch();               /// Cache current clock

        void set_latch_armed(bool latch_armed) {this->latch_armed = latch_armed;}
        void set_latched(bool latched) {this->latched = latched;}
        void set_enabled(bool enabled) {this->enabled = enabled;}
        void set_bank(uint8_t bank) {this->bank = bank;}

        bool is_latch_armed() {return latch_armed;}
        bool is_latched() {return latched;}
        bool is_enabled() {return enabled;}

    private:
        uint8_t cache_secs{};   /// 0x08
        uint8_t cache_mins{};   /// 0x09
        uint8_t cache_hrs{};    /// 0x0a
        uint8_t cache_dl{};     /// 0x0b
        uint8_t cache_dh{};     /// 0x0c

        uint8_t latch_secs{};   /// 0x08
        uint8_t latch_mins{};   /// 0x09
        uint8_t latch_hrs{};    /// 0x0a
        uint8_t latch_dl{};     /// 0x0b
        uint8_t latch_dh{};     /// 0x0c

        bool latch_armed{};
        bool latched{};
        bool enabled{};
        uint8_t bank{};

        std::chrono::time_point<std::chrono::system_clock> last_sync_timestamp = std::chrono::system_clock::now();

        void sync_clock(); /// Just in time
};

struct Header {
    std::string title{};        /// 0x0134 - 0x0142
    uint8_t cgb_flag{};         /// 0x0143
    uint8_t sgb_flag{};         /// 0x0146
    uint8_t cart_type{};        /// 0x0147
    uint8_t rom_size{};         /// 0x0148
    uint8_t sram_size{};        /// 0x0149
    uint8_t header_checksum{};  /// 0x014d
    uint16_t global_checksum{}; /// 0x014e - 0x014f
};

class MMU {
    public:
        void sync_timers(int cycles);
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t val);
        void write(uint16_t addr, uint16_t val);
        void load_rom(const std::string& filename);
        void reset();
        uint8_t direct_read(uint16_t addr) const;       /// Hardware read
        void direct_write(uint16_t addr, uint8_t val);  /// Hardware write

        void set_buttons_state(uint8_t buttons_state) {this->buttons_state = buttons_state & 0x0f;}
        void set_dpad_state(uint8_t dpad_state) {this->dpad_state = dpad_state & 0x0f;}

        uint8_t get_buttons_state() {return buttons_state;}
        uint8_t get_dpad_state() {return dpad_state;}

    private:
        std::vector<uint8_t> rom{};             /// ROM: 0x0000 - 0x7fff (0x4000 * n banks)
        std::array<uint8_t, 0x2000 * 2> vram{}; /// Video RAM: 0x8000 - 0x9fff (0x2000 * 2 banks)
        std::vector<uint8_t> sram{};            /// External RAM: 0xa000 - 0xbfff (0x2000 * n banks)
        std::array<uint8_t, 0x1000 * 8> wram{}; /// Work RAM: 0xc000 - 0xdfff (0x1000 * 8 banks)
        std::array<uint8_t, 0xa0> oam{};        /// Object attribute memory: 0xfe00 - 0xfe9f
        std::array<uint8_t, 0x80> io{};         /// IO registers: 0xff00 - 0xff7f
        std::array<uint8_t, 0x7f> hram{};       /// High RAM: 0xff80 - 0xfffe
        uint8_t ie{};                           /// Interrupt enable: 0xffff

        int running_div_cycles{0};
        int running_tima_cycles{0};

        uint8_t buttons_state{0x0f};
        uint8_t dpad_state{0x0f};

        uint16_t rom_bank{1}; /// 1 - n
        uint8_t sram_bank{0}; /// 0 - n
        uint8_t vram_bank{0}; /// 0 - 1
        uint8_t wram_bank{1}; /// 1 - 7

        uint8_t bank_reg1{0}; /// 5 bits
        uint8_t bank_reg2{0}; /// 2 bits, dual purpose
        bool banking_mode{false};

        RTC rtc{};

        bool sram_enabled{};

        Header header{};

        uint8_t read_io(uint16_t addr) const;
        void write_io(uint16_t addr, uint8_t val);

        void read_header();
        bool verify_rom();

        void mbc_intercept(uint16_t addr, uint8_t val);
};