#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define DATA_SIZE 512

void printip(struct addrinfo* res);
char* WRQ(int socket_fd, struct addrinfo* res, char* file,char* mode);
void sendData(int socket_fd, struct addrinfo* res, char* file);

int main(int argc, char* argv[]){
	
	if(argc != 4){perror("wrong number of arguments");exit(EXIT_FAILURE);}
	
	char* host;
	char* file;

	host = argv[1];
	file = argv[3];

	printf("host : %s	file : %s \n",host,file);
	
	//addrinfo keep only results the same type as hints
	struct addrinfo hints;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_UDP; 
	
	struct addrinfo* res;
	
	int s=getaddrinfo(host, argv[2], &hints, &res);
	if (s!=0){
		fprintf(stderr,"getaddrinfo:%s",gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	printip(res);

	int socket_fd;
	if((socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0){perror("unable to create socket");}
	printf("socket_fd : %d\n", socket_fd);
	
}

char* WRQ(int socket_fd, struct addrinfo* res, char* file,char* mode){
	
	int size_file = strlen(file);
	int size_mode = strlen(mode);
	int size_WRQ = 2 + size_file + 1 + size_mode + 1;	// 2 byts Opcode and a zero to separate filename and mode and to mark the end
	char* WRQ_msg = calloc(1,size_WRQ);							//RRQ de la forme Opcodefile0mode0
	
	WRQ_msg[0] = 0;										// initialise Opcode to read request
	WRQ_msg[1] = 2; 		

	strcpy(WRQ_msg+2,file);
	WRQ_msg[2+size_file]=0;
									//separator
	strcpy(WRQ_msg+3+size_file,mode);
	WRQ_msg[3+size_file+size_mode]=0;

	ssize_t size_msg = sendto(socket_fd, WRQ_msg, size_WRQ, 0, res->ai_addr, res->ai_addrlen);
	if(size_msg == -1){perror("sendto error");exit(EXIT_FAILURE);}
	
	return WRQ_msg;
}

void sendData(int socket_fd, struct addrinfo* res, char* file){
	int fileSize = strlen(file);
	int blockNum=0;
	while (blockNum*DATA_SIZE<fileSize){
		char *data=(char*)calloc(1,DATA_SIZE);
		data[0]=0;
		data[1]=3;
		strcpy(data+2,blockNum);
		strcpy(data+4,file+blockNum*DATA_SIZE);
		ssize_t size_sent = sendto(socket_fd, data, DATA_SIZE, 0, res->ai_addr, res->ai_addrlen);
		if(size_sent == -1){perror("sendto error");exit(EXIT_FAILURE);}
		
	}
}
void printip(struct addrinfo* res){
	char host_r[NI_MAXHOST];
	getnameinfo(res->ai_addr,res->ai_addrlen,host_r,sizeof(host_r),NULL,0,NI_NUMERICHOST | NI_NUMERICSERV);
	printf("ip : %s \n",host_r);
}
