.globl rc4_encrypt_rev
												#		//ebx esi edi ebp
												#		//spazio in stack per i --> 4byte --> sbox sta dove stanno i parametri
												#		//chiamata a funzione da 12 byte
												#		//E TUTTO UNSIGNED

rc4_encrypt_rev:								#		void rc4_encrypt_rev(unsigned char *sbox, unsigned char *pt, unsigned char *ct){
	
	pushl %ebx
	pushl %esi
	pushl %edi
	pushl %ebp
	subl $4, %esp #i
	subl $12, %esp #func
				
	movl 40(%esp), %esi							#			unsigned char* esi = pt;
	movl 44(%esp), %edi							#			unsigned char* edi = ct;
	movl %esi, %ebp								#			unsigned char* ebp = esi;
	movl %esi, (%esp)							#			//passo argomenti in stack
	call strlen									#			int eax = strlen(esi);
	addl %eax, %ebp								#			ebp = ebp + eax;
	decl %ebp									#			ebp = ebp - 1;

	movl $0, 12(%esp)							#			unsigned int i = 0;//metto in stack 
	movb $0, %bl								#			unsigned char bl = 0;//j
L:
	cmpl %esi, %ebp								#			if (ebp < esi) goto E;
	jb E
	movl 12(%esp), %eax							#			eax = i;//prendo ogni volta i dallo stack
	incl %eax									#			eax = (eax + 1);
	andl $255, %eax								#			eax = eax & 255;  
	movl %eax, 12(%esp)							#			i = eax;   //aggiorno valore di i in stack   
					
	movl 36(%esp), %edx							#			unsigned char* edx = sbox; //lo prendo dallo stack              
	addb (%edx, %eax, 1), %bl					#			bl = bl + edx[eax]; 
				   
	movl %edx, (%esp)							#				//passo parametri in stack
	movl %eax, 4(%esp)
	movzbl %bl, %eax
	movl %eax, 8(%esp)
	
	call rc4_helper								#			unsigned char al =  rc4_helper(edx, eax, bl);
	movb (%ebp), %dl							#			unsigned char dl = *ebp;
	xorb %dl, %al								#			al = al ^ dl;
	movb %al, (%edi)							#			*edi = al;  
	decl %ebp									#			ebp--;
	incl %edi									#			edi++;
	jmp L										#			goto L;
E:	
	addl $16, %esp
	popl %ebp
	popl %edi
	popl %esi
	popl %ebx 
	ret 								#			//ret
	
