#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_arrint.h"

stack_arrint_t *cii_stack_arrint_new() {
  stack_arrint_t *stack = malloc(sizeof(stack_arrint_t));

  assert(stack != NULL);
  stack->count = 0;
  stack->size = CII_STACK_START;
  stack->arr = malloc(sizeof(int) * CII_STACK_START);

  return stack;
}

void cii_stack_arrint_push(stack_arrint_t *stack, int x) {
  assert(stack != NULL);

  if (stack->size == (stack->count + 1) * sizeof(int)) {
    stack->size *= 2;
    stack->arr = realloc(stack->arr, stack->size);
    assert(stack->arr != NULL);
  }

  stack->arr[stack->count] = x;
  stack->count++;
}

int cii_stack_arrint_empty(stack_arrint_t *stack) {
  assert(stack != NULL);

  return stack->count = 0;
}

int cii_stack_arrint_pop(stack_arrint_t *stack) {
  assert(stack != NULL);
  assert(stack->count > 0);

  stack->count--;
  return stack->arr[stack->count];
}

void cii_stack_arrint_free(stack_arrint_t *stack) {
  assert(stack != NULL);
  free(stack->arr);
  free(stack);
}

void cii_stack_arrint_print(FILE *out, stack_arrint_t *stack) {
  assert(stack != NULL);

  fprintf(out, "Stack count: %d.\n", stack->count);

  for (int i = stack->count - 1; i >= 0; i--) {
    fprintf(out, "%d->", stack->arr[i]);
  }

  fprintf(out, "\n");
}
