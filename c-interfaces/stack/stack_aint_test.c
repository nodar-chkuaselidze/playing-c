#include <stdio.h>
#include "stack_aint.h"

int main() {
  stack_aint_t *stack = cii_stack_aint_new();

  for (int i = 0; i < 10; i++)
    cii_stack_aint_push(stack, i);

  printf("Printing stack...\n");
  cii_stack_aint_print(stdout, stack);

  for (int i = 0; i < 5; i++) {
    int val = cii_stack_aint_pop(stack);

    printf("popped: %d\n", val);
  }

  cii_stack_aint_print(stdout, stack);
  for (int i = 0; i < 5; i++) {
    cii_stack_aint_push(stack, 10 + i);
  }

  cii_stack_aint_print(stdout, stack);
  cii_stack_aint_free(stack);

  return 0;
}
