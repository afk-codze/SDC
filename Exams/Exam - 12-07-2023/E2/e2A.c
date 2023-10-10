#include "e2A.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int isvocale(char carattere){
	if(carattere == 'a' || carattere == 'A' || carattere == 'e' || carattere == 'E' || carattere == 'i' || carattere == 'I' || carattere == 'o' || carattere == 'O' || carattere == 'u' || carattere == 'U' ){
		return 1;
	}else{
		return 0;
	}
}

int vowelcount(const char** s, int n){
	
	int max_count = 0;
	
	if(n == 0 || s == NULL) return -1;
	
	for(int i = 0; i< n; i++){
		
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			return -1;
		}
		
		
		if(pid == 0){
			char str[strlen(s[i])];
			strcpy(str, s[i]);
			int count = 0;
			for(int j = 0; j < strlen(str); j++){
				if(isvocale(str[j])){
					count++;
				}
			}
			exit(count);
		}
		
		int status;
		pid = wait(&status);
		if(WIFEXITED(status)){
		
			max_count += WEXITSTATUS(status);
			
		}
	}
	
	
	return max_count;
}
