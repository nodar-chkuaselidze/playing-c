#include <stdio.h>

// Arrays are always passed as pointers to functions
// See test4-array-or-pointer/struct.c (Use struct to pass)

// Here, we will be testing various ideas abuot stack vs heap passing.

struct simple_struct {
  int a;
};

int main() {
  // Does assigning one array to another result to Stack copy ?
  struct simple_struct x1 = { 10 };
  struct simple_struct x2 = x1;

  printf("Addr x1: %p, Addr x2: %p\n", &x1, &x2);
  printf("x1 %s x2\n", &x1 == &x2 ? "==" : "!=");

  // Does not work, can't assign.
  // int y1[10] = {};
  // int y2[10] = y1;

  // Neither will this.
  // int y1[10] = {};
  // int y2[] = y1;

}
