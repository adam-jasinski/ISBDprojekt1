#include "crc64.h"

#define POLY 0x42F0E1EBA9EA3693ULL

uint64_t crc64_init(void) {
    return 0xFFFFFFFFFFFFFFFFULL;
}

uint64_t crc64_update(uint64_t crc, const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        crc ^= ((uint64_t)data[i]) << 56;
        for (int j = 0; j < 8; j++)
            crc = (crc & 0x8000000000000000ULL)
                ? (crc << 1) ^ POLY
                : (crc << 1);
    }
    return crc;
}
