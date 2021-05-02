#include <stdio.h>
#include <sys/socket.h>

#define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

typedef struct{
    
}sockaddr;

void launch_server(int port){
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPRTO_UDP)) == -1){
	handle_error("socket");
    }else{
	if(bind(sockfd, ))
    }
}

int main(int argc, char * argv[]){
    if(argc != 2){
	write(2, "operand error\n", 14);
	return 1;
    }

    
}
