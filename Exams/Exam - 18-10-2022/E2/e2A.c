#include "e2A.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int loadStringsFromFile (const char * filename, char *** list){
		
		char line[1000];
		FILE* fp = fopen(filename, "r");
		if(fp == NULL){
			perror("fopen");
			return -1;
		}
		int num = 0;
		char* str = fgets(line, sizeof(line), fp);
		while(str != NULL){
			if(isalpha(str[0])){
				num++;
			}
			str = fgets(line, sizeof(line), fp);
		}
		rewind(fp);
		char** strings = (char**)calloc(num, sizeof(char*));
		char* str1 = fgets(line, sizeof(line), fp);
		int i = 0;
		while(str1 != NULL){
			if(isalpha(str1[0])){
				if (str1[strlen(str1)-1]=='\n') str1[strlen(str1)-1]='\0';
				strings[i] = (char*)calloc(strlen(str1)+1, sizeof(char));
				strcpy(strings[i], str1);
				i++;
			}
			str1 = fgets(line, sizeof(line), fp);
		}
		*list = strings;
		fclose(fp);
	return num;
}
