.globl check_quiz

											#		//n lo recupero sempre dallo stack
											#		//ebx esi edi ebp
											#		//4B per parametri
check_quiz:									#		int* check_quiz(char** answers, char* solution, int n) {
				
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $4, %esp		
																			
	movl 24(%esp), %esi						#			char** esi = answers;
	movl 28(%esp), %edi						#			char* edi = solution;
											#			int* eax1;
										
	cmpl $0, %esi							#			if (esi != NULL) goto H1; 
	jne H1
	movl $0, %eax							#			eax1 = NULL;
	jmp E									#			goto E;

H1: 
	cmpl $0, %edi							#			if (edi != NULL) goto H2; 
	jne H2
	movl $0, %eax							#			eax1 = NULL;
	jmp E									#			goto E;
									   
H2: 
	cmpl $0, 32(%esp)						#			if (n > 0) goto H3; 
	jg H3 
	movl $0, %eax							#			eax1 = NULL;
	jmp E									#			goto E;

H3:  
	movl $32, %edx							#			int edx1 = 32;
	imul 32(%esp), %edx						#			edx1 = edx1*n;
	movl %edx, (%esp)						#			//sposto paramteri in stack
	call malloc								#			eax1 = malloc(edx1);//unica chiamata a funzione
	movl %eax, %ebp							#			int* ebp = eax1;
										
	xorl %edx, %edx							#			int edx = 0; //i
L1:   
	cmpl 32(%esp), %edx						#			if(edx >= n) goto E1;
	jge E1										
	movl $0, (%ebp, %edx, 4)				#			ebp[edx] = 0;
	xorl %ecx, %ecx							#			int ecx = 0; //j
										
L2:
	cmpl $4, %ecx							#			if (ecx >= 4) goto E2;
	jge E2
	movl (%esi, %edx, 4), %eax				#			char* eax = esi[edx]; // attenzione: e' un puntatore! 
	movb (%eax, %ecx, 1), %bl				#			char ebx = eax[ecx];
	cmpb (%edi, %ecx, 1), %bl				#			if (ebx != edi[ecx]) goto E3; // attenzione: confronto di caratteri!
	jne E3
	incl (%ebp, %edx, 4)					#			ebp[edx] += 1; //char
E3:            
	incl %ecx								#			ecx++;
	jmp L2									#			goto L2;
E2:				
	incl %edx								#			edx++;
	jmp L1									#			goto L1;
E1:

	movl %ebp, %eax							#			eax1 = ebp;
E:
	addl $4, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret													#			return eax1;
														

