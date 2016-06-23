/* lclnt1.c
   license server client, ver.1
   link with clnt_funcs1.o dgram.o
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void setup(void);
int get_ticket(void);
void shut_down(void);
int release_ticket(void);

void do_regular_work(void);

int main(int ac, char *av[])
{
  setup();
  if (get_ticket() != 0)
    exit(0);

  do_regular_work();

  release_ticket();
  shut_down();
}

void do_regular_work(void)
{
  printf("SuperSleep version 1.0 Running - Licensed Software\n");
  sleep(10);
}
