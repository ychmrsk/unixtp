#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int connect_to_server(char *, int);
void talk_with_server(int);

int main(int ac, char *av[])
{
  int fd, port;
  char *host = av[1];
  port = atoi(av[2]);
  fd = connect_to_server(host, port);
  if (fd == -1)
    exit(1);
  talk_with_server(fd);
  close(fd);
}

void talk_with_server(int fd)
{
  char buf[BUFSIZ];
  int n;
  n = read(fd, buf, BUFSIZ);
  write(1, buf, n);
}
