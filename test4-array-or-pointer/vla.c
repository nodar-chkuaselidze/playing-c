#include <stdio.h>

// Good quote:
// > Linus Torvalds has expressed his displeasure in the past over VLA usage
// > for arrays with predetermined small sizes because it generates lower
// > quality assembly code. [6] With the Linux 4.20 kernel,
// > Linux kernel is effectively VLA-free.[7]
// Source: https://en.wikipedia.org/wiki/Variable-length_array

// Source: https://gcc.gnu.org/onlinedocs/gcc/Variable-Length.html
// You can do smart weird things???
int sum(int len, int numbers[len]);

// Or this?
//int sum2(int numbers[len], int len);
// NO, above line is wrong

// BUT This?
//int sum3(int len; int numbers[len], int len);
// NOPE !!!
// yes, but PLEASE DONT!... (I believe this is GCC Extention).

int
main(void) {
  return 0;
}
