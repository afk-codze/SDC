.globl suffix
	#//chiamata a funzione riservo 4 byte
	#//ebx, esi, edi, ebp


suffix:														#int suffix(const char* a, const char* b) {

	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $4, %esp											#lo uso prima per le chiamate a funzione poi per tenere i in stack
	
	movl 24(%esp), %ebp										#		const char* ebp = a;
	movl 28(%esp), %edi										#		const char* edi = b;//b lo recupero sempre dallo stack
	movl %ebp, (%esp)
	call strlen												#		int eax = strlen(ebp); 
	movl %eax, %ebx											#		int ebx = eax;	//alen
	movl %edi, (%esp)
	call strlen												#		eax = strlen(edi); 
	movl %eax, %esi											#		int esi = eax;	//blen
															#		int i; //in stack
	movl $1, %eax											#		eax = 1;
	cmpl %ebx, %esi											#		if (esi <= ebx) goto E;
	jle E
	xorl %eax, %eax											#		eax = 0;
	jmp F													#		goto F;
E:	
	movl %ebx, %edx											#		edx = ebx;
	subl %edx, %esi											#		edx=edx-esi;
	movl %edx, (%esp)										#		i = edx;
L:
	cmpl %ebx, (%esp)										#		if (i>=ebx) goto F;
	jge F
	movl (%esp), %edx										#		edx = i;
	movb (%ebp, %edx, 1), %cl								#		char cl = ebp[i];
	cmpb (%edi), %cl										#		if (cl == *edi) goto K;
	xorl %eax, %eax											#		eax = 0;
	jmp F													#		goto F;
K:
	incl %edi												#		edi++; //puntatore a char
	incl (%esp)												#		i++; //intero
	jmp L													#		goto L;
F:	
	addl $4, %esp
    popl %ebp
    popl %edi
    popl %esi
    popl %ebx
	ret#		return eax;
