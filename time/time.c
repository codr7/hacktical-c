#include <errno.h>
#include "time.h"
#include "macro/fail.h"

void get_utc(struct timespec *out) {
  if (!timespec_get(out, TIME_UTC)) {
    hc_fail("Failed getting time: %d", errno);
  }
}

uint64_t sleep(uint64_t ns) {
  struct timespec t = {0};
  t.tv_nsec = ns;

  switch (nanosleep(&t, &t)) {
  case 0:
    break;
  case EINTR:
    return t.tv_nsec;
  default:
    hc_fail("Failed sleeping: %d", errno);
  }

  return 0;
}

void hc_timer_init(struct hc_timer *t) {
  get_utc(&t->start);
}

uint64_t hc_timer_nsecs(const struct hc_timer *t) {
  struct timespec end;
  get_utc(&end);
  
  return
    (end.tv_sec - t->start.tv_sec) * 1000000000 +
    (end.tv_nsec - t->start.tv_nsec);
}
