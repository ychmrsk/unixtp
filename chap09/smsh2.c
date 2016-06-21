/* smsh2.c  -- small-shell version 2
   
   shell first version based on psh
   analyze command-line and make characteristic array
   using fork, exec, wait, and ignore signals

   version.2

   @interface
   support <if...then...else...fi>

   @implementation
   process field -- control three states
   + is_control_command : bool
   + do_control_command : update state
   + ok_to_execute      : bool
   in main, execute() @ver1 => process @ver2
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "smsh.h"

#define DFL_PROMPT "> "

int main(void)
{
  char *cmdline, *prompt, **arglist;
  int result, process(char **);
  void setup();

  prompt = DFL_PROMPT;
  setup();

  while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
    if ((arglist = splitline(cmdline)) != NULL) {
      result = process(arglist);
      freelist(arglist);
    }
    free(cmdline);
  }
  return 0;
}

/* initiate shell
   call fatal() when error occurred
*/
void setup(void)
{
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
  fprintf(stderr, "Error: %s,%s\n", s1, s2);
  exit(n);
}
