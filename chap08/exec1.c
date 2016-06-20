/* exec1.c
   -- launch another program
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
  char *arglist[3];

  arglist[0] = "ls";
  arglist[1] = "-l";
  arglist[2] = 0;
  printf("* * * About to exec %s %s\n", arglist[0], arglist[1]);
  execvp("ls", arglist);
  printf("* * * %s is done. bye\n", arglist[0]);
}
