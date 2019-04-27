#include <stdio.h>
#include <stdlib.h>

struct stA {
  int number;
};

struct stB {
  struct stA *a;
  int number;
};

void printline(const char *s);
void print_sta(struct stA a);
void print_sta_ref(struct stA *a);
void print_stb(struct stB b);
void print_stb_ref(struct stB *b);
void add_stack_sta(struct stB *b);
void add_heap_sta(struct stB *b);

int
main(void) {
  printf("Experiment struct..\n");

  struct stA a1 = { .number=122 };
  printf("Address before passing: %p\n", (void *)&a1);
  print_sta(a1);
  print_sta_ref(&a1);

  struct stB b1 = { .a=&a1, .number=322 };
  print_stb(b1);
  print_stb_ref(&b1);

  // add badd thing
  struct stB b2 = { .number=333 };

  // stack allocated thing will get freed
  // after leaving stack from
  // add_stack_sta function, so it will
  // give us who knows what thing.
  printline("Bad thing.");
  add_stack_sta(&b2);
  print_stb(b2);
  print_stb_ref(&b2);

  // heap thing.
  struct stB b3 = { .number=333 };

  printline("Heap thing.");
  add_heap_sta(&b3);
  print_stb(b3);
  print_stb_ref(&b3);

  free(b3.a);

  // this should be undefined behaviour.
  // What is in b3.a ? who knows.
  printline("After freeing..");
  print_stb(b3);
  print_stb_ref(&b3);

  return 0;
}

void
add_stack_sta(struct stB *b) {
  struct stA la = { .number=111 };
  b->a = &la;
}

void
add_heap_sta(struct stB *b) {
  struct stA *la = (struct stA*)malloc(sizeof(struct stA));
  la->number = 99;
  b->a = la;
}

void
print_stb(struct stB b) {
  printline("----");
  printf("STB val:\n");
  printf("address: %p, number: %d\n", (void *)&b, b.number);
  print_sta_ref(b.a);
  printline("----");
}

void
print_stb_ref(struct stB *b) {
  printline("----");
  printf("STB ref:\n");
  printf("address: %p, number: %d\n", (void *)b, b->number);
  print_sta_ref(b->a);
  printline("----");
}

void
print_sta(struct stA a) {
  printf("STA by val:\n");
  printf("Address: %p, number: %d\n", (void *)&a, a.number);
  printline("");
}

void
print_sta_ref(struct stA *a) {
  printf("STA by ref:\n");
  printf("Address: %p, number: %d\n", (void *)a, a->number);
  printline("");
}

void printline(const char *s) {
  printf("%s\n", s);
}
