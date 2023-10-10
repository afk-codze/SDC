#include "e2A.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getLargeTables(struct booking ** list, const char * filename, int num){
	
	*list = NULL;
	struct booking * elem;
	struct booking * last = NULL;
	
	
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		perror("fopen");
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	char* buffer = (char*)malloc(size*sizeof(char));
	char* pt_buffer = buffer;
	fread(buffer, sizeof(char), size, fp);
	int i = 0;
	while(i < size){
		char* _surname = strtok(buffer, "_");
		char* surname = (char*)malloc(strlen(_surname)*sizeof(char));
		strcpy(surname, _surname);
		
		char _places[3];
		sprintf(_places, "%c%c", buffer[30],buffer[31]);
		int* places = (int*)malloc(sizeof(int));
		*places = atoi(_places);
		
		char _time[6];
		sprintf(_time, "%c%c:%c%c", buffer[32],buffer[33],buffer[35],buffer[36]);
		char* time = (char*)malloc(strlen(_time)*sizeof(char));
		strcpy(time, _time);
		
		if(*places >= num){
			//printf("surname: %s, places: %d, time: %s \n", surname, *places, time);
			elem = (struct booking*)malloc(sizeof(struct booking));
			elem->surname = surname;
			elem->places = *places;
			elem->time = time;
			elem->next = NULL;
			
			if(*list == NULL){
				*list = elem;
			}else{
				last->next = elem;
			}
			last = elem;
		}
		free(places);
		i += 37;
		buffer = buffer+37;	
	}
	free(pt_buffer);
}
