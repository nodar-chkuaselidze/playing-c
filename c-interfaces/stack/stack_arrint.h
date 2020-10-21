#ifndef CII_STACK_ARRINT
#define CII_STACK_ARRINT

#include <stdio.h>

/**
 * Stack A will implement Integer stack using array of integers.
 * Array will start from 128 and double from there.
 */

#define CII_STACK_START 128

struct stack_arrint {
  int size;
  int count;
  int *arr;
};

typedef struct stack_arrint stack_arrint_t;

extern stack_arrint_t *cii_stack_arrint_new();
extern int cii_stack_arrint_empty(stack_arrint_t *stack);
extern void cii_stack_arrint_push(stack_arrint_t *stack, int x);
extern int cii_stack_arrint_pop(stack_arrint_t *stack);
extern void cii_stack_arrint_free(stack_arrint_t *stack);
extern void cii_stack_arrint_print(FILE *out, stack_arrint_t *stack);

#endif // CII_STACK_ARRINT
