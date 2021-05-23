#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h> //htons 
#include <string.h>
#include <sys/epoll.h>

#define MAXLINE 1024
#define MAX_EVENTS 10
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char const *argv[]){
  int server_fd, port, i, nfds, valsize;
  int epoll_fd, new_socket;
  char buffer[MAXLINE];  
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  struct epoll_event ev, events[MAX_EVENTS];  

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

  ev.events = EPOLLIN;
  ev.data.fd = server_fd;
  if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1){
    handle_error("epoll_ctrl");
  }
  
  while(1){
    nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if(nfds == -1){
      handle_error("epoll_wait");
    }
    for(i = 0; i < nfds; i++){
      if(events[i].data.fd == server_fd){
	if((new_socket = accept(server_fd, (struct sockaddr *)&address,
				(socklen_t*)&addrlen)) < 0){
	  handle_error("accept");
	}
	bzero(buffer, MAXLINE);
	valsize = read( new_socket , buffer, MAXLINE);
	buffer[valsize] = '\0';
	send(new_socket, buffer, strlen(buffer), 0);
      }
    }
  }
  
  return 0;
}
