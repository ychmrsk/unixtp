#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>

#define PORTNUM 13000

extern int make_server_socket(int);
void process_request(int);

int main(void)
{
  int sock, fd, port = PORTNUM;
  sock = make_server_socket(port);
  if (sock == -1)
    exit(1);
  while (1) {
    fd = accept(sock, NULL, NULL);
    if (fd == -1)
      break;
    process_request(fd);
    close(fd);
  }
}

void process_request(int fd)
{
  time_t now;
  char *cp;
  printf("Wow! got a call!\n");
  time(&now);
  cp = ctime(&now);
  write(fd, cp, strlen(cp));
}
