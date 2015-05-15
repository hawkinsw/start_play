#include <stdlib.h>
#include <stdint.h>

void memcpy(void *dst, void *src, unsigned long int len);

void main() {
	void *istart = (void*)0x602000;
	void *ostart = NULL;
	void *rdx = NULL;
	//istart = (void*)malloc(0x1b);

	asm("mov %%rdx, %0\n"
	    : "=r" (rdx)
			:
			: "rdx");

	memcpy(istart, (void*)0x602000, 0x1b);

	asm("mov %0, %%rdx\n"
	    :
			: "r" (rdx)
			: "rdx");

	asm("mov %%rbp, %%rsp\n"
	    "add $8, %%rsp\n"
	    :
			:
			:);

	asm("mov %1, %0\n"
	    "jmp *%1\n"
			: "=r" (ostart)
			: "r" (istart)
			: "rdx");
}

void memcpy(void *dst, void *src, unsigned long int len) {
	unsigned long int i = 0;
	for (i = 0; i<len; i++) {
		((uint8_t*)(dst))[i] = ((uint8_t*)(src))[i];
	}
	return;
}
