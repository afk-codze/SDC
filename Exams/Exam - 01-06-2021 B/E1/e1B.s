.globl adler32_simplified
									#		//ebx, esi
									#		//non ci sono chiamate a funzione

adler32_simplified:					#		unsigned int adler32_simplified(unsigned char* data, int len){
	pushl %ebx
	pushl %esi
	pushl %edi			
	movl 16(%esp), %ebx				#			unsigned char* ebx = data;
	movl 20(%esp), %esi				#			int esi = len;
	movl $1, %eax					#			unsigned int eax = 1; // a
	xorl %ecx, %ecx					#			unsigned int ecx = 0; // b
	xorl %edx, %edx					#			int edx = 0;
L:
	cmpl %esi, %edx					#			if (edx >= esi) goto E;
	jge E
	movzbl (%ebx, %edx, 1), %edi	#			int edi = ebx[edx]; //-->promozione intera
	addl %edi, %eax					#			eax = (eax + edi);
	andl $0xFFFF, %eax				#			eax = eax & 0xFFFF;
	addl %eax, %ecx					#			ecx = (ecx + eax);
	andl $0xFFFF, %ecx				#			ecx = ecx & 0xFFFF;
	incl %edx						#			++edx;
	jmp L							#			goto L;
E:
	shll $16, %ecx					#			ecx = ecx << 16;
	orl %ecx, %eax					#			eax = eax | ecx;
	popl %edi
	popl %esi
	popl %ebx	
	ret								#			return eax;
		#		}
