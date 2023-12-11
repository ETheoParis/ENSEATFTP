#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

void printip(struct addrinfo* res);

int main(int argc, char* argv[]){
	
	if(argc != 3){perror("wrong number of arguments");exit(EXIT_FAILURE);}
	
	char* host;
	char* file;

	host = argv[1];
	file = argv[2];

	printf("host : %s	file : %s \n",host,file);
	
	//addrinfo keep only results the same type as hints
	struct addrinfo hints;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_UDP; 
	
	struct addrinfo* res;
	
	int s=getaddrinfo(host, NULL, &hints, &res);
	if (s!=0){
		fprintf(stderr,"getaddrinfo:%s",gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	printip(res);

	int socket_fd;
	if((socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0){perror("unable to create socket");}
	printf("socket_fd : %d\n", socket_fd);
	
}

void printip(struct addrinfo* res){
	char host[NI_MAXHOST];
	getnameinfo(res->ai_addr,res->ai_addrlen,host,sizeof(host),NULL,0,NI_NUMERICHOST | NI_NUMERICSERV);
	printf("ip : %s \n",host);
}
