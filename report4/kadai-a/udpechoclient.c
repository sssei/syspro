#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> // socket, bind
#include <netinet/in.h> //sockaddr_in 
#include <arpa/inet.h> // htons

#define MAXLINE 100000000
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

char buffer[MAXLINE];

int main(int argc, char * argv[]){
    int sockfd, port;
    int valsize;
    char *hostname;
    struct sockaddr_in servaddr;
    struct hostent *hp;
    
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
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
	handle_error("socket");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = *((unsigned long *) hp->h_addr);

    int len, n;

    valsize = fread(buffer, 1, sizeof(buffer), stdin);
    buffer[valsize] = '\0';
    
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, (socklen_t *) &len);
    buffer[n] = '\0';

    fwrite(buffer, sizeof(char), strlen(buffer), stdout);

    close(sockfd);
    return 0;
    
}
