#include <stdio.h>

#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

int
main() {
  printf("Do the same with ints\n");
  int int1 = 0x01 * 0x22;
  printf("%d * %d = ", 0x0101, 0x21);
  printf("%d (%x)\n\n", int1, int1);

  printf("RoundMask: %d\n", __round_mask(int1, 8));
  printf("RoundMask: %d %#0x\n", round_up(int1, 16), round_up(int1, 16));
  printf("RoundMask: %d %x\n", round_down(int1, 16), round_down(int1, 16));

  int dec1 = 11 * 2;
  printf("%d * %d = %d\n", 11, 2, dec1);
  printf("%x * %x = %x\n", 11, 2, dec1);

  return 0;
}
