#include "e2A.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// inserisci la soluzione qui...

void decodeTextFile(const char * encoded_file, const char * key, char ** decoded_text){
	
	FILE * fp1 = fopen(encoded_file, "r");
	if(fp1 == NULL){
		perror("fopen");
		return;
	}
	FILE * fp2 = fopen(key, "r");
	if(fp2 == NULL){
		perror("fopen");
		return;
	}
	fseek(fp1, 0L, SEEK_END);
	int size1 = ftell(fp1);
	rewind(fp1);
	fseek(fp2, 0L, SEEK_END);
	int size2 = ftell(fp2);
	rewind(fp2);
	char buffer[size1];
	fread(buffer, sizeof(char), size1, fp1);
	char key_buf[size2];
	fread(key_buf, sizeof(char), size2, fp2);
	char decoded[size1];
	printf("%d", size1);
	int i = 0;
	for( ; i < size1; i++){
		if(buffer[i] >= 65 && buffer[i] <= 122){
			//decode
			int valore = buffer[i];
			int key_index = (valore - 65);
			decoded[i] = key_buf[key_index];
			
		}else{
			decoded[i] = buffer[i];
		}
	}
	decoded[i] = '\0';
	char* decoded_text_ = (char*)calloc(size1, sizeof(char));
	strcpy(decoded_text_, decoded);
	*decoded_text = decoded_text_;	
}
