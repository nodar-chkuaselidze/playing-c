#include <stdio.h>
#include "stack_arrint.h"

int main() {
  stack_arrint_t *stack = cii_stack_arrint_new();

  for (int i = 0; i < 10; i++)
    cii_stack_arrint_push(stack, i);

  printf("Printing stack...\n");
  cii_stack_arrint_print(stdout, stack);

  for (int i = 0; i < 5; i++) {
    int val = cii_stack_arrint_pop(stack);

    printf("popped: %d\n", val);
  }

  cii_stack_arrint_print(stdout, stack);
  for (int i = 0; i < 5; i++) {
    cii_stack_arrint_push(stack, 10 + i);
  }

  cii_stack_arrint_print(stdout, stack);
  cii_stack_arrint_free(stack);

  return 0;
}
