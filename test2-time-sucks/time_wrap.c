
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void printBytes(unsigned char *address, int size) {
    int count;
    for (count = 0; count < size; count++){
        printf("%.2x ", address[count]);
    }
    printf("\n");
}

int
main(void) {
  time_t max_time = 8000000000000000l;
  // time_t max_time = UINT_MAX;
  time_t cur_time;
  printf("%u\n", UINT_MAX);
  
  time(&cur_time);

  // gmtime will change statically allocated struct *tm
  // So you can't do 
  struct tm *gmtime_1 = gmtime(&max_time);
  struct tm *gmtime_2 = gmtime(&cur_time);
  // both will be same `gmtime_1` and `gmtime_2`
  printf("gmtime_1: %p\n", (void *)gmtime_1);
  printf("gmtime_2: %p\n", (void *)gmtime_2);
  printf("%d", gmtime_1->tm_hour);

  // This rule applies to: gmtime, localtime, ctime
  // So they are not thread safe.

  printf("%s\n", asctime(gmtime(&max_time)));
  printf("%s\n", ctime(&max_time));

  printf("%s\n", asctime(gmtime(&cur_time)));
  printf("%s\n", ctime(&cur_time));

  // the question is, what happens when
  time_t sometime = UINT_MAX;

  struct tm *sometm = gmtime(&sometime);

  {
    // Store in stack
    struct tm exp_tm1;
    memcpy(sometm, &exp_tm1, sizeof(struct tm));
    printf("%p -> %p\n", (void *)sometm, (void *)&exp_tm1);
  }


  // store this struct in HEAP.
  struct tm *exp_tm2_heap = (struct tm *)malloc(sizeof(struct tm));
  memcpy(sometm, exp_tm2_heap, sizeof(struct tm));
  printf("%p -> %p\n", (void *)sometm, (void *)exp_tm2_heap);
  free(exp_tm2_heap);


  return 0;
}
