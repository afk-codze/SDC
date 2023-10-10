#include "e2A.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int multicount(const char** s, char c, int n){
	
	if(c == '\0' || n == 0){
		return -1;
	}
	int max_occorrenze = 0;
	for(int i = 0; i < n; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			return -1;
		}
		if(pid == 0){
			int occorrenze = 0;
			for(int j = 0; j < strlen(s[i]); j++){
				if(c == s[i][j]) occorrenze++;
			}
			_exit(occorrenze);
		}
		int status;
		pid = wait(&status);
		if(WIFEXITED(status)){
			if(WEXITSTATUS(status) > max_occorrenze){
				max_occorrenze = WEXITSTATUS(status);
			}
		}
		
	}
	return max_occorrenze;
}

