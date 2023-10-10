.globl str_to_upper
											#		//ebx esi edi
											#		//2 chiamate a funzione --> riservo 4 B


str_to_upper:								#		char* str_to_upper(const char* s) {
	pushl %ebx 
	pushl %esi
	pushl %edi 
	subl $4, %esp
	
	movl 20(%esp), %ecx						#			const char* ecx = s;
	cmpl $0, %ecx							#			if (ecx != NULL) goto E;
	jne E
	xorl %eax, %eax							#			char* eax = NULL;
	jmp F									#			goto F;
E:   
	movl %ecx, (%esp)						#			//passo argomenti in stack
	call strdup								#			eax = strdup(ecx); 
	movl %eax, %ebx							#			char* ebx = eax; //s_copy
	movl %ebx, %esi							#			char* esi = ebx; //copy
L:
	cmpb $0, (%esi)							#			if (*esi == 0) goto H; // --> *esi = char
	je H
	movsbl (%esi), %eax						#			//passo argomenti in stack
	movl %eax, (%esp)
	call toupper							#			char eax1 = toupper(eax); //c --> *esi = char
	movb %al, (%esi)						#			*esi = edi;
	incl %esi								#			esi++; //esi = char*
	jmp L									#			goto L;
H:
	movl %ebx, %eax							#			eax = ebx; //eax = char*
F:   	
	addl $4, %esp
	popl %edi
	popl %esi
	popl %ebx
	ret										#			return eax;
	
