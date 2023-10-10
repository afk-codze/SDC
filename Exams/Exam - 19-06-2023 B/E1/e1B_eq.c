#include "e1B.h"

//ebx esi edi ebp
//spazio in stack per i --> 4byte --> sbox sta dove stanno i parametri
//chiamata a funzione da 12 byte
//E TUTTO UNSIGNED

void rc4_encrypt_rev(unsigned char *sbox, unsigned char *pt, unsigned char *ct){
	
	unsigned char* esi = pt;
	unsigned char* edi = ct;
    unsigned char* ebp = esi;
    //passo argomenti in stack
    int eax = strlen(esi);
    ebp = ebp + eax;
    ebp = ebp - 1;

	unsigned int i = 0;//metto in stack 
    unsigned char bl = 0;//j
L:
    if (ebp < esi) goto E;
	eax = i;//prendo ogni volta i dallo stack
    eax = (eax + 1);
    eax = eax & 255;  
    i = eax;   //aggiorno valore di i in stack   
        
    unsigned char* edx = sbox; //lo prendo dallo stack              
    bl = bl + edx[eax]; 
       
        //passo parametri in stack
    unsigned char al =  rc4_helper(edx, eax, bl);
    unsigned char dl = *ebp;
    al = al ^ dl;
    *edi = al;  
    ebp--;
    edi++;
    goto L;
E:
    //ret
}
