/* who2.c -- who command ver2
   open utmp file, read data structure, and show the result.
   ver2 : remove empty record, and format time using ctime()
*/

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

#define SHOWHOST  /* remote machine name for output */

void showtime(long);
void show_info(struct utmp *);

int main(void)
{
  struct utmp utbuf;
  int utmpfd;

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);  /* definition is in utmp.h */
    exit(1);
  }

  while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
    show_info(&utbuf);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp *utbufp)
{
  if (utbufp->ut_type != USER_PROCESS)
    return;
  
  printf("%-8.8s", utbufp->ut_name);  /* login name */
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);  /* tty */
  printf(" ");
  showtime(utbufp->ut_time);   /* login time */
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", utbufp->ut_host);  /* host */
#endif
  printf("\n");
}

void showtime(long timeval)
{
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp+4);
}
