#ifndef CRC64_H
#define CRC64_H

#include <stdint.h>
#include <stddef.h>

uint64_t crc64_update(uint64_t crc, const unsigned char *data, size_t len);
uint64_t crc64_init(void);

#endif
