/* whotofile.c

   fork, then redirect stdout of child process, at last exec command

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
  int pid;
  int fd;

  printf("About to run who into a file\n");

  /* create a new process, exit if failed */
  if ((pid = fork()) == -1) {
    perror("fork");
    exit(1);
  }

  /* child process */
  if (pid == 0) {
    close(1);
    fd = creat("userlist", 0644);
    execlp("who", "who", NULL);
    perror("execlp");
    exit(1);
  }

  /* parent process */
  if (pid != 0) {
    wait(NULL);
    printf("Done running who. results in userlist\n");
  }
}
