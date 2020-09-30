#include <stdio.h>

// C does not support multidimensional arrays (Separate type)
// It only has arrays and arrays of arrays.
// But the way it is allocated is exact same, but they can be troublesome
// to work with??

// NOTE: Even though arrays decay to pointers, arrays of arrays do not
// decay to pointer to pointer, but instead they decay to pointer to array.

// This will decay to int (*x)[2], e.g. bellow
void acceptPointerToArray(int x[2][2]) {
}

// this will be the same *x[2]
void acceptPointerToArrayDecayed(int (*x)[2]) {
}

// this will decay to **int
void acceptPointerToPointer(int *x[2]) {
}

// decayed version of above declaration.
void acceptPointerToPointerDecayed(int **x) {
}

int main() {
  int x1[2][2] = {
    {1, 2},
    {3, 4}
  };

  int x2[2][3][4] = {
    {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12}
    },
    {
      {13, 14, 15, 16},
      {17, 18, 19, 20},
      {21, 22, 23, 24}
    }
  };

  int (*xtmp)[2] = x1;

  // Does x1/x2 decay into pointers to pointers?
  acceptPointerToArray(x1);
  acceptPointerToArrayDecayed(x1);
  acceptPointerToArray(xtmp);
  acceptPointerToArrayDecayed(xtmp);

  // int[2][2] != **int / warning.
  acceptPointerToPointer(x1);
  acceptPointerToPointerDecayed(x1);
  acceptPointerToPointer(xtmp);
  acceptPointerToPointerDecayed(xtmp);

  // this is confusing but thats what it is.
  // Because array can be viewed as pointer to the first
  // element and layout in memory are the same,
  // these bellow are grouped so, that they are the same.
  int (*x2x)[3][4] = x2;
  int (*x20)[3][4] = &(x2[0]);

  int (*x20x)[4] = x2[0];
  int (*x200)[4] = &(x2[0][0]);

  int (*x200x) = x2[0][0];
  int (*x2000) = &(x2[0][0][0]);

  for (int i = 0; i < 4; i++) {
    printf("x1 value at %d(int aligned) = %d\n", i, *(*x1 + i));
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("x[%d][%d] = %d\n", i, j, x1[i][j]);
    }
  }
}
