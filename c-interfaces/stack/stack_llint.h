#ifndef CII_STACK_LLINT
#define CII_STACK_LLINT

#include <stdio.h>

/**
 * Stack A will implement Integer stack using linked list.
 */

struct stack_llint_elem {
  struct stack_llint_elem* next;
  int value;
};

typedef struct stack_llint_elem stack_llint_elem_t;

struct stack_llint {
  int count;
  stack_llint_elem_t *head;
};

typedef struct stack_llint stack_llint_t;

extern stack_llint_t *cii_stack_llint_new();
extern int cii_stack_llint_empty(stack_llint_t *stack);
extern void cii_stack_llint_push(stack_llint_t *stack, int x);
extern int cii_stack_llint_pop(stack_llint_t *stack);
extern void cii_stack_llint_free(stack_llint_t *stack);
extern void cii_stack_llint_print(FILE *out, stack_llint_t *stack);

#endif // CII_STACK_LLINT
