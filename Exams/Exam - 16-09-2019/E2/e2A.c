#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multi_get_env(const char** names, char*** values, int num){
	
	*values = (char**)calloc(num, sizeof(char**));
	
	for(int i = 0; i < num; i++){
		
		char* env = getenv(names[i]);
		
		if(env == NULL){
			(*values)[i] = NULL;
		}else{
			(*values)[i] = (char*)calloc(strlen(env), sizeof(char));
			strcpy((*values)[i], env);
		}
	}
}
