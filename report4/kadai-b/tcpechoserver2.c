#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h> //htons 
#include <string.h>
#include <sys/epoll.h>

#define BUFSIZE 1024
#define NEVENTS 16
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char const *argv[]){
  int server_fd, port, i, nfds, sock;
  int epoll_fd, n;
  socklen_t len;
  struct sockaddr_in address, client;
  struct epoll_event ev, ev_ret[NEVENTS];
  
  if(argc != 2){
    fwrite("operand error\n", 1, 14, stderr);
    return 1;
  }

  port = atoi(argv[1]);
  
  if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
    handle_error("socket");
  }
       
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
       
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
    handle_error("bind");
  }
    
  if (listen(server_fd, 3) < 0){
    handle_error("listen");
  }

  if((epoll_fd = epoll_create1(0)) == -1){
    handle_error("epoll_create1");
  }
  

  return 0;
}
