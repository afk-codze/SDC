#include "e1A.h"
//ebx, esi, edi, ebp
//chiamata a funzione che prende 1 parametro da 32bit
//alra chiamata a funzione che prende 1 parametro da 32bit --> indirizzo di memoria char*

int* count_vars(char** vars, int n) {
	
	
	char** ebx = vars; 
	int esi = n;
    int edi; //i
    int* eax1;
    int* ebp;
    
    if (ebx == NULL){
    ebp = NULL;
	goto E;
	}
	
    if (esi <= 0){
	ebp = NULL;
	goto E;
	}
	
	
    //sposto dati in stack
    int edx = 32;
    edx = edx * esi;
  
    eax1 = malloc(edx); //out
    ebp = eax1;
    edi = 0;
L:
    if (edi >= esi) goto E; //interi
	char* ecx = ebx[edi];
	//passo i dati in stack
	char* eax = getenv(ecx);
    if (eax == NULL) goto E2;
    ebp[edi] = 1;
    goto E3;
E2:
    ebp[edi] = 0;
E3:      
    edi++; //intero
    goto L;
E:   
    eax1 = ebp;
    return eax1;
}
