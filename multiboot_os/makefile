objects = boot.o kernel.o printf.o

CPPPRAMS = -m32 -W -fno-common -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-pie
ASPRAMS = --32
LDPRAMS = -m elf_i386

%.o: %.cpp
	g++ ${CPPPRAMS} -o $@ -c $<

%.o: %.s
	as ${ASPRAMS} -o $@ $<

kernel.img: linker.ld $(objects)
	ld ${LDPRAMS} -T $< -o $@ ${objects}

kernel.iso : kernel.img	
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	
	cp $< iso/boot/
	#echo "kernel iso/boot/kernel.img"
	#echo "multiboot iso/boot/kernel.img"
	echo "set timeout=0" > iso/boot/grub/grub.cfg
	echo "set default=0" >> iso/boot/grub/grub.cfg
	echo "" >> iso/boot/grub/grub.cfg
	echo 'menuentry "my os" {'>> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.img'>> iso/boot/grub/grub.cfg
	echo '	boot'>> iso/boot/grub/grub.cfg
	echo '}'>> iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ iso
	rm -rf iso
	
clean:
	rm -rf *.o *.iso *.img a.out iso
	