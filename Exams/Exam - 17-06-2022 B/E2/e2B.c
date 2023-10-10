#include "e2B.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int wordcount(const char** s, int n){
	if(n == 0){
		return -1;
	}
	int max = 0;
	for(int i = 0; i < n; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if(pid == 0){
			char str[strlen(s[i])];
			strcpy(str,s[i]); 
			int num = 0;
			char* c = strtok(str, " ");
			while(c != NULL){
				num++;
				c = strtok(NULL, " ");
			}
			_exit(num);
		}
		int status;
		pid = wait(&status);
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status) > max){
				max = WEXITSTATUS(status);
			}
		}
	}
	return max;
}
