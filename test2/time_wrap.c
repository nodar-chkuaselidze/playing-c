
#include <limits.h>
#include <stdio.h>
#include <time.h>


int
main(void) {
  /*time_t max_time = 8000000000000000l;*/
  time_t max_time = UINT_MAX;
  time_t cur_time;
  
  time(&cur_time);

  // gmtime will change statically allocated struct *tm
  // So you can't do 
  // struct *tm gmtime_1 = gmtime(&max_time);
  // struct *tm gmtime_2 = gmtime(&cur_time);
  // both will be same `gmtime_1` and `gmtime_2`

  printf("%s\n", asctime(gmtime(&max_time)));
  printf("%s\n", ctime(&max_time));

  printf("%s\n", asctime(gmtime(&cur_time)));
  printf("%s\n", ctime(&cur_time));

  return 0;
}
