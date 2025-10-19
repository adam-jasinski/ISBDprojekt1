#ifndef TIMER_H
#define TIMER_H

#include <time.h>

struct timespec timer_start(void);
double timer_end(struct timespec start);

#endif
