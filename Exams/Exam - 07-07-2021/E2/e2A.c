#include "e2A.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int wordWithMaxCount(const char* text, const char c, char ** word){
	
	if (strlen(text)==0) return 0;
	
	int max_count = 0;
	char* max_word = NULL;
	int size = strlen(text);
	char buf[size];
	strcpy(buf, text);
	
	char* token = strtok(buf, " ");
	while(token != NULL){
		int count = 0;
		int i = 0;
		while(i < strlen(token)){
		if(token[i] == c) count++;
		i++;
		}
		if(count > max_count){
			if (max_word!=NULL) free(max_word); 
			max_word = (char *) malloc(strlen(token)+1);
			strcpy(max_word, token);
			max_count=count;
		}
		token = strtok(NULL, " ");
	}
	
	*word = max_word;
	return max_count;
}
