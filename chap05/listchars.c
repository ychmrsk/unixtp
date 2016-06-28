#include <stdio.h>

int main(void)
{
  int c, n = 0;
  while ((c = getchar()) != 'q')
    printf("char %3d is %c code %d\n", n++, c, c);
}
