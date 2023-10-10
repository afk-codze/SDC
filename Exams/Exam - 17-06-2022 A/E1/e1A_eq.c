#include "e1A.h"
#include <stdio.h>

//esi, edi, ebp, ebx
int crc32(char *bytes, int n) {

	char* edi = bytes;
	int esi = n;
    int edx = 0;

    int eax = 0xFFFFFFFF; // valore iniziale
L:   
    if (edx >= esi) goto E;
		
    int ebp = edi[edx]; // attenzione! --> promozione intera
    
    eax = eax ^ ebp; //xor
    int ecx = 0;
    
L1:
    if (ecx >= 8) goto E2;
    
    int ebx = eax;
    ebx = 1 & ebx;
    ebx = -ebx; // operazione: negativo -> operatore NEG	
    eax = (eax >> 1);
    ebp =  0xEDB88320;
    ebp = ebp & ebx;
    eax = eax ^ ebp;
    ecx++;
    goto L1;
       
E2:        
    edx++; //intero
    goto L;
E:
    return ~eax; // operazione: not
}
