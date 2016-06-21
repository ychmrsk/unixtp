#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *cp = getenv("LANG");
  if (cp != NULL && strcmp(cp,"ja_JP.UTF-8")==0)
    printf("Bonjour\n");
  else
    printf("Hello\n");
}
