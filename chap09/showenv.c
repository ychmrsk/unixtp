/* showenv.c
   read and show environment
*/

#include <stdio.h>

extern char **environ;

int main(void)
{
  int i;

  for (i = 0; environ[i]; i++)
    printf("%s\n", environ[i]);
}
