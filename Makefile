all: copy start main Makefile
	@echo -n
# Make c the object of our manipulations and base it
# on main.
	cp main c
# Put start in to jump to the actual start spot
	objcopy --add-section jumpstart=start.small.o --set-section-flags jumpstart=code,alloc c --change-section-address jumpstart=0x0602000
# Put copy in as start segment.
	objcopy --add-section newstart=copy.small.o --set-section-flags newstart=code,alloc c --change-section-address newstart=0x0604000 --set-start=0x0604cfe
# Even though both sections are in, we have to add them
# as segments. We use a special strata-specific tool
# for that.
	$(STRATAFIER)/add_strata_segment64 --segment_name jumpstart c c.addseg.1
	$(STRATAFIER)/add_strata_segment64 --segment_name newstart c.addseg.1 c.addseg
# take away the temporary files.
	rm -f c.addseg.1

copy: copy.c Makefile
	@echo -n
# We need the frame pointer here (rbp), so do not
# compile with -fomit-frame-pointer under any
# circumstances. See copy.c:24 for the use of rbp.
#
# We need -fPIC so that our calls to memcpy (which
# is hand-written internally) can be called
# even when the object code is moved.
	gcc -fPIC -ffreestanding copy.c -static -o copy.o
# Just get the object code for the .text section
# out of copy.o. This places some restrictions on
# what that code can do, but it's okay.
	objcopy -O binary --only-section=".text" \
	copy.o copy.small.o

start: start.c Makefile
	gcc -c start.c
	objcopy -O binary --only-section=".text" start.o start.small.o
main: main.c Makefile
	gcc -o main main.c
clean:
	rm -f main c start.o start.small.o copy.small.o copy.o *addseg*
