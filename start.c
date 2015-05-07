void main() {
	asm("mov $0x400440, %rax\n"
	    "jmp *%rax");
}
