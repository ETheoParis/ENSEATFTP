#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

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
	
	getaddrinfo(host, NULL, &hints, &res);
	
	
	void* addr;
	char ipstr[INET6_ADDRSTRLEN];
	struct sockaddr_in* ip = (struct sockaddr_in*) res->ai_addr;
		
	addr = &(ip->sin_addr);
	inet_ntop(res->ai_family,addr,ipstr,sizeof(ipstr));
	printf("ip : %s \n",ipstr);
	
	//socket_sd = socket(rp->ai_family,rp->ai_socktype,);
	
}
