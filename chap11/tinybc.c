/* tinybc.c

   use `dc`
   bi-direct two pipes
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define oops(m, x) { perror(m); exit(x); }

void fatal(char *);
void be_dc(int in[2], int out[2]);
void be_bc(int to[2], int from[2]);

int main(void)
{
  int pid, todc[2], fromdc[2];

  /* make two pipes */
  if (pipe(todc) == -1 || pipe(fromdc) == -1)
    oops("pipe failed", -1);

  /* user interface */
  if ((pid = fork()) == -1)
    oops("cannot fork", 2);
  if (pid == 0)  /* child is dc */
    be_dc(todc, fromdc);
  else {         /* parent is bc */
    be_bc(todc, fromdc);
    wait(NULL);
  }
}

void be_dc(int in[2], int out[2])
{
  /* connect stdin with in-pipe */
  if (dup2(in[0], 0) == -1)
    oops("dc: cannot redirect stdin", 3);
  close(in[0]);  /* use fd.0 */
  close(in[1]);  /* don't use */

  /* connect stdout with out-pipe */
  if (dup2(out[1], 1) == -1)
    oops("bc: cannot redirect stdout", 4);
  close(out[1]);  /* use fd.1 */
  close(out[0]);  /* don't use */

  /* exec `dc` with `-`(option) */
  execlp("dc", "dc", "-", NULL);
  oops("Cannot run dc", 5);
}

void be_bc(int todc[2], int fromdc[2])
{
  int num1, num2;
  char operation[BUFSIZ], message[BUFSIZ], *fgets();
  FILE *fpout, *fpin, *fdopen();

  /* setup */
  close(todc[0]);
  close(fromdc[1]);
  
  /* convert file descriptor to stream */
  fpout = fdopen(todc[1], "w");
  fpin = fdopen(fromdc[0], "r");
  if (fpout == NULL || fpin == NULL)
    fatal("Error converting pipes to streams");
  
  /* main loop */
  while (printf("tinybc: "), fgets(message, BUFSIZ, stdin) != NULL) {
    if (sscanf(message, "%d%[-+*/^]%d", &num1, operation, &num2) != 3) {
      printf("syntax error\n");
      continue;
    }

    if (fprintf(fpout, "%d\n%d\n%c\np\n", num1, num2, *operation) == EOF)
      fatal("Error writing");
    fflush(fpout);
    if (fgets(message, BUFSIZ, fpin) == NULL)
      break;
    printf("%d %c %d = %s", num1, *operation, num2, message);
  }
  fclose(fpout);
  fclose(fpin);
}

void fatal(char *mess)
{
  fprintf(stderr, "Error: %s\n", mess);
  exit(1);
}
