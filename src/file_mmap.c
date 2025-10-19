#include "file_mmap.h"
#include "crc64.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

uint64_t mmap_sequential(int fd, size_t filesize, size_t block_size) {
    uint64_t crc = crc64_init();
    unsigned char *map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) return 0;

    size_t blocks = (filesize + block_size - 1) / block_size;
    for (size_t i = 0; i < blocks; i++) {
        size_t offset = i * block_size;
        size_t to_read = (offset + block_size > filesize) ? filesize - offset : block_size;
        crc = crc64_update(crc, map + offset, to_read);
    }

    munmap(map, filesize);
    return crc;
}

uint64_t mmap_random(int fd, size_t filesize, size_t block_size) {
    uint64_t crc = crc64_init();
    unsigned char *map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) return 0;

    size_t blocks = (filesize + block_size - 1) / block_size;
    for (size_t i = 0; i < blocks; i++) {
        size_t offset = (i % 2 == 0)
            ? (filesize - (i + 1) * block_size)
            : (i * block_size);
        if ((ssize_t)offset < 0) offset = 0;
        size_t to_read = (offset + block_size > filesize) ? filesize - offset : block_size;
        crc = crc64_update(crc, map + offset, to_read);
    }

    munmap(map, filesize);
    return crc;
}
