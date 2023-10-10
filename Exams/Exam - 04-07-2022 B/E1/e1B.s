.globl count_matching_vars
										#	//ebx, esi, edi ebp
										#	//ci sono due chiamate a funzione --> la chiamata con piu parametri richiede 8 byte di spazio in stack
count_matching_vars:					#	int count_matching_vars(char** vars, char* pattern) {

	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $8, %esp
		
	movl 28(%esp), %ebx					#		char** ebx = vars;
	movl 32(%esp), %esi					#		char* esi = pattern;
										#		int eax;
	cmpl $0, %ebx						#		if (ebx == NULL){
	movl $-1, %eax						#		eax = -1;
	je H								#		goto H;
										#		}
	cmpl $0, %esi						#		if (esi == NULL){
	movl $-1, %eax						#		eax = -1;
	je H								#		goto H;
										#		}
	xorl %edi, %edi						#		int edi = 0; //count
L:
	cmpl $0, (%ebx)						#		if (*ebx == NULL) goto E;
	je E
	movl (%ebx), %ecx					#		char* ecx = *ebx;
	movl %ecx, (%esp)					#		//metto param in stack
	call getenv							#		char* eax1 = getenv(ecx);
	movl %eax, %ebp						#		char* ebp =  eax1; 
	cmpl $0, %ebp						#		if (ebp == NULL) goto E1;
	je E1
	movl %ebp, (%esp)					#		//metto 2 parametri in stack
	movl %esi, 4(%esp)
	call strstr							#		eax1 = strstr(ebp, esi);
	cmpl $0, %eax						#		if (eax1 == NULL)goto E1;
	je E1
	incl %edi							#		edi += 1;        
E1:           
	addl $4, %ebx						#		ebx++; 
	jmp L								#		goto L;
E:
	movl %edi, %eax						#		eax = edi;
H:
	addl $8, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret														#		return eax;

