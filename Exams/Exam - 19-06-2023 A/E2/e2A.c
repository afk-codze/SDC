#include "e2A.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int examStats(const char* fname, int * min, int * max, float * avg){
	
	char line[1000];
	int _max = 0;
	int _min = 31;
	float _avg = 0;
	FILE* fp = fopen(fname, "r");
	if(fp == NULL){
		perror("open");
		return -1;	
	}
	float sum = 0;
	float superato = 0;
	char* c = fgets(line, sizeof(line), fp);
	while(c != NULL){
		char* token = strtok(c, "-");
		token = strtok(NULL, "-");
		token = strtok(NULL, "-");
		int voto = atoi(token);
		if(voto > 17){
			superato++;
			sum += voto;
			if(voto > _max){
				_max = voto;
			}
			if(voto < _min){
				_min = voto;
			}
		}
		c = fgets(line, sizeof(line), fp);
	}
	if(superato > 0){
		_avg = sum/superato;
	}else{
		_avg = 0;
	}
	if(superato == 0){
		_min = 0;
	}
	*avg = _avg;
	*max = _max;
	*min = _min;
	return superato;
}
