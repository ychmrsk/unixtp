/* SIGCHLD handler that call wait() : bug+ */

int main(void)
{
  int sock, fd;
  void child_waiter(int), process_request(int);

  signal(SIGCHLD, child_waiter);

  if ((sock = make_server_socket(PROTNUM)) == -1)
    oops("make_server_socket");

  while (1) {
    fd = accept(sock, NULL, NULL);
    if (fd == -1)
      break;
    process_request(fd);
    close(fd);
  }
}

void child_waiter(int signum)
{
  /* ver.1
  wait(NULL);
  */

  /* ver.2 */
  while (waitpid(-1, NULL, WHOHANG) > 0)
    ;
}

void process_request(int fd)
{
  if (fork() == 0) {
    dup2(fd, 1);
    close(fd);
    execlp("date", "date", NULL);
    oops("execlp date");
  }
}

