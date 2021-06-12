#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h> //htons 
#include <string.h>
#include <pthread.h>

#define MAXLINE 1024
#define THREAD_NUM 10
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

struct thread_args{
  int server_fd;
  struct sockaddr_in address;
};

void *server(void *arg){
  char buffer[MAXLINE];
  struct thread_args *targs = (struct thread_args *)arg;
  struct sockaddr_in address = targs->address;  
  int server_fd = targs->server_fd;
  int new_socket;
  int addrlen = sizeof(address);  

  while(1){
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
			     (socklen_t*)&addrlen))<0)
      {
	handle_error("accept");
      }
      
    bzero(buffer, MAXLINE);
    if(read( new_socket , buffer, MAXLINE) < 0){
      handle_error("read");
    };
    
    send(new_socket , buffer , strlen(buffer), 0 );
  }

  return NULL;
}

int main(int argc, char const *argv[]){
  pthread_t thread[THREAD_NUM];
  int server_fd, port, i;
  struct sockaddr_in address;
  struct thread_args *targs = (struct thread_args*)malloc(sizeof(struct thread_args));

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

  targs->address = address;
  targs->server_fd = server_fd;

  for(i = 0; i < THREAD_NUM; i++){
    if(pthread_create(&thread[i], NULL, server, targs) != 0){
      handle_error("pthread_create");
    }
  }

  for(i = 0; i < THREAD_NUM; i++){
    if(pthread_join(thread[i], NULL) != 0){
      handle_error("pthread_join");
    }
  }

  return 0;
}
