/** lsrv_func1.c -- functions for license server. */
/* ver.2 : ticket_reclaim() */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORTNUM 2020
#define MSGLEN 128
#define TICKET_AVAIL 0
#define MAXUSERS 3
#define RECLAIM_INTERVAL 60

#define oops(x) { perror(x); exit(-1); }

int ticket_array[MAXUSERS];
int sd = -1;
int num_tickets_out = 0;
char *do_hello();
char *do_goodbye();

int make_dgram_server_socket(int);

void free_all_tickets(void)
{
  int i;

  for (i = 0; i < MAXUSERS; i++)
    ticket_array[i] = TICKET_AVAIL;
}

int setup(void)
{
  sd = make_dgram_server_socket(SERVER_PORTNUM);
  if (sd == -1)
    oops("make socket");
  free_all_tickets();
  return sd;
}

void shut_down(void)
{
  close(sd);
}

void narrate(char *msg1, char *msg2, struct sockaddr_in *clientp)
{
  fprintf(stderr, "\t\tSERVER: %s %s ", msg1, msg2);
  if (clientp)
    fprintf(stderr, "(%s:%d)", inet_ntoa(clientp->sin_addr), ntohs(clientp->sin_port));
  putc('\n', stderr);
}

void handle_request(char *req, struct sockaddr_in *client, socklen_t addrlen)
{
  char *response;
  int ret;

  if (strncmp(req, "HELO", 4) == 0)
    response = do_hello(req);
  else if (strncmp(req, "GBYE", 4) == 0)
    response = do_goodbye(req);
  else
    response = "FAIL invalid request";

  narrate("SAID:", response, client);
  ret = sendto(sd, response, strlen(response), 0,
               (struct sockaddr *)client, addrlen);
  if (ret == -1)
    perror("SERVER sendto failed");
}

char *do_hello(char *msg_p)
{
  int x;
  static char replybuf[MSGLEN];

  if (num_tickets_out >= MAXUSERS)
    return("FAIL no tickets available");

  for (x = 0; x < MAXUSERS && ticket_array[x] != TICKET_AVAIL; x++)
    ;

  if (x == MAXUSERS) {
    narrate("database corrupt", "", NULL);
    return("FAIL database corrupt");
  }

  ticket_array[x] = atoi(msg_p + 5);
  sprintf(replybuf, "TICK %d.%d", ticket_array[x], x);
  num_tickets_out++;
  return(replybuf);
}

char *do_goodbye(char *msg_p)
{
  int pid, slot;

  if ((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) ||
      (ticket_array[slot] != pid)) {
    narrate("Bogus ticket", msg_p + 5, NULL);
    return("FAIL invalid ticket");
  }

  ticket_array[slot] = TICKET_AVAIL;
  num_tickets_out--;

  return("THNX See ya!");
}

void ticket_reclaim(void)
{
  int i;
  char tick[BUFSIZ];
  for (i = 0; i < MAXUSERS; i++) {
    if ((ticket_array[i] != TICKET_AVAIL) && /* ESRCH: no such process */
        (kill(ticket_array[i], 0) == -1) && (errno == ESRCH)) { 
      sprintf(tick, "%d.%d", ticket_array[i], i);
      narrate("feeling", tick, NULL);
      ticket_array[i] = TICKET_AVAIL;
      num_tickets_out--;
    }
  }
  alarm(RECLAIM_INTERVAL);
}
