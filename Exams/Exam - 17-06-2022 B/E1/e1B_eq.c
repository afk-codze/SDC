#include "e1B.h"
#include <stdio.h>
//ebx, esi. edi. ebp
//variablie locale in stack --> 4 byte
//chiamata a funzione --> 8 byte

int crc32b(char *bytes, int n) {
	
	char* ebx = bytes;
	//n lo recupero sempre dallo stack
    int ecx = ~0; // operazione: not
    int esi = ecx; //crc
L:    
    if (n == 0) goto E;	
    int value; //in stack
    int edi = *ebx; // attenzione! --> promozione intera
    ebx++; 
    int ebp = esi;
    
    ebp = ebp ^ edi;
    ebp = ebp & 0xFF;
    int edx = ebp;
    int* eax = &value;
    //muovo parametri in stack
    get_constant(eax, edx);//indirizzo di value leal stack
    esi = (esi >> 8);
    esi = esi ^ value; 
    n--;
    goto L;
 
E:    
	int eax1 = esi;
	ecx = ~0;
	eax1 = eax1 ^ ecx;
    return eax1;
}
