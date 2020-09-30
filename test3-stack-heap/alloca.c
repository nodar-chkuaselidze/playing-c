#include <stdio.h>
#include <alloca.h>

struct st1 {
  int x;
};

int main() {
  struct st1 x1 = {11};
  struct st1 *x2 = alloca(sizeof(struct st1));
  x2->x = 22;

  printf("Both are at the stack:\n");
  printf("%p\n", &x1);
  printf("%p\n", x2);
}
