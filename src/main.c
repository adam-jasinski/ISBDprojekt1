#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "file_read.h"
#include "file_mmap.h"
#include "timer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Użycie: %s <plik>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat sb;
    fstat(fd, &sb);
    size_t filesize = sb.st_size;
    size_t block_size = 8 * 1024 * 1024;

    printf("Plik: %s (%.2f MB)\n", filename, filesize / (1024.0 * 1024.0));

    struct timespec t;
    double elapsed;
    uint64_t crc;

    // read + sequential
    lseek(fd, 0, SEEK_SET);
    t = timer_start();
    crc = read_sequential(fd, filesize, block_size);
    elapsed = timer_end(t);
    printf("[read+seq]  czas: %.3f ms,  CRC64: 0x%016lX\n", elapsed, crc);

    // read + random
    lseek(fd, 0, SEEK_SET);
    t = timer_start();
    crc = read_random(fd, filesize, block_size);
    elapsed = timer_end(t);
    printf("[read+rand] czas: %.3f ms,  CRC64: 0x%016lX\n", elapsed, crc);

    // mmap + sequential
    t = timer_start();
    crc = mmap_sequential(fd, filesize, block_size);
    elapsed = timer_end(t);
    printf("[mmap+seq]  czas: %.3f ms,  CRC64: 0x%016lX\n", elapsed, crc);

    // mmap + random
    t = timer_start();
    crc = mmap_random(fd, filesize, block_size);
    elapsed = timer_end(t);
    printf("[mmap+rand] czas: %.3f ms,  CRC64: 0x%016lX\n", elapsed, crc);

    close(fd);
    return 0;
}
