#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run(int* v, int n, int (*f)(int i)){
	for(int i = 0; i < n; i++){
		pid_t pid = fork();
		if(pid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if(pid == 0){
			int res = f(i);
			_exit(res);
		}
		int status;
		pid = wait(&status);
		if(WIFEXITED(status)){
			v[i] = WEXITSTATUS(status);
		}
	}
}

