.globl has_duplicates


has_duplicates:							#int has_duplicates(short* v, unsigned n) {
	pushl %ebx
	pushl %edi
	pushl %esi
	movl 16(%esp), %esi					#    short* ebx = v;
	movl 20(%esp), %edi					#    unsigned edi = n;
	xorl %ecx, %ecx						#    unsigned ecx = 0; //i
	xorl %edx, %edx						#    unsigned edx = 0; //j
	xorl %eax, %eax						#    int eax = 0;
L:    
	cmpl %edi, %ecx						#    if (ecx>=edi) goto E;
	jae E
	movl $1, %edx						#    edx=ecx+1;
	addl %ecx, %edx
L1:	
	cmpl %edi, %edx						#    if(edx>=edi) goto E1;    
	jae E1
	movw (%esi, %ecx, 2), %bx			#    short esi = ebx[ecx];   
	cmpw (%esi, %edx, 2), %bx			#    if (esi != ebx[edx]) goto E2;
	jne E2
	movl $1, %eax						#    eax = 1;
	jmp E								#    goto E;
E2:	
	incl %edx							#    ++edx;
	jmp L1								#    goto L1;
E1:        
	incl %ecx							#    ++ecx;
	jmp L								#    goto L;
E: 
	popl %esi
	popl %edi
	popl %ebx       
	ret									#    return eax;

