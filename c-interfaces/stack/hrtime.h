#ifndef CII_HRTIME
#define CII_HRTIME

#include <inttypes.h>

void print_timediff(const char *name, uint64_t diff, uint64_t ops);
uint64_t hrtime(void);

#endif // CII_HRTIME
