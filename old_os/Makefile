objects = loader.o mkernel.o printf.o port.o gdt.o interrupt.o interruptstub.o

CPPPRAMS = -m32 -W -fno-common -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-pie
ASPRAMS = --32
LDPRAMS = -m elf_i386 

%.o: %.cpp
	g++ ${CPPPRAMS} -o $@ -c $<

%.o: %.s
	as ${ASPRAMS} -o $@ $<

mkernel.img: linker.ld $(objects)
	ld ${LDPRAMS} -T $< -o $@ ${objects}


mkernel.iso : mkernel.img	
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	
	cp $< iso/boot/
	#echo "kernel iso/boot/mkernel.img"
	#echo "multiboot iso/boot/mkernel.img"
	echo "set timeout=0" > iso/boot/grub/grub.cfg
	echo "set default=0" >> iso/boot/grub/grub.cfg
	echo "" >> iso/boot/grub/grub.cfg
	echo 'menuentry "my os" {'>> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mkernel.img'>> iso/boot/grub/grub.cfg
	echo '	boot'>> iso/boot/grub/grub.cfg
	echo '}'>> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso
	rm -rf iso
	
clean:
	rm -rf *.o *.iso *.img a.out iso
	
	
