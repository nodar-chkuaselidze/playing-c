#include <setjmp.h>

#include <stdio.h>
/*#define printf(...) do {} while(0)*/

/**
 * Q1: Can we setjmp in a function,
 *  then go out of it and jump back into it from another function.
 *  Stack at the time of setjmp needs to be backed up with the data it was supplied
 *  in order to "rewind". Is it possible?
 *
 *  - If it is possible, where does this data get stored? (e.g. 1 MB array)
 *  - If not, okay...
 * A1: https://stackoverflow.com/a/8628294/3607360
 *
 * Fun1:
 *  - Use fork/longjmp before fork (to basically spawn many forked processes. xD)
 */

/**
 * Q1
 * Check if we can jump back into non-existent stack (Does it back it up.)
 */

static int q1_jump_back_into_this(jmp_buf buf);
static void q1_jump_from_here(jmp_buf buf);

int main(void) {
  jmp_buf buf1;

  /* This will just SMASH THE STACK by GCC and clang.
   * We can trick the system into thinking that stack was not
   * corrupted if we match the stack sizes in two functions,
   * basically making stack pointer backed up in jmp_buf
   * valid??
   * It will still rewind the execution to the SETJMP function though.
   * Bellow shows 
   */
  int res1;
  

  res1 = q1_jump_back_into_this(buf1);

  printf("Will this run again? (%d)\n", res1);
  if (res1 == 0)
    q1_jump_from_here(buf1);
  printf("We are done.");

  return 0;
}

int q1_jump_back_into_this(jmp_buf buf) {
  int x = 111;

  printf("%p\n", (void *)&x);
  int res = setjmp(buf);

  if (res == 0) {
    printf("Nothing happening, we just set the jump.\n");
    return res;
  } else {
    printf("Jump was successful. x: %d, code: %d\n", x, res);
    return res;
  }
}

void q1_jump_from_here(jmp_buf buf) {
  int x = 333;
  int res = 222;
  printf("%p\n", (void *)&x);
  printf("Jumping from another function.\n");
  longjmp(buf, 1);
}

