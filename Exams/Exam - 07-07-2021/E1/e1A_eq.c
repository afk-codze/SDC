#include "e1A.h"
//chiamata a funzione riservo 4 byte
//ebx, esi, edi, ebp
//devo mettere i in stack
int suffix(const char* a, const char* b) {
	
	const char* ebp = a;
	const char* edi = b;//b lo recupero sempre dallo stack
    int eax = strlen(ebp); 
    int ebx = eax;	//alen
    eax = strlen(edi); 
    int esi = eax;	//blen
    int i; //in stack
    eax = 1;
    if (esi <= ebx) goto E;
    eax = 0;
    goto F;
E:	
	int edx = ebx;
	edx=edx-esi;
	i = edx;
L:
    if (i>=ebx) goto F;
    edx = i;
    char cl = ebp[edx];
    if (cl == *edi) goto K;
	eax = 0;
	goto F;
K:
    edi++; //puntatore a char
    i++; //intero
    goto L;
F:	
	return eax;
}
