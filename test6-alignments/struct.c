#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

#define WORDSIZE 8
#define psizeof(item)    printf("sizeof: " #item " = %ld bytes\n", sizeof(item))
#define palignof(item)   printf("alignof: " #item " = %ld\n", alignof(item))
#define poffsetof(st, m) printf("offsetof: " #st "->" #m " = %lu\n", offsetof(st, m))

void _memprint(void *ptr, size_t length);
#define memprt(ptr, length) _memprint(ptr, length)
#define mark(item) memset(&item, 0xff, sizeof(item))

/**
 * Experiment with struct alignments..
 */

struct st1 {
  char a;
};

struct st2 {
  char a[2];
};

/**
 * Memory layout:
 *  sizeof: 12
 *  alignof: 4
 *
 *  0x7ffd9b77e8c0: 0x01    0xff    0xff    0xff    0x14    0x13    0x12    0x11
 *                  └ a                             └ b                        ⅃
 *  0x7ffd9b77e8c8: 0x21    0x31    0xff    0xff
 *                  └ c     └ d
 */
struct st3 {
  char a;
  int b;
  char c;
  char d;
};

/**
 * Memory layout:
 *  sizeof: 16
 *  alignof: 8
 *
 *  0x7ffd9b77e8c0: 0x01    0xff    0xff    0xff    0xff    0xff    0xff    0xff
 *                  └ a
 *  0x7ffd9b77e8c8: 0x09    0x08    0x07    0x06    0x05    0x04    0x03    0x02
 *                  └ b                                                        ⅃
 *
 */
struct st4 {
  char a;
  long b;
};

/**
 * Memory layout:
 *  sizeof: 40
 *  alignof: 8
 *
 *  0x7ffd9b77e8c0: 0x01    0xff    0xff    0xff    0xff    0xff    0xff    0xff
 *                  └ a
 *  0x7ffd9b77e8c8: 0x18    0x17    0x16    0x15    0x14    0x13    0x12    0x11
 *                  └ b                                                        ⅃
 *  0x7ffd9b77e8d0: 0x21    0xff    0xff    0xff    0x34    0x33    0x32    0x31
 *                  └ c                             └ d                        ⅃
 *  0x7ffd9b77e8d8: 0x41    0xff    0xff    0xff    0xff    0xff    0xff    0xff
 *                  └ e
 *  0x7ffd9b77e8e0: 0x58    0x57    0x56    0x55    0x54    0x53    0x52    0x51
 *                  └ f                                                        ⅃
 */
struct st5 {
  char a;
  long b;
  char c;
  int d;
  char e;
  long f;
};

int main(void) {
  psizeof(struct st1);
  palignof(struct st1);
  psizeof(struct st2);
  palignof(struct st2);

  {
    printf("\n  struct st3\n");
    struct st3 x = {};

    mark(x);
    x.a = 1;
    x.b = 0x11121314;
    x.c = 0x21;
    x.d = 0x31;

    psizeof(struct st3);
    palignof(struct st3);
    poffsetof(struct st3, a);
    poffsetof(struct st3, b);

    printf("\nDumping mem of x: \n");
    memprt(&x, sizeof(x));
    printf("\n");
  }

  {
    printf("\n  struct st4\n");

    psizeof(struct st4);
    palignof(struct st4);
    poffsetof(struct st4, a);
    poffsetof(struct st4, b);

    struct st4 x = {};

    mark(x);

    x.a = 1;
    x.b = 0x0203040506070809;

    printf("\n Dumping mem of x: \n");
    memprt(&x, sizeof(x));
    printf("\n");
  }

  {
    printf("\n  struct st5\n");

    psizeof(struct st5);
    palignof(struct st5);
    poffsetof(struct st5, a);
    poffsetof(struct st5, b);
    poffsetof(struct st5, c);
    poffsetof(struct st5, d);
    poffsetof(struct st5, e);
    poffsetof(struct st5, f);

    struct st5 x = {};

    mark(x);
    x.a = 0x01;
    x.b = 0x1112131415161718;
    x.c = 0x21;
    x.d = 0x31323334;
    x.e = 0x41;
    x.f = 0x5152535455565758;

    printf("\n Dumping mem of x: \n");
    memprt(&x, sizeof(x));
    printf("\n");
  }

  return 0;
}

void _memprint(void *ptr, size_t length) {
  size_t ptraddr = (size_t)ptr;
  size_t start_from = ptraddr - (ptraddr % WORDSIZE);

  for (size_t i = start_from; i < ptraddr + length; i++) {
    if (i % WORDSIZE == 0) {
      printf("0x%lx: ", i);
    }

    unsigned char *ptr = (unsigned char *)i;
    printf("0x%02x\t", *ptr);

    if (i % WORDSIZE == WORDSIZE - 1)
      printf("\n");
  }
}
