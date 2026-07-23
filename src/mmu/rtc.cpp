#include "mmu.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

uint8_t RTC::read() {
    if (!latched) sync_clock();

    uint8_t secs = latched ? latch_secs : cache_secs;
    uint8_t mins = latched ? latch_mins : cache_mins;
    uint8_t hrs = latched ? latch_hrs : cache_hrs;
    uint8_t dl = latched ? latch_dl : cache_dl;
    uint8_t dh = latched ? latch_dh : cache_dh;

    switch (bank) {
        case 0x08: return secs;
        case 0x09: return mins;
        case 0x0a: return hrs;
        case 0x0b: return dl;
        case 0x0c: return dh;

        default: return 0xff;
    }
}

void RTC::write(uint8_t val) {
    sync_clock();

    switch (bank) {
        case 0x08: cache_secs = val & 0x3f; break;
        case 0x09: cache_mins = val & 0x3f; break;
        case 0x0a: cache_hrs = val & 0x1f; break;
        case 0x0b: cache_dl = val & 0xff; break;
        case 0x0c: cache_dh = val & 0xc1; break;
    }
}

void RTC::latch() {
    sync_clock();

    latch_secs = cache_secs;
    latch_mins = cache_mins;
    latch_hrs = cache_hrs;
    latch_dl = cache_dl;
    latch_dh = cache_dh;
}

void RTC::sync_clock() {
    bool halt = cache_dh & 0x40;
    if (halt) {
        last_sync_timestamp = system_clock::now();
        return;
    }

    int64_t seconds_elapsed = (duration_cast<seconds>(system_clock::now() - last_sync_timestamp)).count();
    if (seconds_elapsed < 0) return;
    uint16_t cache_days = ((cache_dh & 0x01) << 8) | (cache_dl);

    cache_secs += seconds_elapsed;

    cache_mins += cache_secs / 60;
    cache_secs %= 60;

    cache_hrs += cache_mins / 60;
    cache_mins %= 60;

    cache_days += cache_hrs / 24;
    cache_hrs %= 24;

    if (cache_days >= 0x200) {
        cache_dh |= 0x80;
        cache_days %= 0x200;
    }

    cache_dl = cache_days & 0xff;
    cache_dh = (cache_dh & 0xC0) | ((cache_days & 0x100) >> 8);

    last_sync_timestamp += seconds(seconds_elapsed);
}