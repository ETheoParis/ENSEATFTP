#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 512

void printip(struct addrinfo* res);
char* RRQ(int socket_fd, struct addrinfo* res, char* file,char* mode);

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
	
	int s=getaddrinfo(host,"69", &hints, &res);
	if (s!=0){
		fprintf(stderr,"getaddrinfo:%s",gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	printip(res);
	
	int socket_fd;
	if((socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0){perror("unable to create socket");}
	printf("socket_fd : %d\n", socket_fd);
	
	char* RRQ_msg;
	RRQ_msg = RRQ(socket_fd,res, file, "octet");
	printf("RRQ : %s \n", RRQ_msg);
	
	freeaddrinfo(res);
	close(socket_fd);
}

void printip(struct addrinfo* res){
	char host_r[NI_MAXHOST];
	getnameinfo(res->ai_addr,res->ai_addrlen,host_r,sizeof(host_r),NULL,0,NI_NUMERICHOST | NI_NUMERICSERV);
	printf("ip : %s \n",host_r);
}

char* RRQ(int socket_fd, struct addrinfo* res, char* file,char* mode){
	int size_file = strlen(file);
	int size_mode = strlen(mode);
	int size_RRQ = 2 + size_file + 1 + size_mode + 1;	// 2 byts Opcode and a zero to separate filename and mode and to mark the end
	char* RRQ_msg = calloc(1,size_RRQ);							//RRQ de la forme Opcode0filename0mode
	
	RRQ_msg[0] = '0';
	RRQ_msg[1] = '1'; 		
										// initialise Opcode to read request
	strcpy(RRQ_msg+2,file);
	RRQ_msg[2+size_file]='0';
									//separator
	strcpy(RRQ_msg+3+size_file,mode);
	RRQ_msg[3+size_file+size_mode]='0';

	ssize_t size_msg = sendto(socket_fd, RRQ_msg, size_RRQ, 0, res->ai_addr, res->ai_addrlen);
	printf("%ld\n",size_msg);
	if(size_msg == -1){perror("sendto error");exit(EXIT_FAILURE);}
	
	return RRQ_msg;
}

char* receive(int socket_fd, struct addrinfo* res,char* filename){
	//char data[BUFF_SIZE];
	return "todo";
	}


