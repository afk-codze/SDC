#include "e1B.h"
//ebx, esi, edi ebp
//ci sono due chiamate a funzione --> la chiamata con piu parametri richiede 8 byte di spazio in stack


int count_matching_vars(char** vars, char* pattern) {
	
	char** ebx = vars;
	char* esi = pattern;
	int eax;
    if (ebx == NULL){
	eax = -1;
    goto H;
	}
    if (esi == NULL){
    eax = -1;
    goto H;
	}
    int edi = 0; //count
L:
    if (*ebx == NULL) goto E;
    char* ecx = *ebx;
    //metto param in stack
    char* eax1 = getenv(ecx);
    char* ebp =  eax1; 
    if (ebp == NULL) goto E1;
    //metto 2 parametri in stack
    eax1 = strstr(ebp, esi);
    if (eax1 == NULL)goto E1;
    edi += 1;        
E1:           
    ebx++;
    goto L;
E:
    eax = edi;
H:
    return eax;
}
