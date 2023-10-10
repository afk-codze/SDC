#include "e1A.h"

int* strings_are_upper(const char** array, int n) {
	
	//ebx esi edi ebp
	//ho una chiamata a funzione sizeof(int) = 4 --> 4 byte
	
	const char** ebx = array;
	//n in stack
    if (ebx != NULL) goto I1;
    int* eax = NULL;
    goto E;
    
I1:   
    if (n > 0) goto I2; 
    eax = 	NULL;
    goto E;
    
I2:  
	//passo parametri in stack
    eax = malloc(sizeof(int) * n);
    int* esi = eax;
    int ebp = 0;
L1:
    if (ebp >= n) goto E1;
    const char* edi = ebx[ebp]; // INDIRIZZO 
    esi[ebp] = 1; //intero
        
L2:
    if (*edi == 0) goto E2; //*edi e un char
    //passo parametri in stack --> con promozione intera
    int eax1 = isupper(*edi);
    
    if (eax1 != 0) goto E3;
    esi[ebp] = 0; //intero
    goto E2;
E3:
    edi += 1; //incl
    goto L2;
E2:
    ebp++; //intero
    goto L1;    
E1:
	eax = esi;	//indirizzo
E:
    return eax;
}
