/* more02.c -- more ver0.2
   read file, print 24 lines, stop temporally and wait next command.
   ADD@ver0.2 : read command from /dev/tty
*/

#include <stdio.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int ac, char *av[])
{
  FILE *fp;

  if (ac == 1)
    do_more(stdin);
  else
    while (--ac)
      if ((fp = fopen(*++av, "r")) != NULL) {
        do_more(fp);
        fclose(fp);
      } else
        exit(1);
  return 0;
}

/* read 'PAGELEN' lines and wait next command to call see_more() */
void do_more(FILE *fp)
{
  char line[LINELEN];
  int num_of_lines = 0;
  int see_more(FILE *), reply;
  FILE *fp_tty;

  fp_tty = fopen("/dev/tty", "r");  /* new @ver0.2 */
  if (fp_tty == NULL)
    exit(1);

  while (fgets(line, LINELEN, fp)) {  /* there are any inputs */
    if (num_of_lines == PAGELEN) {  /* already full-screen output */
      reply = see_more(fp_tty); /* y: wait next command */
      if (reply == 0)     /* quit */
        break;
      num_of_lines -= reply;  /* reset counter */
    }
    if (fputs(line, stdout) == EOF)  /* display lines */
      exit(1);                       /* quit if EOF */
    num_of_lines++;                  /* count lines */
  }
}

/* display message and wait to response.
   return lines forward.
   q: NO, space: YES, CR: 1 line
 */
int see_more(FILE *cmd)
{
  int c;

  printf("\033[7m more? \033[m");  /* display converted */
  while ((c = getc(cmd)) != EOF) {  /* read from tty */
    if (c == 'q')
      return 0;
    if (c == ' ')
      return PAGELEN;
    if (c == '\n')
      return 1;
  }
  return 0;
}
