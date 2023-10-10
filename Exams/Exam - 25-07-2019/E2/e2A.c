#include "e2A.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int contains(char* s, char c, int n){
	
	int len = strlen(s);
	int m = len/n;
	
	if(m*n < len){
		for(int j = n*m; j < len; j++){
			if(s[j] == c){
				return 1;
			} 
		}
	}
	
	int found = 0;
	
	for(int i = 0; i < n; i++){
		
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			return 0;
		}
		
		
		if(pid == 0){
			int a = 0;
			for(int k = i*m; k < (i+1)*m; k++){
				if(s[k] == c){
					a = 1;
				}
			}
			_exit(a);
		}
		
		int status;
		pid = wait(&status);
		if(WIFEXITED(status) && WEXITSTATUS(status) == 1){
			found = 1;
		}
	
	}
	return found;
}


