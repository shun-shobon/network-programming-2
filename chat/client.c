#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT (in_port_t)50000
#define BUF_LEN 512

int main() {
  struct hostent *server_ent;
  struct sockaddr_in server;
  int soc;
  char hostname[] = "localhost";
  char buf[BUF_LEN];

  if ((server_ent = gethostbyname(hostname)) == NULL) {
    perror("gethostbyname");
    return 1;
  }

  printf("server name: %s\n", server_ent->h_name);
  for (int i = 0; server_ent->h_aliases[i] != NULL; i++) {
    printf("\talias[%d]: %s\n", i, server_ent->h_aliases[i]);
  }
  for (int i = 0; server_ent->h_addr_list[i] != NULL; i++) {
    printf("\taddress[%d]: %s\n", i,
           inet_ntoa(*(struct in_addr *)server_ent->h_addr_list[i]));
  }

  memset((char *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);

  if ((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }

  if (connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1) {
    perror("connect");
    return 1;
  }

  write(1, "connected!\n", 12);

  do {
    int n;

    n = read(soc, buf, BUF_LEN);
    write(1, "server: ", 9);
    write(1, buf, n);

    write(1, "client: ", 9);
    n = read(1, buf, BUF_LEN);
    write(soc, buf, n);
  } while (strncmp(buf, "quit", 4) != 0);

  close(soc);

  return 0;
}
