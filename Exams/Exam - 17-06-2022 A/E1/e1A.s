.globl crc32


									#//esi, edi, ebp, ebx
crc32:								#int crc32(char *bytes, int n) {
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	
	movl 20(%esp), %edi				#	char* edi = bytes;
	movl 24(%esp), %esi				#	int esi = n;
	xorl %edx, %edx					#   int edx = 0;

	movl $0xFFFFFFFF, %eax			#   int eax = 0xFFFFFFFF; // valore iniziale
L:   
	cmpl %esi, %edx					#   if (edx >= esi) goto E;
	jge E
			
	movsbl (%edi, %edx, 1), %ebp	#   int ebp = edi[edx]; // attenzione! --> promozione intera
		
	xorl %ebp, %eax					#   eax = eax ^ ebp; //xor
	xorl %ecx, %ecx					#   int ecx = 0;
		
L1:
	cmpl $8, %ecx					#   if (ecx >= 8) goto E2;
	jge E2
	movl %eax, %ebx					#	int ebx = eax;
    andl $1, %ebx					#	ebx = 1 & ebx;
	negl %ebx						#   ebx = -ebx; // operazione: negativo -> operatore NEG	
	sarl $1, %eax					#   eax = (eax >> 1);
	movl $0xEDB88320, %ebp			#   ebp =  0xEDB88320;
	andl %ebx, %ebp					#   ebp = ebp & ebx;
	xorl %ebp, %eax					#   eax = eax ^ ebp;
	incl %ecx						#   ecx++;
	jmp L1							#   goto L1;
       
E2:        
	incl %edx						#   edx++; //intero
	jmp L							#   goto L;
E:	
	not %eax
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret										#   return ~eax; // operazione: not
