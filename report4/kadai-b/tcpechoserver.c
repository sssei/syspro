#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h> //htons 
#include <string.h>

#define MAXLINE 1024
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char const *argv[]){
    int server_fd, new_socket, port;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAXLINE];

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
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
			     (socklen_t*)&addrlen))<0)
    {
      handle_error("accept");
    }
    
    if(read( new_socket , buffer, MAXLINE) < 0){
      handle_error("read");
    };
    
    printf("%s\n",buffer );
    send(new_socket , buffer , strlen(buffer) , 0 );
    printf("Message sent\n");
    return 0;
}
