#include "e1A.h"
#include <stdio.h>
#include <stdlib.h>

void init_matrix(short** m, unsigned n) {
	
	//ho una chiamata a funzione devo riservare spazio per i due parametri unsiged che prende
	//devo salvare le info che mi interessa che persistano in registri callee-saved --> e d c verranno sporcati
	//m deve persistere, n deve persistere i deve persistere e j deve persistere
	
	short** ebx = m;
	unsigned esi = n;
	unsigned edi = 0; //i 

L:  
    if (edi>=esi) goto E;
	unsigned ebp = 0; //j
		
K:		
	if (ebp>=esi) goto H;
	
	short* ecx = ebx[edi];
	short eax = value(edi,ebp);
	ecx[ebp] = eax;

    ++ebp;
    goto K;

H:
	++edi;
	goto L;
  
E:
     
}
