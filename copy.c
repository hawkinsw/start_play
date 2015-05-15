#include <stdlib.h>
#include <stdint.h>

void memcpy(void *dst, void *src, unsigned long int len);

void main() {
	void *istart = (void*)0x602000;
	void *ostart = NULL;
	void *rdx = NULL;

	/*
	 * Store rdx so that it's not killed
	 * when we invoke other functions.
	 */
	asm("mov %%rdx, %0\n"
	    : "=r" (rdx)
			:
			: "rdx");

	/*
	 * Using commands from Makefile, we know that
	 * there is going to be some code at 0x602000
	 * that will do "something" and eventually
	 * transfer control to the entry point of the
	 * original program.
	 *
	 * This memcpy() is a nop, but we do it just to
	 * show that we can call functions here.
	 *
	 * Eventually, we are just going to jump
	 * to that code and hope that it does the right
	 * thing.
	 */
	memcpy(istart, (void*)0x602000, 0x1b);

	/*
	 * Restore rdx from where we stored it.
	 */
	asm("mov %0, %%rdx\n"
	    :
			: "r" (rdx)
			: "rdx");

	/*
	 * Reload rsp with its address when this
	 * function began. In essence, we are
	 * popping the stack from this function.
	 * We want the stack back because it contains
	 * argv.
	 */
	asm("mov %%rbp, %%rsp\n"
	    "add $8, %%rsp\n"
	    :
			:
			:);

	/*
	 * And, jump.
	 */
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
