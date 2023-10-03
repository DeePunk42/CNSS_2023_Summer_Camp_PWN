#include <stdio.h>

int main(void) {
  int s = 0;
  printf("\x90\x90\x90%n%d", &s, s);
  printf("%d", s);
  return 0;
}
