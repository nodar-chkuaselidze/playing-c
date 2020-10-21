#include <time.h>
#include <stdio.h>
#include "hrtime.h"

void print_timediff(const char *name, uint64_t diff, uint64_t ops) {
  double seconds = (double)diff / 1e9;
  uint64_t rate = (uint64_t)((double)ops / seconds);
  uint64_t perOp = diff / ops;

  printf("%s: ops=%lu, time=%fs, rate=%lu ops/s %lu ns/op",
      name, ops, seconds, rate, perOp);
}

uint64_t hrtime() {
  struct timespec t;

  if (clock_gettime(CLOCK_MONOTONIC, &t))
    return 0;  /* Not really possible. */

  return (uint64_t)t.tv_sec * (uint64_t) 1e9 + (uint64_t) t.tv_nsec;
}
