#include "apu.hpp"

#include "constants.hpp"

void APU::sync_apu(int cycles) {
    if (muted) return;

    running_apu_cycles += cycles;
    frame_seq_cycles += cycles;

    // TODO: Use accumulators to match variable style above
    ch1_freq_timer -= cycles;
    ch2_freq_timer -= cycles;
    // ch3_freq_timer -= cycles;
    // ch4_freq_timer -= cycles;

    while (frame_seq_cycles >= 8192) {
        frame_seq = (frame_seq + 1) & 0x07;
        frame_seq_cycles -= 8192;
    }

    while (ch1_freq_timer <= 0) {
        ch1_duty_step = (ch1_duty_step + 1) & 0x07;

        uint8_t nr13 = mmu->direct_read(0xff13);
        uint8_t nr14 = mmu->direct_read(0xff14);
        uint16_t freq = ((nr14 & 0x07) << 8) | nr13;

        ch1_freq_timer = ((2048 - freq) * 4) + ch1_freq_timer;
    }

    while (ch2_freq_timer <= 0) {
        ch2_duty_step = (ch2_duty_step + 1) & 0x07;

        uint8_t nr23 = mmu->direct_read(0xff23);
        uint8_t nr24 = mmu->direct_read(0xff24);
        uint16_t freq = ((nr24 & 0x07) << 8) | nr23;

        ch2_freq_timer = ((2048 - freq) * 4) + ch2_freq_timer;
    }

    // while (ch3_freq_timer <= 0) {

    // }

    // while (ch4_freq_timer <= 0) {

    // }

    while (running_apu_cycles >= 95) {
        int32_t left_sum = 0;
        int32_t right_sum = 0;

        uint8_t ch1 = get_ch1_amp();
        uint8_t ch2 = get_ch2_amp();
        uint8_t ch3 = get_ch3_amp();
        uint8_t ch4 = get_ch4_amp();

        uint8_t nr51 = mmu->direct_read(0xff25);

        if (nr51 & 0x10) left_sum += ch1;
        if (nr51 & 0x20) left_sum += ch2;
        if (nr51 & 0x40) left_sum += ch3;
        if (nr51 & 0x80) left_sum += ch4;

        if (nr51 & 0x01) right_sum += ch1;
        if (nr51 & 0x02) right_sum += ch2;
        if (nr51 & 0x04) right_sum += ch3;
        if (nr51 & 0x08) right_sum += ch4;

        // HACK: -30 center shift
        int16_t left_sample = (
            static_cast<int16_t>(left_sum - 30) *
            static_cast<int16_t>(constants::VOLUME_SCALE)
        );

        // HACK: Same as above
        int16_t right_sample = (
            static_cast<int16_t>(right_sum - 30) *
            static_cast<int16_t>(constants::VOLUME_SCALE)
        );

        sample_buffer.push_back(left_sample);
        sample_buffer.push_back(right_sample);

        running_apu_cycles -= 95;
    }
}

uint8_t APU::get_ch1_amp() {
    uint8_t nr11 = mmu->direct_read(0xff11);
    uint8_t nr12 = mmu->direct_read(0xff12);

    uint8_t res = (nr12 >> 4) & 0x0f;

    return constants::duty_table[(((nr11 >> 6) & 0x03) * 8) + ch1_duty_step] ? res : 0;
}

uint8_t APU::get_ch2_amp() {
    uint8_t nr21 = mmu->direct_read(0xff16);
    uint8_t nr22 = mmu->direct_read(0xff17);
    
    uint8_t res = (nr22 >> 4) & 0x0f;

    return constants::duty_table[(((nr21 >> 6) & 0x03) * 8) + ch2_duty_step] ? res : 0;
}

uint8_t APU::get_ch3_amp() {
    uint8_t res = 0;
    return res;
}

uint8_t APU::get_ch4_amp() {
    uint8_t res = 0;
    return res;
}