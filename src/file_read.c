#include "file_read.h"
#include "crc64.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

uint64_t read_sequential(int fd, size_t filesize, size_t block_size) {
    uint64_t crc = crc64_init();
    char *buffer = malloc(block_size);
    if (!buffer) return 0;

    size_t bytes_read;
    while ((bytes_read = read(fd, buffer, block_size)) > 0) {
        crc = crc64_update(crc, (unsigned char*)buffer, bytes_read);
    }

    free(buffer);
    return crc;
}

uint64_t read_random(int fd, size_t filesize, size_t block_size) {
    uint64_t crc = crc64_init();
    char *buffer = malloc(block_size);
    if (!buffer) return 0;

    size_t blocks = (filesize + block_size - 1) / block_size;
    for (size_t i = 0; i < blocks; i++) {
        off_t offset = (i % 2 == 0)
            ? (off_t)(filesize - (i + 1) * block_size)
            : (off_t)(i * block_size);
        if (offset < 0) offset = 0;

        lseek(fd, offset, SEEK_SET);
        size_t to_read = (offset + block_size > filesize) ? filesize - offset : block_size;
        ssize_t bytes_read = read(fd, buffer, to_read);
        if (bytes_read > 0)
            crc = crc64_update(crc, (unsigned char*)buffer, bytes_read);
    }

    free(buffer);
    return crc;
}
