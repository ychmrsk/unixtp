/* genserv2.c  -- generic server (time server) ver.2

   using fork(), process `date` in unix

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/wait.h>

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

/* ver.2 -- using `date` process */
void process_request(int fd)
{
  int pid = fork();
  switch (pid) {
  case -1:
    return;
  case 0:
    dup2(fd, 1);
    close(fd);
    execl("/bin/date", "date", NULL);
    exit(1);
  default:
    wait(NULL);
  }
}
