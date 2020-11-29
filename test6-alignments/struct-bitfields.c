#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

#define WORDSIZE 8
#define psizeof(item)    printf("sizeof: " #item " = %ld bytes\n", sizeof(item))
#define palignof(item)   printf("alignof: " #item " = %ld\n", alignof(item))
#define poffsetof(st, m) printf("offsetof: " #st "->" #m " = %lu\n", offsetof(st, m))

static void _memprint(void *ptr, size_t length);
static void _memprintbits(void *ptr, size_t length);
#define memprt(ptr, length) _memprint(ptr, length)
#define memprtbits(ptr, length) _memprintbits(ptr, length)
#define mark(item) memset(&item, 0xff, sizeof(item))

/**
 * Experiment with struct bitfield alignments..
 */

struct st1 {
  unsigned char bit0:1;
  unsigned char bit1:1;
  unsigned char bit2:1;
  unsigned char bit3:1;
  unsigned char bit4:1;
  unsigned char bit5:1;
  unsigned char bit6:1;
  unsigned char bit7:1;
};

int main(void) {
  psizeof(struct st1);
  palignof(struct st1);

  struct st1 x1 = { 0, 0 };
  mark(x1);
  /*x1.bit0 = 0;*/
  x1.bit1 = 0;
  /*x1.bit2 = 0;*/
  /*x1.bit3 = 0;*/
  /*x1.bit4 = 0;*/
  /*x1.bit5 = 0;*/
  /*x1.bit6 = 0;*/
  /*x1.bit7 = 0;*/

  memprt(&x1, sizeof(x1));
  printf("\n");
  memprtbits(&x1, sizeof(x1));

  {
    printf("\nChar manipulation with st1...\n");
    // char manipulation using st1.
    char x = 'a';

    memprtbits(&x, 1);
    struct st1 *xt = (struct st1*)&x;
    xt->bit0 = 0;
    memprtbits(&x, 1);
  }

  return 0;
}

static void _memprint(void *ptr, size_t length) {
  size_t ptraddr = (size_t)ptr;

  for (size_t i = 0; i < length; i++) {
    if (i % WORDSIZE == 0) {
      printf("0x%lx: ", ptraddr + i);
    }

    unsigned char *ptr = (unsigned char *)ptraddr + i;
    printf("0x%02x\t", *ptr);

    if (i % WORDSIZE == WORDSIZE - 1)
      printf("\n");
  }
}

static void printbits(unsigned char x) {
  for (int i = 0; i < 8; i++) {
    printf("%u", (x >> i) & 0x1);
  }
}

static void _memprintbits(void *ptr, size_t length) {
  size_t ptraddr = (size_t)ptr;

  for (size_t i = 0; i < length; i++) {
    if (i % WORDSIZE == 0) {
      printf("0x%lx: ", ptraddr + i);
    }

    unsigned char *ptr = (unsigned char *)ptraddr + i;
    printbits(*ptr);
    printf(" ");

    if (i % WORDSIZE == WORDSIZE - 1)
      printf("\n");
  }
}
