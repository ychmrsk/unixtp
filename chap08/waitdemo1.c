/* waitdemo1.c
   parent process wait for exit of child process
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DELAY 2

int main(void)
{
  int newpid;
  void child_code(), parent_code();

  printf("before: mypid is %d\n", getpid());

  if ((newpid = fork()) == -1)
    perror("fork");
  else if (newpid == 0)
    child_code(DELAY);
  else
    parent_code(newpid);
}

void child_code(int delay)
{
  printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
  sleep(delay);
  printf("child done. about to exit\n");
  exit(17);
}

void parent_code(int childpid)
{
  int wait_rv;
  wait_rv = wait(NULL);
  printf("done waiting for %d. wait returned: %d\n", childpid, wait_rv);
}
