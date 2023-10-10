.globl rc4_encrypt
									#		// ebx, esi, edi, ebp 
									#		//8 byte in stack --> i e rnd
									#		//16 byte per parametri funzione

rc4_encrypt:						#		void rc4_encrypt(unsigned char *sbox, unsigned char *pt, unsigned char *ct){
	
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $24, %esp
				
	xorb %bl, %bl					#			unsigned char bl = 0; //j
	movl 48(%esp), %edi				#			unsigned char* edi = pt;
	movl 52(%esp), %ebp				#			unsigned char* ebp = ct;
	xorl %esi, %esi					#			unsigned int esi = 0; //n
	movl $0, 20(%esp)				#			unsigned int i = 0;//in stack
									#			unsigned char rnd; //in stack
									#			//sbox in stack
L:
	cmpb $0, (%edi)					#			if (*edi == 0) goto E;
	je E
	movl 20(%esp), %eax				#			unsigned int eax = i;
	incl %eax						#			eax = (eax + 1);
	andl $255, %eax					#			eax = eax & 255;
	movl %eax, 20(%esp)				#			i = eax; 
	movl 44(%esp), %ecx				#			unsigned char* ecx = sbox;        
	movb (%ecx, %eax, 1), %dl		#			unsigned char dl = ecx[eax];
	addb %dl, %bl					#			bl = bl + dl;
	movl %ecx, (%esp)				#			//passo parametri in stack --> promozione intera di bl
	movl %eax, 4(%esp)
	movzbl %bl, %eax
	movl %eax, 8(%esp)
	leal 16(%esp), %eax
	movl %eax, 12(%esp)
	call rc4_helper					#			rc4_helper(sbox, eax, bl, &rnd); 
	movb 16(%esp), %dl				#			dl = rnd; //valore in stack di rnd per ASM
	xorb (%edi), %dl				#			dl = dl ^ *edi;
	movb %dl, (%ebp, %esi, 1)		#			ebp[esi] = dl;      
	incl %edi						#			edi++;
	incl %esi						#			esi++;   
	jmp L							#			goto L; 
E:
	addl $24, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx
	ret


