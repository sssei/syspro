#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h> //htons
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

#define BUFSIZE 2048
#define MAX_EVENTS 10
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char const *argv[]){
  int server_fd, port, i, nfds, listen_sock;
  int epoll_fd, conn_sock, flag, read_size;
  char buf[BUFSIZE];
  struct sockaddr_in address;
  socklen_t adr_len = sizeof(address);  
  struct epoll_event ev, events[MAX_EVENTS];
  
  if(argc != 2){
    fwrite("operand error\n", 1, 14, stderr);
    return 1;
  }

  port = atoi(argv[1]);
  
  if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    handle_error("socket");
       
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
       
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    handle_error("bind");
    
  if (listen(server_fd, 128) < 0) handle_error("listen");

  if((epoll_fd = epoll_create1(0)) == -1) handle_error("epoll_create1");
  
  ev.events = EPOLLIN;
  ev.data.fd= server_fd;
  if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD, server_fd, &ev) ==-1)
    handle_error("epoll_cntl");
  
  listen_sock = server_fd;
  while(1){
    nfds = epoll_wait(epoll_fd,events, MAX_EVENTS, -1);
    if(nfds==-1) handle_error("epoll_wait");
      
    for(i = 0; i < nfds; i++){
      if (events[i].data.fd == listen_sock) {
	conn_sock = accept(server_fd,(struct sockaddr *)&address, &adr_len);
	if(conn_sock == -1) handle_error("accept");
	flag = fcntl(conn_sock, F_GETFL, 0);
	fcntl(conn_sock, F_SETFL, flag | O_NONBLOCK);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = conn_sock;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_sock,&ev) == -1) 
	  handle_error("epoll_cntl");
      } else {
	read_size = read (events[i].data.fd, buf, BUFSIZE);
	write(events[i].data.fd, buf, read_size);
      }
    }
  }
  
  close(server_fd);

  return 0;
}
