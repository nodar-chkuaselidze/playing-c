#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_aint.h"

stack_aint_t *cii_stack_aint_new() {
  stack_aint_t *stack = malloc(sizeof(stack_aint_t));

  assert(stack != NULL);
  return stack;
}

void cii_stack_aint_push(stack_aint_t *stack, int x) {
  stack_aint_elem_t *elem = malloc(sizeof(stack_aint_elem_t));

  assert(stack != NULL);
  assert(elem != NULL);

  elem->next = stack->head;
  elem->value = x;

  stack->head = elem;
  stack->count++;
}

int cii_stack_aint_empty(stack_aint_t *stack) {
  assert(stack != NULL);
  return stack->count == 0;
}

int cii_stack_aint_pop(stack_aint_t *stack) {
  stack_aint_elem_t *head = stack->head;

  assert(stack != NULL);
  assert(stack->count > 0);

  stack->head = head->next;
  stack->count--;

  int value = head->value;
  free(head);


  return value;
}

void cii_stack_aint_free(stack_aint_t *stack) {
  assert(stack != NULL);

  if (stack->count == 0) {
    free(stack);
    return;
  }

  stack_aint_elem_t *curr, *next;

  for (curr = stack->head; curr != NULL; curr = next) {
    next = curr->next;
    free(curr);
  }

  free(stack);
}

void cii_stack_aint_print(FILE *out, stack_aint_t *stack) {
  assert(stack != NULL);
  fprintf(out, "Stack count: %d.\n", stack->count);

  stack_aint_elem_t *elem = stack->head;

  while (elem != NULL) {
    fprintf(out, "%d->", elem->value);
    elem = elem->next;
  }

  fprintf(out, "\n");
}
