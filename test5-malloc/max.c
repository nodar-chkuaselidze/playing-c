#include <stdio.h>
#include <stdlib.h>

int main() {
  int mb = 0;

  while (malloc(1 << 20)) ++mb;
  printf("Allocated %d MB.\n", mb);
  return 0;
}
