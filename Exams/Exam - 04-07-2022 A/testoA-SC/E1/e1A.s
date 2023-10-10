.globl count_vars
								#		//ebx, esi, edi, ebp
								#		//chiamata a funzione che prende 1 parametro da 32bit
								#		//alra chiamata a funzione che prende 1 parametro da 32bit --> indirizzo di memoria char*

count_vars:						#		int* count_vars(char** vars, int n) {
	pushl %ebx
	pushl %edi
	pushl %esi
	pushl %ebp
	subl $4, %esp
	movl 24(%esp), %ebx			#			char** ebx = vars; 
	movl 28(%esp), %esi			#			int esi = n;
								#			int edi; //i
								#			int* eax1;
								#			int* ebp;
	cmpl $0, %ebx				#			if (ebx == NULL){
	movl $0, %ebp				#			ebp = NULL;	
	je E						#			goto E;
								#			}
	cmpl $0, %esi				#			if (esi <= 0){
	movl $0, %ebp				#			ebp = NULL;
	jle	E						#			goto E;
								#			}
	movl $32, %edx				#			int edx = 32;
    imull %esi, %edx			#			edx = edx * esi;
	movl %edx, (%esp)			#			//sposto dati in stack
	call malloc					#			eax1 = malloc(edx); //out
	movl %eax, %ebp				#			ebp = eax1;
	xorl %edi, %edi				#			edi = 0;
L:
	cmpl %esi, %edi				#			if (edi >= esi) goto E; //interi
	jge E
	movl (%ebx, %edi, 4), %ecx	#			char* ecx = ebx[edi];
	movl %ecx, (%esp)			#			//passo i dati in stack
	call getenv					#			char* eax = getenv(ecx);
	cmpl $0, %eax				#			if (eax == NULL) goto E2;
	je E2
	movl $1, (%ebp, %edi, 4)	#			ebp[edi] = 1;
	jmp E3						#			goto E3;
E2:
	movl $0, (%ebp, %edi, 4)	#			ebp[edi] = 0;
E3:      
	incl %edi					#			edi++; //intero
	jmp L						#			goto L;
E:   
	movl %ebp, %eax				#			eax1 = ebp;
	addl $4, %esp
	popl %ebp
	popl %esi
	popl %edi
	popl %ebx
	ret							#			return eax1;
