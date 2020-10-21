#include <stdio.h>
#include "stack_llint.h"

int main() {
  stack_llint_t *stack = cii_stack_llint_new();

  for (int i = 0; i < 10; i++)
    cii_stack_llint_push(stack, i);

  printf("Printing stack...\n");
  cii_stack_llint_print(stdout, stack);

  for (int i = 0; i < 5; i++) {
    int val = cii_stack_llint_pop(stack);

    printf("popped: %d\n", val);
  }

  cii_stack_llint_print(stdout, stack);
  for (int i = 0; i < 5; i++) {
    cii_stack_llint_push(stack, 10 + i);
  }

  cii_stack_llint_print(stdout, stack);
  cii_stack_llint_free(stack);

  return 0;
}
