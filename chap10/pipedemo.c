/* pipedemo.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int len, i, apipe[2];
  char buf[BUFSIZ];

  /* make a pipe */
  if (pipe(apipe) == -1) {
    perror("could not make pipe");
    exit(1);
  }
  printf("Got a pipe! It is file descriptors: {%d %d}\n", apipe[0], apipe[1]);

  /* read from stdin, write into apipe,
     read from apipe, and write into stdout */
  while (fgets(buf, BUFSIZ, stdin)) {
    len = strlen(buf);
    if (write(apipe[1], buf, len) != len) {
      perror("writing to pipe");
      break;
    }
    for (i = 0; i < len; i++)  /* delete */
      buf[i] = 'X';
    len = read(apipe[0], buf, BUFSIZ);
    if (len == -1) {
      perror("reading from pipe");
      break;
    }
    if (write(1, buf, len) != len) {  /* stdout */
      perror("writing to stdout");
      break;
    }
  }
}
