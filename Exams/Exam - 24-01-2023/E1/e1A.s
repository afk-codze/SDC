.globl strings_are_upper

strings_are_upper:								#	int* strings_are_upper(const char** array, int n) {
			
	pushl %ebx									#		//ebx esi edi ebp
	pushl %esi									#		//ho una chiamata a funzione sizeof(int) = 4 --> 4 byte
	pushl %edi
	pushl %ebp
	subl $4, %esp	
		
	movl 24(%esp), %ebx							#		const char** ebx = array;
												#		//n in stack
	cmpl $0, %ebx								#		if (ebx != NULL) goto I1;
	jne I1
	movl $0, %eax								#		int* eax = NULL;
	jmp E										#		goto E;
			
I1:   
	cmpl $0, 28(%esp)							#		if (n > 0) goto I2; 
	jg I2
	movl $0, %eax								#		eax = 	NULL;
	jmp E										#		goto E;
			
I2:  
	movl 28(%esp), %eax							#		//passo parametri in stack
	imul $4, %eax
	movl %eax, (%esp)
	call malloc									#		eax = malloc(sizeof(int) * n);
	movl %eax, %esi								#		int* esi = eax;
	xorl %ebp, %ebp								#		int ebp = 0;
L1:
	cmpl 28(%esp), %ebp							#		if (ebp >= n) goto E1;
	jge E1
				
	movl (%ebx,%ebp,4), %edi					#		const char* edi = ebx[ebp]; // INDIRIZZO 
	movl $1, (%esi,%ebp,4)						#		esi[ebp] = 1; //intero
				
L2:
	cmpb $0, (%edi)								#		if (*edi == 0) goto E2; //*edi e un char
	je E2
	movsbl (%edi), %eax
	movl %eax, (%esp)							#		//passo parametri in stack --> con promozione intera
	call isupper								#		int eax1 = isupper(*edi);
			
	cmpl $0, %eax								#		if (eax1 != 0) goto E3;
	jne E3
	movl $0, (%esi, %ebp, 4)					#		esi[ebp] = 0; //intero
	jmp E2										#		goto E2;
E3:
	incl %edi									#		edi += 1; //incl
	jmp L2										#		goto L2;
E2:
	incl %ebp									#		ebp++; //intero
	jmp L1										#		goto L1;    
E1:
	movl %esi, %eax								#		eax = esi;	//indirizzo
E:	
	addl $4, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret											#		return eax;
	
