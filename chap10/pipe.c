/* pipe.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define oops(m, x) { perror(m); exit(x); }

int main(int ac, char **av)
{
  int thepipe[2], newfd, pid;

  if (ac != 3) {
    fprintf(stderr, "usage: pipe cmd1 cmd2\n");
    exit(1);
  }
  if (pipe(thepipe) == -1)
    oops("Cannot get a pipe", 1);
  
  /* fork the process */
  if ((pid = fork()) == -1)
    oops("Cannot fork", 2);

  /* parent : read from pipe and exec av[2] */
  if (pid > 0) {
    close(thepipe[1]);  /* don't write to pipe */
    if (dup2(thepipe[0], 0) == -1)  /* dual connection */
      oops("Could not redirect stdin", 3);
    close(thepipe[0]);  /* thepipe[0] connection is only fd.0 (stdin) */
    execlp(av[2], av[2], NULL);
    oops(av[2], 4);
  }

  /* child : exec av[1] and write to pipe */
  close(thepipe[0]);  /* don't read from pipe */
  if (dup2(thepipe[1], 1) == -1)  /* dual connection */
    oops("could not redirect stdout", 5);
  close(thepipe[1]);  /* thepipe[1] connection is only fd.1 (stdout) */
  execlp(av[1], av[1], NULL);
  oops(av[1], 6);
}
