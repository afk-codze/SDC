#include "e1A.h"
#include <stdio.h>
// ebx, esi, edi, ebp 
//8 byte in stack --> i e rnd
//16 byte per parametri funzione

void rc4_encrypt(unsigned char *sbox, unsigned char *pt, unsigned char *ct){
	
	unsigned char bl = 0; //j
	unsigned char* edi = pt;
	unsigned char* ebp = ct;
    unsigned int esi = 0; //n
    unsigned int i = 0;//in stack
    unsigned char rnd; //in stack
	//sbox in stack
L:
    if (*edi == 0) goto E;
	unsigned int eax = i;
    eax = (eax + 1);
    eax = eax & 255;
    i = eax; 
    unsigned char* ecx = sbox;        
    unsigned char dl = ecx[eax];
    bl = bl + dl;
    //passo parametri in stack --> promozione intera di bl
    rc4_helper(ecx, eax, bl, &rnd); 
    dl = rnd; //valore in stack di rnd per ASM
    printf("|%c|", rnd);
    dl = dl ^ *edi;
    ebp[esi] = dl;      
    edi++;
    esi++;   
    goto L; 
E:
    //ret
}
