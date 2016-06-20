/* splitline.c  -- function of analyzing commands

   char *next_cmd(char *prompt, FILE *fp)
   char **splitline(char *str);

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smsh.h"

/* read next command from fp
   return char-pointer holding string with command-line
   error: NULL when error.  call fatal from emalloc()
*/
char *next_cmd(char *prompt, FILE *fp)
{
  char *buf;
  int bufspace = 0;
  int pos = 0;
  int c;

  printf("%s", prompt);
  while ((c = getc(fp)) != EOF) {
    /* need space? */
    if (pos+1 >= bufspace) {
      if (bufspace == 0)
        buf = emalloc(BUFSIZ);
      else
        buf = erealloc(buf, bufspace+BUFSIZ);
      bufspace += BUFSIZ;
    }
    /* end of command? */
    if (c == '\n')
      break;
    /* not end */
    buf[pos++] = c;
  }
  if (c == EOF && pos == 0)
    return NULL;
  buf[pos] = '\0';
  return buf;
}


#define is_delim(x) ((x)==' '||(x)=='\t')

/* divide line into space-delimed-token */
char **splitline(char *line)
{
  char *newstr();
  char **args;
  int spots = 0;
  int bufspace = 0;
  int argnum = 0;
  char *cp = line;
  char *start;
  int len;

  if (line == NULL)
    return NULL;

  args = emalloc(BUFSIZ);
  bufspace = BUFSIZ;
  spots = BUFSIZ / sizeof(char *);

  while (*cp != '\0') {
    while (is_delim(*cp))
      cp++;
    if (*cp == '\0')
      break;

    if (argnum+1 >= spots) {
      args = erealloc(args, bufspace+BUFSIZ);
      bufspace += BUFSIZ;
      spots += (BUFSIZ / sizeof(char *));
    }

    start = cp;
    len = 1;
    while (*++cp != '\0' && !(is_delim(*cp)))
      len++;
    args[argnum++] = newstr(start, len);
  }
  args[argnum] = NULL;
  return args;
}

/* constructor of string */
char *newstr(char *s, int l)
{
  char *rv = emalloc(l+1);

  rv[l] = '\0';
  strncpy(rv, s, l);
  return rv;
}

/* free a list returned by splitline*/
void freelist(char **list)
{
  char **cp = list;
  while (*cp)
    free(*cp++);
  free(list);
}

void *emalloc(size_t n)
{
  void *rv;
  if ((rv = malloc(n)) == NULL)
    fatal("out of memory", "", 1);
  return rv;
}

void *erealloc(void *p, size_t n)
{
  void *rv;
  if ((rv = realloc(p, n)) == NULL)
    fatal("realloc() failed", "", 1);
  return rv;
}
