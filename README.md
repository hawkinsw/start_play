Playing around with the start symbol of a binary program.

# Goal
The goal is to add code that executes before code
from the original program.


#Process
1. Write code that will execute before the original
program.
2. Add that code (as a section) to the original program.
3. Add that section as a loadable segment to the original program.
4. Set the entry point of the binary to the new code.
5. Maintain the appropriate registers and stack entries
during new code execution
6. (In the new code) jump to the entry point of the original
program.

# Notes on (5)
There are a few things that `_start` expects to see when it
executes. These are based upon the ELF format (maybe), the
ABI and calling conventions. To satisfy these requirements,
we have to satisfy the following requirements before 
invoking the original `_start`:
- maintain `rdx`: pointer to the shared library's termination
function
- maintain the stack entries: these are pointers to the
command line arguments
- maintain the stack pointer: for above, and other obvious
reasons.
- do not maintain rax: `rax` is used in `_start` but
its value does not matter.
