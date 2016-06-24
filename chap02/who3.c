/* who3.c -- who command ver3
   open utmp file, read data structure, and show the result.
   ver2 : remove empty record, and format time using ctime()
   ver3 : buffering using utmplib.c
*/

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>

#define SHOWHOST  /* remote machine name for output */

void showtime(time_t);
void show_info(struct utmp *);

int main(void)
{
  struct utmp *utbufp;
  struct utmp *utmp_next();
  
  int utmp_open(char *);
  int utmp_reload(void);
  void utmp_close(void);

  if (utmp_open(UTMP_FILE) == -1) {
    perror(UTMP_FILE);
    exit(1);
  }

  while ((utbufp = utmp_next()) != ((struct utmp *) NULL))
    show_info(utbufp);
  utmp_close();

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

void showtime(time_t timeval)
{
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp+4);
}
