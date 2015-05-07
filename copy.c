#include <stdlib.h>
#include <stdint.h>

void memcpy(void *dst, void *src, unsigned long int len);

void main() {
	void *istart = (void*)0x602000;
	void *ostart = NULL;
	//istart = (void*)malloc(0x1b);

	memcpy(istart, (void*)0x602000, 0x1b);

	asm("mov %1, %0\n"
	    "jmp *%1\n"
			: "=r" (ostart)
			: "r" (istart));
}

void memcpy(void *dst, void *src, unsigned long int len) {
	unsigned long int i = 0;
	for (i = 0; i<len; i++) {
		((uint8_t*)(dst))[i] = ((uint8_t*)(src))[i];
	}
	return;
}
