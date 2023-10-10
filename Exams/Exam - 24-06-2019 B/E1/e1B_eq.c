//non vengono usate funzioni

int has_duplicates(short* v, unsigned n) {
	
    short* ebx = v;
    unsigned edi = n;
    unsigned ecx = 0; //i
    unsigned edx = 0; //j
    int eax = 0;
    
L:    
    if (ecx>=edi) goto E;
	edx=ecx+1;
	
L1:	
    if(edx>=edi) goto E1;    
    short esi = ebx[ecx];   
    if (esi != ebx[edx]) goto E2;
    eax = 1;
    goto E;

E2:
        
    ++edx;
    goto L1;
E1:        
    ++ecx;
    goto L;
E:        
    return eax;
}
