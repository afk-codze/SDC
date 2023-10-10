#include "e1B.h"
//ebx, esi, edi
//non ci sono chiamate a funzione

unsigned int adler32_simplified(unsigned char* data, int len){
	
	unsigned char* ebx = data;
	int esi = len;
    unsigned int eax = 1; // a
    unsigned int ecx = 0; // b
    int edx = 0;
L:
    if (edx >= esi) goto E;
    
    int edi = ebx[edx]; //-->promozione intera
    eax = (eax + edi);
    eax = eax & 0xFFFF;
    ecx = (ecx + eax);
    ecx = ecx & 0xFFFF;
    ++edx;
    goto L;
E:
	ecx = ecx << 16;
	eax = eax | ecx;
    return eax;
}
