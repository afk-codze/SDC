#include "e1A.h"


//n lo recupero sempre dallo stack
//ebx esi edi ebp
//4B per parametri
int* check_quiz(char** answers, char* solution, int n) {
	
	
	char** esi = answers;
	char* edi = solution;
	int* eax1;
	
    if (esi != NULL) goto H1; 
	eax1 = NULL;
	goto E;

H1: 
    if (edi != NULL) goto H2; 
    eax1 = NULL;
	goto E;
   
H2: 
    if (n > 0) goto H3;  
    eax1 = NULL;
	goto E;

H3:  
	int edx1 = 32;
	edx1 = edx1*n;
	//sposto paramteri in stack
    eax1 = malloc(edx1);//unica chiamata a funzione
	int* ebp = eax1;
    
    int edx = 0; //i
L1:   
    if(edx >= n) goto E1;
		
    ebp[edx] = 0;
    int ecx = 0; //j
    
L2:
    if (ecx >= 4) goto E2;
    char* eax = esi[edx]; // attenzione: e' un puntatore! 
    char ebx = eax[ecx];
    if (ebx != edi[ecx]) goto E3; // attenzione: confronto di caratteri!
    ebp[edx] += 1; //char
E3:            
    ecx++;
    goto L2;
E2:
        
    edx++;
    goto L1;
        
E1:

	eax1 = ebp;
E:
    return eax1;
}
