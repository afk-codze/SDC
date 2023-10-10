#include "e2A.h"
#include <stdio.h>
#include <string.h>

void reverseTextFile(const char * input_file, const char * output_file){
	
	char line[1000];
	
	FILE* fd_in = fopen(input_file, "r");
	FILE* fd_out = fopen(output_file, "w+");
	
	if(fd_in == NULL || fd_out == NULL) return;
	
	fseek(fd_in, 0L, SEEK_END);
	int size = ftell(fd_in);
	fseek(fd_in, 0L, SEEK_SET);
	
	
	//creo spazio per file di output
	for(int i = 0; i < size; i++) fputc('0', fd_out);
	
	while(fgets(line, sizeof(line), fd_in)){
		
		fseek(fd_out, -strlen(line), SEEK_CUR); //mi porto indietro della grandezza della stringa
		fputs(line, fd_out); //scrive la stringa cominciando da SEEK_CUR e porta il puntatore avanti di strlen(line) byte
		fseek(fd_out, -strlen(line), SEEK_CUR);//riporto indietro il puntatore cosi potro fare lo stesso con la stringa successiva
		
	}
	
	fclose(fd_in);
	fclose(fd_out);
	
}
