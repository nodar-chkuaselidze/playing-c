#include <stdio.h>

// This is simple experiment with array and array of arrays.
// Testing if we can have two interfaces to the same data.

// Because both are allocated the exact same way in the memory
// these two can be used interchangably.
// Also see: test4-array-or-pointer/arr-of-arr.c
union arr2d {
  int arr1d[6];
  int arr2d[2][3];
};

static void printAddr(union arr2d x) {
  printf("printAddr: %p\n", (void *)&x);
}

int main() {
  union arr2d x1 = {{1, 2, 3, 4, 5, 6}};

  // We can see that union also copies array on the stack.
  printf("Size of the union: %lu\n", sizeof(union arr2d));
  printf("at stack: %p\n", (void *)&x1);
  printAddr(x1);

  printf("2d element: %d, 4th element: %d, 6th element: %d\n",
    x1.arr1d[1], x1.arr1d[3], x1.arr1d[5]);

  printf("el[0][1]: %d, el[1][0]: %d, el[1][2]: %d\n",
    x1.arr2d[0][1], x1.arr2d[1][0], x1.arr2d[1][2]);

  return 0;
}
