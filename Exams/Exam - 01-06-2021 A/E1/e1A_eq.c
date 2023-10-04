#include "e1A.h"
//ebx esi edi ebp
//8B per parametri

int count_tokens(char* str, const char* sep) {
	
	char* ebx = str;
	const char* esi = sep;
    int edi = 0; //cnt
    
    //passo i parametri in stack
    char* ebp = strtok(ebx, esi);
L:   
    if (ebp == NULL) goto E;
    edi++;
    //passo parametri in stack
    ebp = strtok(NULL, esi);
    goto L;
E:
	return edi;
}

