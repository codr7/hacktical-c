#ifndef HACKTICAL_TIME_H
#define HACKTICAL_TIME_H

#include <stdint.h>
#include <time.h>

struct hc_timer {
  struct timespec start;
};

void get_utc(struct timespec *out);
uint64_t sleep(uint64_t ns);

void hc_timer_init(struct hc_timer *t);
uint64_t hc_timer_nsecs(const struct hc_timer *t);

#endif
