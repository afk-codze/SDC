#include "e1A.h"
//ebx esi edi
//4B per k in stack
//4B per parametro func


unsigned adler32(unsigned char *data, unsigned len) {
	
	unsigned char* ebx = data;
	unsigned esi = len;
	
	unsigned eax2;
	
    if (ebx != NULL) goto I;
	eax2 = 0;
	goto E2;
I:	
    if (esi != 0) goto I2;
    eax2 = 0;
	goto E2;
I2:
    unsigned edi = 0; //b
    unsigned k; //k deve stare in stack 
    unsigned* eax1 = &k; //--> leal
    get_adler_constant(eax1);
    
	unsigned ecx = 1; //a
	
    unsigned ebp = 0;
L:    
    if (ebp >= esi) goto E; //--> confronto tra unsigned
	//divisione unsigned --> %edx:%eax / S --> %edx puo essere settato a 0
	int edx = 0; //setto edx = 0
	unsigned int eax = ebx[ebp]; //concateno eax con PROMOZIONE INTERA --> ebx[ebp] e char va promosso MOVZ!!	
	eax = ecx + eax;
    edx = (eax) % k; //sorgente puo essere memoria --> il resto della divisione viene restituito in edx
    ecx = edx;
        
    edx = 0; //resetto edx a 0
    eax = ecx;
    eax = eax + edi;
    edx = eax % k;    
    edi = edx;
    ++ebp; //intero
    goto L;

E:	
	edi = edi <<16;
	edi = edi | ecx;
	eax2 = edi;
E2:
    return eax2;
}
