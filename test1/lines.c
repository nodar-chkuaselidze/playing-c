#include <stdio.h>

int main() {
  // this simple program will count lines in file and print them out
  // This is probably not efficient way to do this, anyway..

  long int lines = 0;
  char ch = (char)getchar();

  while(ch != EOF) {
    if (ch == '\n')
      lines++;

    ch = (char)getchar();
  }

  printf("File has %ld lines.", lines);

  return 0;
}
