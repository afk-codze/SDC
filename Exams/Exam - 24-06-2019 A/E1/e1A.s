.globl init_matrix

init_matrix:						#void init_matrix(short** m, unsigned n) {
	
									#	//ho una chiamata a funzione devo riservare spazio per i due parametri unsiged che prende
									#	//devo salvare le info che mi interessa che persistano in registri callee-saved --> e d c verranno sporcati
									#	//m deve persistere, n deve persistere i deve persistere e j deve persistere
	
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $8, %esp
	
									#primo parametro sta a 28(%esp)
	
	movl 28(%esp), %ebx				#	short** ebx = m;
	movl 32(%esp), %esi				#	unsigned esi = n;
	xorl %edi, %edi					#	unsigned edi = 0; //i 

L:  
	cmpl %esi, %edi				#   if (edi>=esi) goto E;
	jae E
	xorl %ebp, %ebp					#	unsigned ebp = 0; //j
			
K:		
	cmpl %esi, %ebp					#	if (ebp>=esi) goto H;
	jae H
							#	//unsigned sono da 32 bit (4 byte) dunque non devo fare promozione intera										
	movl %edi, (%esp)
	movl %ebp, 4(%esp)
	call value						#	short eax = value(edi,ebp);
	
	movl (%ebx, %edi, 4), %ecx		#	short* ecx = ebx[edi];
	movw %ax, (%ecx, %ebp, 2)		#	ecx[ebp] = eax;
	
	incl %ebp						#    ++ebp;
	jmp K							#    goto K;

H:
	incl %edi						#	++edi;
	jmp L							#	goto L;
	  
E:
	addl $8, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
     
