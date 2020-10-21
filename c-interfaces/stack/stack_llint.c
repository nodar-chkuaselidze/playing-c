#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_llint.h"

stack_llint_t *cii_stack_llint_new() {
  stack_llint_t *stack = malloc(sizeof(stack_llint_t));

  assert(stack != NULL);
  return stack;
}

void cii_stack_llint_push(stack_llint_t *stack, int x) {
  stack_llint_elem_t *elem = malloc(sizeof(stack_llint_elem_t));

  assert(stack != NULL);
  assert(elem != NULL);

  elem->next = stack->head;
  elem->value = x;

  stack->head = elem;
  stack->count++;
}

int cii_stack_llint_empty(stack_llint_t *stack) {
  assert(stack != NULL);
  return stack->count == 0;
}

int cii_stack_llint_pop(stack_llint_t *stack) {
  stack_llint_elem_t *head = stack->head;

  assert(stack != NULL);
  assert(stack->count > 0);

  stack->head = head->next;
  stack->count--;

  int value = head->value;
  free(head);


  return value;
}

void cii_stack_llint_free(stack_llint_t *stack) {
  assert(stack != NULL);

  if (stack->count == 0) {
    free(stack);
    return;
  }

  stack_llint_elem_t *curr, *next;

  for (curr = stack->head; curr != NULL; curr = next) {
    next = curr->next;
    free(curr);
  }

  free(stack);
}

void cii_stack_llint_print(FILE *out, stack_llint_t *stack) {
  assert(stack != NULL);
  fprintf(out, "Stack count: %d.\n", stack->count);

  stack_llint_elem_t *elem = stack->head;

  while (elem != NULL) {
    fprintf(out, "%d->", elem->value);
    elem = elem->next;
  }

  fprintf(out, "\n");
}
