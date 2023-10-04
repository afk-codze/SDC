#include "e2A.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void handle_error(int res, char* msg){
	if(res == -1 ){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

char* load(const char* filename, unsigned* size){
	
	int fd = open(filename, O_RDONLY, S_IRWXU);
	handle_error(fd, "open");
	int _size = lseek(fd, 0, SEEK_END);
	handle_error(_size, "lseek");
	
	char* buffer = (char*)calloc(_size, sizeof(char));
	
	int res = lseek(fd, 0, SEEK_SET);
	handle_error(res, "lseek");
	
	res = read(fd, buffer, _size);
	handle_error(res, "read");
	
	*size = _size;
	return buffer;
}

