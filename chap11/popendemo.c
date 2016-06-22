/* popendemo.c

   open program as file for stdio

   1. popen() return FILE * like fopen()
   2. returned FILE * can be used by all standard function
   3. when exit, call pclose()

*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  char buf[100];
  int i = 0;

  fp = popen("who|sort", "r");

  while (fgets(buf, 100, fp) != NULL)
    printf("%3d %s", i++, buf);

  pclose(fp);
  return 0;
}
