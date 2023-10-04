.globl count_tokens
								#		//ebx esi edi ebp
								#		//8B per parametri

	count_tokens:						#		int count_tokens(char* str, const char* sep) {
		pushl %ebx
		pushl %esi
		pushl %edi
		pushl %ebp
		subl $8, %esp		
		movl 28(%esp), %ebx				#			char* ebx = str;
		movl 32(%esp), %esi				#			const char* esi = sep;
		xorl %edi, %edi					#			int edi = 0; //cnt
					
		movl %ebx, (%esp)				#			//passo i parametri in stack
		movl %esi, 4(%esp)
		call strtok
		movl %eax, %ebp					#			char* ebp = strtok(ebx, esi);
		
L:   
		cmpl $0, %ebp					#			if (ebp == NULL) goto E;
		je E
		incl %edi					#			edi++;
		movl $0, (%esp)					#			//passo parametri in stack
		movl %esi, 4(%esp)
		call strtok
		movl %eax, %ebp					#			ebp = strtok(NULL, esi);
		jmp L						#			goto L;
E:
		movl %edi, %eax					#			return edi;
		addl $8, %esp
		popl %ebp
		popl %edi
		popl %esi
		popl %ebx
		ret
								#		}
