#include "mylib.h"
#include "sessionman.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int num;
  int soc;
  int maxfd;

  if (argc != 2) {
    fprintf(stderr, "Usage: s attendants\n");
    exit(0);
  }

  if ((num = atoi(argv[1])) <= 0 || num > MAX_ATTENDANTS) {
    fprintf(stderr, "attendants limit = %d\n", MAX_ATTENDANTS);
    exit(1);
  }

  if ((soc = mserver_socket(PORT, num)) == -1) {
    fprintf(stderr, "cannot setup server\n");
    exit(0);
  }

  maxfd = mserver_maccept(soc, num, enter);

  sessionman_init(num, maxfd);
  sessionman_loop();
}
