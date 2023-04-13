#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT (in_port_t)50000
#define BUF_LEN 512

int main() {
  struct sockaddr_in me;
  int soc_waiting;
  int soc;
  char buf[BUF_LEN];

  // サーバのアドレスを構造体に格納
  memset((char *)&me, 0, sizeof(me));
  me.sin_family = AF_INET;
  me.sin_addr.s_addr = htonl(INADDR_ANY);
  me.sin_port = htons(PORT);

  // IPv4でストリーム型のソケットを作成
  if ((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }

  // ソケットにアドレスを割り当てる
  if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
    perror("bind");
    return 1;
  }

  // クライアントからの接続を待つ
  listen(soc_waiting, 1);

  // クライアントからの接続を受け付ける
  soc = accept(soc_waiting, NULL, NULL);

  // 接続待ちのためのソケットを閉じる
  close(soc_waiting);

  // ここから先
  write(1, "Go ahead!\n", 10);

  // 通信のループ
  do {
    int n;
    n = read(0, buf, BUF_LEN);
    write(soc, buf, n);
    n = read(soc, buf, BUF_LEN);
    write(1, buf, n);
  } while (strncmp(buf, "quit", 4) != 0);

  close(soc);

  return 0;
}
