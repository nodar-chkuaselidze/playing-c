#include <stdio.h>
#include <setjmp.h>

static void x(jmp_buf b) {
  printf("x: %p\n", (void *)&b);

  // longjmp with 0 value evaluates to 1.
  longjmp(b, 1);
}

int main(void) {
  jmp_buf buf1;

  int jmpstatus = setjmp(buf1);

  printf("Jump status: %d\n", jmpstatus);
  if (jmpstatus == 0) {
    printf("normal execution\n");
    printf("%p\n", (void *)&buf1);
    x(buf1);
  } else {
    printf("We came here from x..\n");
    printf("%d\n", jmpstatus);
  }
}
