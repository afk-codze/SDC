#include "e1A.h"
//%ebx, %esi, %edi, %ebp
//chiamata a funzione  --> 4byte
//n lo recupero dallo stack ogni volta!!
unsigned int* div_vectors(unsigned int* a, unsigned int* b, int n) {
	
	unsigned int* ebx = a;
	unsigned int* esi = b;
	
	
	unsigned int* eax;
	
    if (ebx == NULL){
		eax = NULL;
		goto E;
	} 
	if(esi == NULL){
		eax = NULL;
		goto E;
	}
	if(n == 0){
		eax = NULL;
		goto E;
	}
        
    int ecx = 32;
    ecx = ecx * n;
    //passo parametri in stack
    unsigned int* ebp = malloc(ecx);
    ecx = 0; //i
    
L:    
    if (ecx >= n) goto H;
	//devo settare edx con il bit piu significativo di eax oppure con 0 dato che e unsiged?
	//edx:eax/S 
	int eax1 = ebx[ecx];
	int edi = esi[ecx];
	//setto edx
    ebp[ecx] = eax1 / edi;  // usare idiv, attenzione a edx!
    ecx++;
    goto L;
    
H:
    eax = ebp;
E:
    return eax;
}
