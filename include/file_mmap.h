#ifndef FILE_MMAP_H
#define FILE_MMAP_H

#include <stdint.h>
#include <stddef.h>

uint64_t mmap_sequential(int fd, size_t filesize, size_t block_size);
uint64_t mmap_random(int fd, size_t filesize, size_t block_size);

#endif
