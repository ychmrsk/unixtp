/* popen_ex3.c

 */

#include <stdio.h>

int main(void)
{
  FILE *fp;

  fp = popen("mail admin backup", "w");
  fprintf(fp, "Error with backup!!\n");
  pclose(fp);
}
