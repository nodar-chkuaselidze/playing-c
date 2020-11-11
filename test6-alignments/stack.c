#include <stdio.h>
#include <stddef.h>

/**
 * Many operation speed can be impacted by the machine WORDSIZE and
 * proper alignment of the data with WORDSIZE in the memory.
 *
 * The reason for this is that, machines can access memory only in WORDSIZE
 * steps, meaning: If you have WORDSIZE of 4 and you stack four chars inside it,
 * in order to get 3rd char machine will have to grab 4 bytes and that shift and
 * mask to give you the char. These operations are pretty quick on the machines,
 * but still can make difference for heavily intensive operations if the data
 * is not properly aligned.
 *
 * In this file we are checking WORDSIZE and compiler decisions to align
 * our data properly for optimized access.
 *
 * Q: Can 4 byte(int) can be anywhere???
 *      - Maybe its optimized to be better on 0 and 4-th bytes (32 bit compat)
 *      - Will be interesting to check if this alignment matters.
 */

/**
 * Machine used for testing:
 *  char: 1
 *  short: 2
 *  int: 4
 *  long int: 8
 */
void print_sizes() {
  printf("char: %ld\n", sizeof(char));
  printf("short: %ld\n", sizeof(short));
  printf("int: %ld\n", sizeof(int));
  printf("long int: %ld\n", sizeof(long int));
}

/**
 * Note stack alignment of the variables
 * is fully dependent on the compiler we are using.
 *
 * Clang will have totally different layout when compared to GCC.
 * We will represent this layouts in the examples.
 */

/**
 * GCC (64bit/8byte machine):
 *  GDB outputs:
 *    a: 0x7fffffffde5b, (1 byte)
 *    b: 0x7fffffffde5c, (4 bytes)
 *    c: 0x7fffffffde60, (8 bytes)
 *
 *    (gdb) x/30bx $sp
 *    0x7fffffffde50: 0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde58: 0x00    0x00    0x00    0x31    0x01    0x00    0x00    0x00
 *                                            └ a(5b) └ b(5c)                    ⅃
 *    0x7fffffffde60: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ c(60)                                                    ⅃
 *    ...
 * Clang:
 *  GDB Outputs:
 *    a: 0x7fffffffde57, (1 byte)
 *    b: 0x7fffffffde50, (4 bytes)
 *    c: 0x7fffffffde48, (8 bytes)
 *
 *    (gdb) x/30bx $sp
 *    0x7fffffffde40: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde48: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ c(48)                                                    ⅃
 *    0x7fffffffde50: 0x01    0x00    0x00    0x00    0x07    0x00    0x00    0x31
 *                    └ b(50)                    ⅃                            └ a(57)
 *    ...
 */
void example1() {
  char a = '1';
  int b = 1;
  long c = 1l;

  printf(
      "a: %p,\n"
      "b: %p,\n"
      "c: %p,\n"
  ,
    &a,
    &b,
    &c
  );
}

/**
 * GCC:
 *  GDB outputs:
 *    a: 0x7fffffffde59, (1 byte)
 *    b: 0x7fffffffde5a, (2 bytes)
 *    c: 0x7fffffffde5c, (4 bytes)
 *    d: 0x7fffffffde60, (8 bytes)
 *
 *    (gdb) x/40bx $sp
 *    0x7fffffffde50: 0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde58: 0x00    0x31    0x01    0x00    0x01    0x00    0x00    0x00
 *                            └ a(59) └ b(5a)    ⅃    └ c(5c)                    ⅃
 *    0x7fffffffde60: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ d(60)                                                    ⅃
 *    ...
 * Clang:
 *  GDB Outputs:
 *    a: 0x7fffffffde57,
 *    b: 0x7fffffffde54,
 *    c: 0x7fffffffde50,
 *    d: 0x7fffffffde48,
 *
 *    (gdb) x/40bx $sp
 *    0x7fffffffde40: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde48: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ d(48)                                                    ⅃
 *    0x7fffffffde50: 0x01    0x00    0x00    0x00    0x01    0x00    0x00    0x31
 *                    └ c(50)                    ⅃    └ b(54)    ⅃            └ a(57)
 *    ...
 */
void example2() {
  char a = '1';
  short b = 1;
  int c = 1;
  long d = 1l;

  printf(
      "a: %p,\n"
      "b: %p,\n"
      "c: %p,\n"
      "d: %p,\n"
  ,
    &a,
    &b,
    &c,
    &d
  );
}

/**
 * Unoptimized.
 * GCC:
 *   GDB Out:
 *    a: 0x7fffffffde4c (1 byte)
 *    b: 0x7fffffffde50 (8 bytes)
 *    c: 0x7fffffffde4d (1 byte)
 *    d: 0x7fffffffde58 (8 bytes)
 *    e: 0x7fffffffde4e (2 bytes)
 *    f: 0x7fffffffde60 (8 bytes)
 *
 *    0x7fffffffde40: 0x08    0x26    0xfa    0xf7    0xff    0x7f    0x00    0x00
 *    0x7fffffffde48: 0xc2    0x80    0xe5    0xf7    0x31    0x33    0x05    0x00
 *                                                    └ a(4c) └ c(4d) └ e(4e)    ⅃
 *    0x7fffffffde50: 0x02    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ b(50)                                                    ⅃
 *    0x7fffffffde58: 0x04    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ d(58)                                                    ⅃
 *    0x7fffffffde60: 0x06    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ f(60)                                                    ⅃
 *
 * Clang:
 *  GDB Out:
 *    a: 0x7fffffffde57 (1 byte)
 *    b: 0x7fffffffde48 (8 bytes)
 *    c: 0x7fffffffde47 (1 byte)
 *    d: 0x7fffffffde38 (8 bytes)
 *    e: 0x7fffffffde36 (2 bytes)
 *    f: 0x7fffffffde28 (8 bytes)
 *
 *    (gdb) x/72bx $sp
 *    0x7fffffffde10: 0x28    0xde    0xff    0xff    0xff    0x7f    0x00    0x00
 *    0x7fffffffde18: 0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde20: 0xff    0xb5    0xf0    0x00    0x00    0x00    0x00    0x00
 *    0x7fffffffde28: 0x06    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ f(28)                                                    ⅃
 *    0x7fffffffde30: 0x00    0x00    0x00    0x00    0x00    0x00    0x05    0x00
 *                                                                    └ e(36)    ⅃
 *    0x7fffffffde38: 0x04    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ d(38)                                                    ⅃
 *    0x7fffffffde40: 0x01    0x00    0x00    0x00    0x00    0x00    0x00    0x33
 *                                                                            └ c(47)
 *    0x7fffffffde48: 0x02    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                    └ b(48)                                                    ⅃
 *    0x7fffffffde50: 0x01    0x00    0x00    0x00    0x01    0x00    0x00    0x31
 *                                                                            └ a(57)
 */
void example3() {
  char a = '1';
  long b = 2l;
  char c = '3';
  long d = 4l;
  short e = 5l;
  long f = 6;

  printf(
      "a: %p\n"
      "b: %p\n"
      "c: %p\n"
      "d: %p\n"
      "e: %p\n"
      "f: %p\n"
  ,
    &a,
    &b,
    &c,
    &d,
    &e,
    &f
  );
}


int main(void) {

  print_sizes();
  printf("\n");
  example1();
  printf("\n");
  example2();
  printf("\n");
  example3();

  return 0;
}
