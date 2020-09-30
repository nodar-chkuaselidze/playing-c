#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

void printBits(const char *name, char *bytes, int len) {
  printf("Layout for %s with %d bytes is: ", name, len);

  // small endian
  for (int i = len - 1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      printf("%d", bytes[i] >> j & 0x01);
    }
  }
  printf("\n");
}

// Check 0-ed values bit layouts.
int main() {
  short int x1 = 0;
  int x2 = 0;
  long x3 = 0;
  long long x4 = 0;

  float x5 = 0;
  double x6 = 0;
  char x7 = 0;
  bool x8 = 0;

  printf("System is: %s\n", is_big_endian() ? "big endian" : "small endian");

  printBits("short int", (char *)&x1, sizeof(x1));
  printBits("int", (char *)&x2, sizeof(x2));
  printBits("long", (char *)&x3, sizeof(x3));
  printBits("long long", (char *)&x4, sizeof(x4));
  printBits("float", (char *)&x5, sizeof(x5));
  printBits("double", (char *)&x6, sizeof(x6));
  printBits("char", (char *)&x7, sizeof(x7));
  printBits("bool", (char *)&x8, sizeof(x8));
}
