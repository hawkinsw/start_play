void main() {
	asm("mov %%rbp, %%rsp\n"
	    "add $8, %%rsp\n"
	    "mov $0x400490, %%rax\n"
	    "jmp *%%rax\n"
	    :
	    :
	    :);
}
