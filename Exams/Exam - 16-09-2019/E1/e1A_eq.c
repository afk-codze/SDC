#include "e1A.h"
#include <string.h>

int is_prefix(const char* s, const char* t) {
	
	const char* ecx = s;
	const char* edx = t;
L:	
	
	if(*ecx == 0) goto E; // cl
	if(*edx == 0) goto E; // dl
	char al = *ecx;
	if(al != *edx) goto E;
	ecx++; 
	edx++; //puntaotre a char inremento di 1
	goto L;

E:  
	int eax1 = *ecx == 0;
    return eax1;
}
