/* who1.c -- who command ver1
   open utmp file, read data structure, and show the result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST  /* remote machine name for output */

void show_info(struct utmp *);

int main(void)
{
  struct utmp current_record;
  int utmpfd;
  int reclen = sizeof(current_record);

  if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
    perror(UTMP_FILE);  /* definition is in utmp.h */
    exit(1);
  }

  while (read(utmpfd, &current_record, reclen) == reclen)
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp *utpbufp)
{
  printf("%-8.8s", utpbufp->ut_name);  /* login name */
  printf(" ");
  printf("%-8.8s", utpbufp->ut_line);  /* tty */
  printf(" ");
  printf("%10d", utpbufp->ut_time);   /* login time */
  printf(" ");
#ifdef SHOWHOST
  printf("(%s)", utpbufp->ut_host);  /* host */
#endif
  printf("\n");
}

