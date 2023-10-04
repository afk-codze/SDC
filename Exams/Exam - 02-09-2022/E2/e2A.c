#include "e2A.h"
#include <stdio.h>


void getStudents(const char * filename, student * in_list, int min_mark){
	FILE* fp = fopen(filename, "w");
	if(fp == NULL){
		perror("fopen");
	}
	while(in_list != NULL){
		
		if(in_list->mark >= min_mark){
			int res = fprintf(fp, "%s %s - %d ", in_list->surname, in_list->name, in_list->mark);
			if(res < 0){
				perror("fprintf");
			}
		}
		in_list = in_list->next;
	}
	fclose(fp);
}
