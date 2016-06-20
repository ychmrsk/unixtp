#include <stdio.h>
#include <unistd.h>

int main(void)
{
  printf("my pid is %d\n", getpid());
  fork();
  sleep(1);
  fork();
  sleep(1);
  fork();
  sleep(1);
  printf("my pid is %d\n", getpid());
}
