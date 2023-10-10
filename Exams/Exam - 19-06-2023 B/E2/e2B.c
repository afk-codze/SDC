#include "e2B.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getBalanceMovements(const char* fname, int min, int max, int *bal){
	char line[1000];
	FILE* fp = fopen(fname, "r");
	if(fp == NULL){
		perror("open");
		return -1;
	}
	char* c = fgets(line, sizeof(line), fp);
	int balance = 0;
	int num = 0;
	while(c != NULL){
		int _giorno;
		int _valore;
		char* giorno = strtok(c, "|");
		char* segno = strtok(NULL, "|");
		char* valore = strtok(NULL, "|");
		if(giorno != NULL){
			_giorno = atoi(giorno);
		}
		if(valore != NULL){
			_valore = atoi(valore);
		}
		if(_giorno >= min && _giorno <= max){
			num++;
			if(*segno == '-'){
				balance -= _valore;
			}else{
				balance += _valore;
			}
		}
		c = fgets(line, sizeof(line), fp);
	}
	*bal = balance;
	return num;
}
