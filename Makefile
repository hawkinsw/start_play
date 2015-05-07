all: copy start main Makefile 
	cp main c
	# Put start in to jump to the actual start spot
	objcopy --add-section jumpstart=start.small.o --set-section-flags jumpstart=code,alloc c --change-section-address jumpstart=0x0602000
	# Put copy in as start segment.
	objcopy --add-section newstart=copy.small.o --set-section-flags newstart=code,alloc c --change-section-address newstart=0x0604000 --set-start=0x0604cfe
	$(STRATAFIER)/add_jumpstart_segment64 c c.addseg.1
	$(STRATAFIER)/add_newstart_segment64 c.addseg.1 c.addseg
	rm -f c.addseg.1
copy: copy.c Makefile
	gcc -fPIC -ffreestanding copy.c -static -o copy.o
	objcopy -O binary --only-section=".text" \
	copy.o copy.small.o
start: start.c Makefile
	gcc -c start.c
	objcopy -O binary --only-section=".text" start.o start.small.o
main: main.c Makefile
	gcc -o main main.c
clean:
	rm -f main c start.o start.small.o copy.small.o copy.o *addseg*
