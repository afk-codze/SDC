#include "e1A.h"
//ebx esi edi
//2 chiamate a funzione --> riservo 4 B


char* str_to_upper(const char* s) {
	
	const char* ecx = s;
    if (ecx != NULL) goto E;
    char* eax = NULL;
    goto F;
    
E:   
    //passo argomenti in stack
    eax = strdup(ecx); 
    char* ebx = eax; //s_copy
    char* esi = ebx; //copy
L:
    if (*esi == 0) goto H; // --> *esi = char
    //passo argomenti in stack
    char eax2 = *esi; //promozione intera 
    char eax1 = toupper(eax2); 
    char edi = eax1;
    *esi = edi;
    esi++; //esi = char*
    goto L;
H:
    eax = ebx; //eax = char*
F:   
    return eax;
}
