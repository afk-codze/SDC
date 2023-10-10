.globl adler32
										#		//ebx esi edi ebp
										#		//4B per k in stack
										#		//4B per parametro func
adler32:								#		unsigned adler32(unsigned char *data, unsigned len) {
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $8, %esp
	movl 28(%esp), %ebx					#			unsigned char* ebx = data;
	movl 32(%esp), %esi					#			unsigned esi = len;
										#			unsigned eax2;	
	cmpl $0, %ebx						#			if (ebx != NULL) goto I; //compare unsigned
	jne I
	movl $0, %eax						#			eax2 = 0;
	jmp E2								#			goto E2;
I:	
	cmpl $0, %esi						#			if (esi != 0) goto I2;	//compare unsigned
	jne I2
	movl $0, %eax						#			eax2 = 0;
	jmp E2								#			goto E2;
I2:
	xorl %edi, %edi						#			unsigned edi = 0; //b
										#			unsigned k; //k deve stare in stack 
	leal 4(%esp), %eax					#			unsigned* eax1 = &k; //--> leal
	movl %eax, (%esp)					# 			//muovo i parametri in stack
	call get_adler_constant				#			get_adler_constant(eax1);		
	movl $1, %ecx						#			unsigned ecx = 1; //a		
	xorl %ebp, %ebp						#			unsigned ebp = 0;
L:    
	cmpl %esi, %ebp						#			if (ebp >= esi) goto E; //--> confronto tra unsigned
	jae E
										#			//divisione unsigned --> %edx:%eax / S --> %edx puo essere settato a 0
	xorl %edx, %edx						#			int edx = 0; //setto edx = 0
	movzbl (%ebx, %ebp, 1), %eax		#			unsigned int eax = ebx[ebp]; //concateno eax con PROMOZIONE INTERA --> ebx[ebp] e char va promosso MOVZ!!	
	addl %ecx, %eax						#			eax = ecx + eax;
	divl 4(%esp)						#			edx = (eax) % k; //sorgente puo essere memoria --> il resto della divisione viene restituito in edx
	movl %edx, %ecx						#			ecx = edx;				
	xorl %edx, %edx						#			edx = 0; //resetto edx a 0
	movl %ecx, %eax						#			eax = ecx;
	addl %edi, %eax						#			eax = eax + edi;
	divl 4(%esp)						#			edx = eax % k;    
	movl %edx, %edi						#			edi = edx;
	incl %ebp							#			++ebp; //intero
	jmp L								#			goto L;
E:	
	shll $16, %edi						#			edi = edi <<16;
	orl %ecx, %edi						#			edi = edi | ecx;
	movl %edi, %eax						#			eax2 = edi;
E2:
	addl $8, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret										#			return eax2;
	

