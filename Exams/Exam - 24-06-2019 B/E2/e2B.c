#include "e2B.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
// inserisci la soluzione qui...
void make_files(int n, void (*f)(int i, char name[64], char buf[256])){
	
	for(int i = 0; i < n; i++){
		
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			return;
		}
		if(pid == 0){
			char my_name[64] = { 0 };
			char my_buf[256] = { 0 };
			f(i, my_name, my_buf);
			int fd = open(my_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			if(fd == -1){
				perror("open");
				return;
			}
			write(fd, my_buf, 256);
			_exit(EXIT_SUCCESS);
		}
		
		wait(NULL);
	}
}
