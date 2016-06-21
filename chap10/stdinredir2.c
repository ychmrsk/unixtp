/* stdinredir2.c

   open fd, close stdin(fd.0), dup(fd)(assign fd.0), close(fd)

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* #define CLOSE_DUP   /* open, close, dup, close */
/* #define USE_DUP2    /* open, dup2, close */

int main(void)
{
  int fd;
  int newfd;
  char line[100];

  fgets(line, 100, stdin);  printf("%s", line);
  fgets(line, 100, stdin);  printf("%s", line);
  fgets(line, 100, stdin);  printf("%s", line);

  /* redirect input */
  fd = open("/etc/passwd", O_RDONLY);
#ifdef CLOSE_DUP
  close(0);
  newfd = dup(fd);
#else
  newfd = dup2(fd, 0);
#endif
  if (newfd != 0) {
    fprintf(stderr, "Could not open data as fd 0\n");
    exit(1);
  }
  close(fd);

  fgets(line, 100, stdin);  printf("%s", line); 
  fgets(line, 100, stdin);  printf("%s", line); 
  fgets(line, 100, stdin);  printf("%s", line); 
}
