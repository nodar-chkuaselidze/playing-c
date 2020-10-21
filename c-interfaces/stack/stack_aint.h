#ifndef CII_STACK_AINT
#define CII_STACK_AINT

#include <stdio.h>

/**
 * Stack A will implement Integer stack using linked list.
 */

struct stack_aint_elem {
  struct stack_aint_elem* next;
  int value;
};

typedef struct stack_aint_elem stack_aint_elem_t;

struct stack_aint {
  int count;
  stack_aint_elem_t *head;
};

typedef struct stack_aint stack_aint_t;

extern stack_aint_t *cii_stack_aint_new();
extern int cii_stack_aint_empty(stack_aint_t *stack);
extern void cii_stack_aint_push(stack_aint_t *stack, int x);
extern int cii_stack_aint_pop(stack_aint_t *stack);
extern void cii_stack_aint_free(stack_aint_t *stack);
extern void cii_stack_aint_print(FILE *out, stack_aint_t *stack);

#endif // CII_STACK_AINT
