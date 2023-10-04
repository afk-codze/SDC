.globl div_vectors
											#		//%ebx, %esi, %edi, %ebp
											#		//chiamata a funzione  --> 4byte
											#		//n lo recupero dallo stack ogni volta!!
div_vectors:										#		unsigned int* div_vectors(unsigned int* a, unsigned int* b, int n) {
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $4, %esp
	movl 24(%esp), %ebx								#			unsigned int* ebx = a;
	movl 28(%esp), %esi								#			unsigned int* esi = b;
											#			unsigned int* eax;
	cmpl $0, %ebx									#			if (ebx == NULL){
	movl $0, %eax									#				eax = NULL;
	je E										#				goto E;
											#			} 
	cmpl $0, %esi									#			if(esi == NULL){
	movl $0, %eax									#				eax = NULL;
	je E										#				goto E;
											#			}
	cmpl $0, 32(%esp)								#			if(n == 0){
	movl $0, %eax									#				eax = NULL;
	je E										#				goto E;
											#			}				
	movl $32, %ecx									#			int ecx = 32;
	imull 32(%esp), %ecx								#			ecx = ecx * n;
	movl %ecx, (%esp)								#			//passo parametri in stack
	call malloc									#			unsigned int* ebp = malloc(ecx);
	movl %eax, %ebp									#			ebp = eax;
	xorl %ecx, %ecx									#			ecx = 0; //i	
L:    
	cmpl 32(%esp), %ecx								#			if (ecx >= n) goto H;
	jge H
	movl (%ebx, %ecx, 4), %eax							#			int eax1 = ebx[ecx];
	movl %eax, %edx									#			//devo settare edx con il bit piu significativo di eax
	sarl $31, %edx									#			//setto edx
											#			//edx:eax/S 
	movl (%esi, %ecx, 4), %edi							#			int edi = esi[ecx];
	idivl %edi									#			ebp[ecx] = eax1 / edi;  // usare idiv, attenzione a edx!
	movl %eax, (%ebp, %ecx, 4)
	incl %ecx									#			ecx++;
	jmp L										#			goto L;
H:
	movl %ebp, %eax									#			eax = ebp;
E:
	addl $4, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx	
	ret										#			return eax;
	
