#include "e1A.h"

//ho una chiamata a funzione devo fare spazio per i 64 bit di parametri in stack
//ebx, esi, edi + 2 parametri
int most_freq_char(const char* s, int* map) {
	
	const char* edi = s;
	int* esi = map;
    
    clear(map, 256);  
L:    
    if (*edi == 0) goto E;
	int edx = (int)*edi; //promozione intera
	esi[edx]++;
	edi++;
	goto L;
E:    
    int ecx = 0; //i
    int eax = 0; //max
    
L1:
    if (ecx>=256) goto E1;  
    int ebx = esi[ecx];
    if (ebx <= esi[eax]) goto E2;
	eax = ecx; 
E2:    
    ++ecx;
    goto L1;
        
E1: 
    return eax;
}
