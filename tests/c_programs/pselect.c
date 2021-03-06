#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/sendfile.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int sock1, sock2;
  if ((sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return(EXIT_FAILURE);
  if ((sock2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return(EXIT_FAILURE);

  fd_set fdset;
  FD_ZERO(&fdset);
  FD_SET(sock1, &fdset);
  FD_SET(sock2, &fdset);

  struct timespec timeout;
  timeout.tv_sec = 1;
  timeout.tv_nsec = 1000;

  if (pselect(sock2+1, &fdset, NULL, NULL, &timeout, NULL) < 0) {
    fprintf(stderr, "pselect() failed: %s\n.", strerror(errno));
    return(EXIT_FAILURE);
  }
          
  return(EXIT_SUCCESS);
}
