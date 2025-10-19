#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdint.h>
#include <stddef.h>

uint64_t read_sequential(int fd, size_t filesize, size_t block_size);
uint64_t read_random(int fd, size_t filesize, size_t block_size);

#endif
