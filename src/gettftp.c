#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
	
	if(argc != 3){perror("wrong number of arguments");exit(EXIT_FAILURE);}
	
	char* host;
	char* file;

	host = argv[1];
	file = argv[2];

	printf("host : %s	file : %s \n",host,file);

}
