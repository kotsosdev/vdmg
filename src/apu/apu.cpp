#include "apu.hpp"

#include "constants.hpp"

void APU::sync_apu(int cycles) {
    if (muted) return;

    running_apu_cycles += cycles;

    while (running_apu_cycles >= 95) {
        int32_t left_sum = 0;
        int32_t right_sum = 0;

        // TODO: Flip (*-1) logic for each channel
        int8_t ch1 = static_cast<int8_t>(get_ch1_amp()); // Duty table
        int8_t ch2 = static_cast<int8_t>(get_ch2_amp()); // Duty table
        int8_t ch3 = static_cast<int8_t>(get_ch3_amp()) - 8;
        int8_t ch4 = static_cast<int8_t>(get_ch4_amp()); // Bit 0 LFSR

        uint8_t nr51 = mmu->direct_read(0xff25);

        if (nr51 & 0x10) left_sum += ch1;
        if (nr51 & 0x20) left_sum += ch2;
        if (nr51 & 0x40) left_sum += ch3;
        if (nr51 & 0x80) left_sum += ch4;

        if (nr51 & 0x01) right_sum += ch1;
        if (nr51 & 0x02) right_sum += ch2;
        if (nr51 & 0x04) right_sum += ch3;
        if (nr51 & 0x08) right_sum += ch4;

        int16_t left_sample = (
            static_cast<int16_t>(left_sum) *
            static_cast<int16_t>(constants::VOLUME_SCALE)
        );

        int16_t right_sample = (
            static_cast<int16_t>(right_sum) *
            static_cast<int16_t>(constants::VOLUME_SCALE)
        );

        sample_buffer.push_back(left_sample);
        sample_buffer.push_back(right_sample);

        running_apu_cycles -= 95;
    }
}

uint8_t APU::get_ch1_amp() {

}

uint8_t APU::get_ch2_amp() {

}

uint8_t APU::get_ch3_amp() {

}

uint8_t APU::get_ch4_amp() {

}