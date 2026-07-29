#include "apu.hpp"

#include "constants.hpp"

void Channel::trigger(MMU* mmu) {
    switch (channel) {
        case 1: {
            uint8_t nr10 = mmu->direct_read(0xff10);
            uint8_t nr12 = mmu->direct_read(0xff12);
            uint8_t nr13 = mmu->direct_read(0xff13);
            uint8_t nr14 = mmu->direct_read(0xff14);

            volume = (nr12 >> 4) & 0x0f;

            length_timer = (length_timer == 0) ? 64 : length_timer;

            env_timer = nr12 & 0x07;
            env_timer = (env_timer == 0) ? 8 : env_timer;
            env_volume_inc = (nr12 >> 3) & 0x01;

            sweep_timer = (nr10 >> 4) & 0x07;
            freq_shadow = ((nr14 & 0x07) << 8) | nr13;

            enabled = (volume != 0) || env_volume_inc;
        } break;

        case 2: {
            uint8_t nr22 = mmu->direct_read(0xff17);

            volume = (nr22 >> 4) & 0x0f;

            length_timer = (length_timer == 0) ? 64 : length_timer;

            env_timer = nr22 & 0x07;
            env_timer = (env_timer == 0) ? 8 : env_timer;
            env_volume_inc = (nr22 >> 3) & 0x01;

            enabled = (volume != 0) || env_volume_inc;
        } break;

        case 3: {
            uint8_t nr30 = mmu->direct_read(0xff1a);

            length_timer = (length_timer == 0) ? 256 : length_timer;
            wave_step = 0;

            enabled = (nr30 >> 7) & 0x01;
        } break;

        case 4: {
            uint8_t nr42 = mmu->direct_read(0xff21);

            volume = (nr42 >> 4) & 0x0f;

            length_timer = (length_timer == 0) ? 64 : length_timer;

            env_timer = nr42 & 0x07;
            env_timer = (env_timer == 0) ? 8 : env_timer;
            env_volume_inc = (nr42 >> 3) & 0x01;

            lfsr = 0x7fff;

            enabled = (volume != 0) || env_volume_inc;
        } break;
    }
}

void APU::sync_apu(int cycles) {
    if (muted) return;

    uint8_t nr52 = mmu->direct_read(0xff26);
    bool audio_enabled = (nr52 >> 7) & 0x01;

    if (!audio_enabled) return;

    sample_cycles += cycles;
    frame_counter_cycles += cycles;

    ch1.freq_cycles += cycles;
    ch2.freq_cycles += cycles;
    ch3.freq_cycles += cycles;
    ch4.freq_cycles += cycles;

    while (frame_counter_cycles >= 8192) {
        switch (frame_counter) {
            case 0x0: sync_length_counters(); break;
            case 0x1: break;
            case 0x2: sync_length_counters(); sync_freq_sweep(); break;
            case 0x3: break;
            case 0x4: sync_length_counters(); break;
            case 0x5: break;
            case 0x6: sync_length_counters(); sync_freq_sweep(); break;
            case 0x7: sync_volume_envelopes(); break;

            default: break;
        }

        frame_counter = (frame_counter + 1) & 0x07;
        frame_counter_cycles -= 8192;
    }

    while (ch1.freq_cycles >= ch1.period) {
        ch1.duty_step = (ch1.duty_step + 1) & 0x07;

        uint8_t nr13 = mmu->direct_read(0xff13);
        uint8_t nr14 = mmu->direct_read(0xff14);
        uint16_t freq = ((nr14 & 0x07) << 8) | nr13;

        ch1.freq_cycles -= ch1.period;
        ch1.period = ((2048 - freq) * 4);
    }

    while (ch2.freq_cycles >= ch2.period) {
        ch2.duty_step = (ch2.duty_step + 1) & 0x07;

        uint8_t nr23 = mmu->direct_read(0xff23);
        uint8_t nr24 = mmu->direct_read(0xff24);
        uint16_t freq = ((nr24 & 0x07) << 8) | nr23;

        ch2.freq_cycles -= ch2.period;
        ch2.period = ((2048 - freq) * 4);
    }

    while (ch3.freq_cycles >= ch3.period) {
        ch3.wave_step = (ch3.wave_step + 1) & 0x1f;

        uint8_t nr33 = mmu->direct_read(0xff1d);
        uint8_t nr34 = mmu->direct_read(0xff1e);
        uint16_t freq = ((nr34 & 0x07) << 8) | nr33;

        ch3.freq_cycles -= ch3.period;
        ch3.period = ((2048 - freq) * 2);
    }

    while (ch4.freq_cycles >= ch4.period) {
        uint8_t nr43 = mmu->direct_read(0xff22);

        uint8_t clock_divider_code = nr43 & 0x07;
        uint8_t clock_divider = (clock_divider_code == 0) ? 8 : (clock_divider_code * 16);
        bool lfsr_7_bit = (nr43 >> 3) & 0x01;
        uint8_t clock_shift = (nr43 >> 4) & 0x0f;

        uint8_t feedback = (ch4.lfsr & 0x01) ^ ((ch4.lfsr >> 1) & 0x01);
        ch4.lfsr = ((ch4.lfsr >> 1) & 0xbfff) | (feedback << 14);
        ch4.lfsr = lfsr_7_bit ? ((ch4.lfsr & 0xffbf) | (feedback << 6)) : ch4.lfsr;

        ch4.freq_cycles -= ch4.period;
        ch4.period = clock_divider << clock_shift;
    }

    while (sample_cycles >= 95) {
        int32_t left_sum = 0;
        int32_t right_sum = 0;

        int16_t ch1_sample = get_ch1_sample();
        int16_t ch2_sample = get_ch2_sample();
        int16_t ch3_sample = get_ch3_sample();
        int16_t ch4_sample = get_ch4_sample();

        uint8_t nr51 = mmu->direct_read(0xff25);

        if (nr51 & 0x10) left_sum += ch1_sample;
        if (nr51 & 0x20) left_sum += ch2_sample;
        if (nr51 & 0x40) left_sum += ch3_sample;
        if (nr51 & 0x80) left_sum += ch4_sample;

        if (nr51 & 0x01) right_sum += ch1_sample;
        if (nr51 & 0x02) right_sum += ch2_sample;
        if (nr51 & 0x04) right_sum += ch3_sample;
        if (nr51 & 0x08) right_sum += ch4_sample;

        int16_t left_sample = (static_cast<int16_t>(left_sum) * static_cast<int16_t>(constants::VOLUME_SCALE));
        int16_t right_sample = (static_cast<int16_t>(right_sum) * static_cast<int16_t>(constants::VOLUME_SCALE));

        sample_buffer.push_back(left_sample);
        sample_buffer.push_back(right_sample);

        sample_cycles -= 95;
    }
}

void APU::trigger_channel(int channel) {
    switch (channel) {
        case 1: ch1.trigger(mmu); break;
        case 2: ch2.trigger(mmu); break;
        case 3: ch3.trigger(mmu); break;
        case 4: ch4.trigger(mmu); break;

        default: break;
    }
}

void APU::sync_length_counters() {
    uint8_t nr14 = mmu->direct_read(0xff14);
    uint8_t nr24 = mmu->direct_read(0xff19);
    uint8_t nr34 = mmu->direct_read(0xff1e);
    uint8_t nr44 = mmu->direct_read(0xff23);

    bool ch1_len_ctr_enabled = (nr14 >> 6) & 0x01;
    bool ch2_len_ctr_enabled = (nr24 >> 6) & 0x01;
    bool ch3_len_ctr_enabled = (nr34 >> 6) & 0x01;
    bool ch4_len_ctr_enabled = (nr44 >> 6) & 0x01;

    if (ch1_len_ctr_enabled && (ch1.length_timer > 0) && (--ch1.length_timer == 0)) ch1.enabled = false;
    if (ch2_len_ctr_enabled && (ch2.length_timer > 0) && (--ch2.length_timer == 0)) ch2.enabled = false;
    if (ch3_len_ctr_enabled && (ch3.length_timer > 0) && (--ch3.length_timer == 0)) ch3.enabled = false;
    if (ch4_len_ctr_enabled && (ch4.length_timer > 0) && (--ch4.length_timer == 0)) ch4.enabled = false;
}

void APU::sync_freq_sweep() {
    if ((ch1.sweep_timer > 0) && (--ch1.sweep_timer == 0)) {
        uint8_t nr10 = mmu->direct_read(0xff10);

        uint8_t freq_step = nr10 & 0x07;
        bool freq_sub = (nr10 >> 3) & 0x01;

        uint16_t freq_offset = ch1.freq_shadow >> freq_step;
        uint16_t new_freq = freq_sub ? (ch1.freq_shadow - freq_offset) : (ch1.freq_shadow + freq_offset);

        if (!freq_sub && (new_freq > 2047)) {
            ch1.enabled = false;

        } else {

            if (freq_step) {
                mmu->direct_write(0xff14, static_cast<uint8_t>((mmu->direct_read(0xff14) & 0xf8) | (new_freq >> 8)));
                mmu->direct_write(0xff13, static_cast<uint8_t>(new_freq & 0xff));

                ch1.freq_shadow = new_freq;
            }

            uint16_t next_freq_offset = ch1.freq_shadow >> freq_step;
            uint16_t next_new_freq = freq_sub ? (ch1.freq_shadow - next_freq_offset) : (ch1.freq_shadow + next_freq_offset);

            if (!freq_sub && next_new_freq > 2047) ch1.enabled = false;
            
        }

        ch1.sweep_timer = (nr10 >> 4) & 0x07;
    }
}

void APU::sync_volume_envelopes() {
    uint8_t nr12 = mmu->direct_read(0xff12);
    uint8_t nr22 = mmu->direct_read(0xff17);
    uint8_t nr42 = mmu->direct_read(0xff21);

    ch1.env_volume_inc = (nr12 >> 3) & 0x01;
    ch2.env_volume_inc = (nr22 >> 3) & 0x01;
    ch4.env_volume_inc = (nr42 >> 3) & 0x01;

    ch1.env_pace = nr12 & 0x07;
    ch2.env_pace = nr22 & 0x07;
    ch4.env_pace = nr42 & 0x07;

    if ((ch1.env_timer > 0) && (--ch1.env_timer == 0)) {
        if (ch1.env_pace != 0) {
            if (ch1.env_volume_inc && (ch1.volume < 15)) ++ch1.volume;
            if (!ch1.env_volume_inc && (ch1.volume > 0)) --ch1.volume;
        }

        ch1.env_timer = (ch1.env_pace == 0) ? 8 : ch1.env_pace;
    }

    if ((ch2.env_timer > 0) && (--ch2.env_timer == 0)) {
        if (ch2.env_pace != 0) {
            if (ch2.env_volume_inc && (ch2.volume < 15)) ++ch2.volume;
            if (!ch2.env_volume_inc && (ch2.volume > 0)) --ch2.volume;
        }

        ch2.env_timer = (ch2.env_pace == 0) ? 8 : ch2.env_pace;
    }

    if ((ch4.env_timer > 0) && (--ch4.env_timer == 0)) {
        if (ch4.env_pace != 0) {
            if (ch4.env_volume_inc && (ch4.volume < 15)) ++ch4.volume;
            if (!ch4.env_volume_inc && (ch4.volume > 0)) --ch4.volume;
        }

        ch4.env_timer = (ch4.env_pace == 0) ? 8 : ch4.env_pace;
    }
}

int16_t APU::get_ch1_sample() {
    if (!ch1.enabled) return 0;
    
    uint8_t nr11 = mmu->direct_read(0xff11);

    int16_t sample = constants::duty_table[(((nr11 >> 6) & 0x03) * 8) + ch1.duty_step] ? ch1.volume : -ch1.volume;
    return sample;
}

int16_t APU::get_ch2_sample() {
    if (!ch2.enabled) return 0;

    uint8_t nr21 = mmu->direct_read(0xff16);

    int16_t sample = constants::duty_table[(((nr21 >> 6) & 0x03) * 8) + ch2.duty_step] ? ch2.volume : -ch2.volume;
    return sample;
}

int16_t APU::get_ch3_sample() {
    if (!ch3.enabled) return 0;
    
    uint8_t nr32 = mmu->direct_read(0xff1c);

    uint8_t output_level = (nr32 >> 5) & 0x03;
    int output_shift = 0;
    if (output_level != 0) output_shift = output_level - 1;
    else return 0;

    uint16_t addr = 0xff30 + (ch3.wave_step / 2);
    int16_t sample = (
        (ch3.wave_step % 2 == 0) ?
        (mmu->direct_read(addr) >> 4) :
        (mmu->direct_read(addr) & 0x0f)
    );

    sample = (sample - 8) >> output_shift;
    return sample;
}

int16_t APU::get_ch4_sample() {
    if (!ch4.enabled) return 0;
    int16_t sample = (ch4.lfsr & 0x0001) ? -ch4.volume : ch4.volume;
    return sample;
}