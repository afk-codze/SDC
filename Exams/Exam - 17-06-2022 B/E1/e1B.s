.globl crc32b
										#		//ebx, esi. edi. ebp
										#		//variablie locale in stack --> 4 byte
										#		//chiamata a funzione --> 8 byte

crc32b:									#		int crc32b(char *bytes, int n) {		
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $4, %esp 						#variabile locale
	subl $8, %esp 						#parametri funzione	
	movl 32(%esp), %ebx					#			char* ebx = bytes;
										#			//n lo recupero sempre dallo stack
	xorl %ecx, %ecx						#			int ecx = ~0; // operazione: not
	notl %ecx
	movl %ecx, %esi						#			int esi = ecx; //crc
L:    
	cmpl $0, 36(%esp)					#			if (n == 0) goto E;	
	je E
										#			int value; //in stack
	movsbl (%ebx), %edi					#			int edi = *ebx;// attenzione! --> promozione intera
	incl %ebx							#			ebx++; 
	movl %esi, %ebp						#			int ebp = esi;
	xorl %edi, %ebp						#			ebp = ebp ^ edi;
	andl $0xFF, %ebp					#			ebp = ebp & 0xFF;
    movl %ebp, %edx						#			int edx = ebp;		
	leal 8(%esp), %eax					#			int* eax = &value; 
	movl %eax, (%esp)					#			//muovo parametri in stack
	movl %edx, 4(%esp)
	call get_constant					#			get_constant(eax, edx);//indirizzo di value leal stack
	sarl $8, %esi						#			esi = (esi >> 8);
	xorl 8(%esp), %esi					#			esi = esi ^ value; 
	decl 36(%esp)						#			n--;
	jmp L								#			goto L;
			 
E:    
	movl %esi, %eax						#			int eax1 = esi;
	xorl %ecx, %ecx						#			ecx = ~0;
	notl %ecx	
	xorl %ecx, %eax						#			eax1 = eax1 ^ ecx;
	addl $12, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx		
	ret										#			return eax1;
	

