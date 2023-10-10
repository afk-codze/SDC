.globl most_freq_char

											#//ho una chiamata a funzione devo fare spazio per i 64 bit di parametri in stack
											#//ebx, esi, edi + 2 parametri
most_freq_char:								#int most_freq_char(const char* s, int* map) {
	
	pushl %ebx
	pushl %edi
	pushl %esi
	subl $8, %esp
		
	movl 24(%esp), %edi						#	const char* edi = s;
	movl 28(%esp), %esi						#	int* esi = map;
	
	
	movl %esi, (%esp)
	movl $256, 4(%esp)
	call clear								#   clear(map, 256);  
L:  
	movsbl (%edi), %ecx						#   int ecx = *edi;
	testl %ecx, %ecx						#   if (ecx == 0) goto E;
	je E
	movl %ecx, %edx							#	int edx = ecx; //promozione intera
	incl (%esi, %edx, 4)					#	esi[edx]++;
	incl %edi								#	edi++;
	jmp L									#	goto L;
E:    
	xorl %ecx, %ecx							#   int ecx = 0; //i
	xorl %eax, %eax							#   int eax = 0; //max
		
L1:
	cmpl $256, %ecx							#   if (ecx>=256) goto E1;
	jge E1  
	movl (%esi, %ecx, 4), %ebx				#   int ebx = esi[ecx];
	cmpl (%esi, %eax, 4), %ebx				#   if (ebx <= esi[eax]) goto E2;
	cmovgl %ecx, %eax						#	eax = ecx; --> AVEVO FATTO ERRORE QUA!! MOV CONDIZIONALE
E2:    
	incl %ecx								#   ++ecx;
	jmp L1									#   goto L1;
			
E1: 
	addl $8, %esp
	popl %esi
	popl %edi
	popl %ebx
	ret										#   return eax;

