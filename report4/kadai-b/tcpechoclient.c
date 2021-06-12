#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> //htons 
#include <string.h>

#define MAXLINE 1000000000
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

char buffer[MAXLINE];

int main(int argc, char *argv[]){
  int server_fd, port, valsize;
  struct sockaddr_in address;
  struct hostent *hp;
  char* hostname;

  if(argc != 3){
    fwrite("operand error\n", 1, 14, stderr);
    return 1;
  }
    
  hostname = argv[1];    
  port = atoi(argv[2]);

  hp = gethostbyname(hostname);
  if(hp == NULL){
    handle_error("gethostbyname");
  }
    
  if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
    handle_error("socket");
  }

  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = *((unsigned long *) hp->h_addr);       

  if (connect(server_fd, (struct sockaddr *)&address,
	      sizeof(address))<0)
    {
      handle_error("connect");
    }

  valsize = fread(buffer, 1, sizeof(buffer), stdin);
  buffer[valsize] = '\0';
    
  send(server_fd, buffer, strlen(buffer) , 0 );
  valsize = read(server_fd, buffer, MAXLINE);
  buffer[valsize] = '\0';

  fwrite(buffer, sizeof(char), strlen(buffer), stdout);

  return 0;
}
