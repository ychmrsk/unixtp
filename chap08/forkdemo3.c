/* forkdemo3.c
   return value of fork is useful for judgement
   which process is parent, and the other is child.
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
  int fork_rv;

  printf("Before: my pid is %d\n", getpid());
  
  fork_rv = fork();

  if (fork_rv == -1)
    perror("fork");
  else if (fork_rv == 0)
    printf("I am the child. my pid=%d\n", getpid());
  else
    printf("I am the parent. my child is %d\n", fork_rv);
}
