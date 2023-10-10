#include "e2B.h"
#include <stdio.h>

off_t searchfile(char* filename, char c){
	int offset = 0;
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		perror("fopen");
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	for(int i = 0; i<size; i++){
		char carattere = fgetc(fp);
		if(carattere == c){
			offset = ftell(fp);
			return offset-1;
		}	
	}
	fclose(fp);
	return -1;
}
