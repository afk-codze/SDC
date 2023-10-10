.globl is_prefix


is_prefix:									#int is_prefix(const char* s, const char* t) {
	
	
	movl 4(%esp), %ecx						#	const char* ecx = s;
	movl 8(%esp), %edx						#	const char* edx = t
L:	
		
	cmpb $0, (%ecx)							#	if(*ecx == 0) goto E; 
	je E
	cmpb $0, (%edx)							#	if(*edx == 0) goto E; 
	je E
	movb (%ecx), %al						#	char al = *ecx;
	cmpb (%edx), %al						#	if(al != *edx) goto E;
	jne E
	incl %ecx								#	ecx++; 
	incl %edx								#	edx++; //puntaotre a char inremento di 1
	jmp L									#	goto L;  
E:  
	xorl %eax, %eax
	cmpb $0, (%ecx)
	sete %al								#	int eax1 = *ecx == 0;
	ret										#   return eax1;

