#include <stdio.h>
#include <string.h>

/**
 * Examples
 * &types1 - 0x555555558050 (which will contain pointers to the strings)
 *  sizeof(types1) -> 40 (5 pointers (on 64 bit cpu - 8 * 5))
 *  contains->
 *    (gdb) x/40bx &types
 *    0x555555558050 <run1.types1>:     0x25    0x60    0x55    0x55    0x55    0x55    0x00    0x00
 *    0x555555558058 <run1.types1+8>:   0x04    0x60    0x55    0x55    0x55    0x55    0x00    0x00
 *    0x555555558060 <run1.types1+16>:  0x08    0x60    0x55    0x55    0x55    0x55    0x00    0x00
 *    0x555555558068 <run1.types1+24>:  0x0d    0x60    0x55    0x55    0x55    0x55    0x00    0x00
 *    0x555555558070 <run1.types1+32>:  0x14    0x60    0x55    0x55    0x55    0x55    0x00    0x00
 * so (print types1):
 *  &types[0] - 0x555555556025 - 0x00
 *  &types[1] - 0x555555556004 - 0x41    0x4c    0x4c    0x00
 *  &types[2] - 0x555555556008 - 0x4e    0x4f    0x4e    0x45    0x00
 *  &types[3] - 0x55555555600d - 0x53    0x49    0x4e    0x47    0x4c    0x45    0x00
 *  &types[4] - 0x555555556014
 *    0x555555556014: 0x53    0x49    0x4e    0x47    0x4c    0x45    0x52    0x45
 *    0x55555555601c: 0x56    0x45    0x52    0x53    0x45    0x00
 */

void run1() {
  static const char *types1[5] = {"", "ALL", "NONE", "SINGLE", "SINGLEREVERSE"};

  printf("%p\n", types1);
}

/**
 * Example run:
 *  &types2 - 0x555555556040
 *  contains (5 * 14) = 70 of consecutive memory ->
 *   &types2[0] - 0x555555556040 <run2.types2>
 *   &types2[1] - 0x55555555604e <run2.types2+14>
 *   &types2[2] - 0x55555555605c <run2.types2+28>
 *   &types2[3] - 0x55555555606a <run2.types2+42>
 *   &types2[4] - 0x555555556078 <run2.types2+56>
 *
 *   0x555555556040 <run2.types2>:     0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                                     └ \0 - End of string - size 0 basically
 *   0x555555556048 <run2.types2+8>:   0x00    0x00    0x00    0x00    0x00    0x00    0x41    0x4c
 *                                                              end of types2[0]  ⅃    └ A     └ L
 *   0x555555556050 <run2.types2+16>:  0x4c    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                                     └ L     └ \0
 *   0x555555556058 <run2.types2+24>:  0x00    0x00    0x00    0x00    0x4e    0x4f    0x4e    0x45
 *                                               end of types2[1] ⅃    └ N     └ O     └ N     └ E
 *   0x555555556060 <run2.types2+32>:  0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                                     └ \0
 *   0x555555556068 <run2.types2+40>:  0x00    0x00    0x53    0x49    0x4e    0x47    0x4c    0x45
 *                               end of types2[2] ⅃    └ S     └ I     └ N     └ G     └ L     └ E
 *   0x555555556070 <run2.types2+48>:  0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
 *                                     └ \0                                      end of types2[3] ⅃
 *   0x555555556078 <run2.types2+56>:  0x53    0x49    0x4e    0x47    0x4c    0x45    0x52    0x45
 *                                     └ S     └ I     └ N     └ G     └ L     └ E     └ R     └ E 
 *   0x555555556080 <run2.types2+64>:  0x56    0x45    0x52    0x53    0x45    0x00
 *                                     └ V     └ E     └ R     └ S     └ E     └ \0 
 *                                                               end of types2[3] ⅃
 */
void run2() {
  static const char types2[5][14] = {"", "ALL", "NONE", "SINGLE", "SINGLEREVERSE"};
  printf("%p\n", types2);
}

int main() {
  printf("running 1..\n");
  run1();

  printf("running 2..\n");
  run2();
}
