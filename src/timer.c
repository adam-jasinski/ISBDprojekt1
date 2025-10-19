#define _POSIX_C_SOURCE 200809L
#include "timer.h"

struct timespec timer_start(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t;
}

double timer_end(struct timespec start) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    return (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6; // ms
}
