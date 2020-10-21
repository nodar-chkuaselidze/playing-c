#include <stdio.h>
#include <inttypes.h>
#include "hrtime.h"
#include "stack_llint.h"

#define N 10000000

int main() {

  uint64_t start = hrtime();

  stack_llint_t *stack = cii_stack_llint_new();

  for (int i = 0; i < N; i++) {
    cii_stack_llint_push(stack, i);
  }

  uint64_t pushed = hrtime();

  for (int i = 0; i < N; i++) {
    cii_stack_llint_pop(stack);
  }

  cii_stack_llint_free(stack);

  uint64_t end = hrtime();

  print_timediff("stack_push", pushed - start, N);
  printf("\n");
  print_timediff("stack_pop", end - pushed, N);
  printf("\n");
  print_timediff("stack_push & pop", end - start, N * 2);

  return 0;
}
