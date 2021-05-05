#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> // socket, bind
#include <netinet/in.h> //sockaddr_in 
#include <arpa/inet.h> // htons

#define MAXLINE 1024
#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char * argv[]){
    int sockfd, port;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    
    if(argc != 2){
	write(2, "operand error\n", 14);
	return 1;
    }

    port = atoi(argv[1]);
    
    // Creating socket file descriptor 
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPRTO_UDP)) == -1){
	handle_error("socket");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));    

    // Filling server information 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket with the server address 
    if(bind(sockfd, &servaddr, sizeof(servaddr)) == -1){
	handle_error("bind");
    }

    int len, n;
    len = sizeof(cliaddr);
    
    n = recvfrom(sockfd, buffer, MAXLINE, 0, &cliaddr, &len);
    buffer[n] = '\0';
    fwrite(buffer, sizeof(char), n, stdout);
    fwrite("\n", sizeof(char), 1, stdout);
    sendto(sockfd, buffer, n, 0, &cliaddr, len);

    return 0;
    
}
