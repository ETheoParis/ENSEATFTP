#define SIZE 1024
#define MESSAGE "test"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void gettftp(char* input){
	if (read(STDIN_FILENO, input, SIZE) == -1){
		perror("read");
        }
	}
	
void puttftp(){
	if (write(STDOUT_FILENO, MESSAGE, strlen(MESSAGE)) == -1) {
		perror("write");
        }
	}
	
	
int main(int argc, char* argv[]){
	char input[SIZE];
	
	
	gettftp(input);
	puttftp();
	
	}
