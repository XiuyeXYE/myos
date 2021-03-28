#include"port.h"


Port::Port(u16 portNo):portNo(portNo){
}
Port::~Port(){}


Port8Bit::Port8Bit(u16 portNo):Port(portNo){}

Port8Bit::~Port8Bit(){}

void Port8Bit::write(u8 data){

	asm volatile("outb %1,%0"::"Nd"(portNo),"a"(data):);
}

u8 Port8Bit::read(){
	u8 result;

	asm volatile("inb %1,%0":"=a"(result):"Nd"(portNo));
	
	return result;
}




Port16Bit::Port16Bit(u16 portNo):Port(portNo){}

Port16Bit::~Port16Bit(){}

void Port16Bit::write(u16 data){

	asm volatile("outw %1,%0"::"Nd"(portNo),"a"(data));
}

u16 Port16Bit::read(){
	u16 result;

	asm volatile("inw %1,%0":"=a"(result):"Nd"(portNo));
	
	return result;
}






Port32Bit::Port32Bit(u16 portNo):Port(portNo){}

Port32Bit::~Port32Bit(){}

void Port32Bit::write(u32 data){

	asm volatile("outl %1,%0"::"Nd"(portNo),"a"(data));
}

u32 Port32Bit::read(){
	u32 result;

	asm volatile("inl %1,%0":"=a"(result):"Nd"(portNo));
	
	return result;
}





Port8BitSlow::Port8BitSlow(u16 portNo):Port8Bit(portNo){}

Port8BitSlow::~Port8BitSlow(){}

void Port8BitSlow::write(u8 data){

	asm volatile("outb %1,%0 \n "
			"jmp 1f\n"
			"1:jmp 1f\n"
			"1:\n"
			::"Nd"(portNo),"a"(data)
			
			);
}

u8 Port8BitSlow::read(){
	u8 result;

	asm volatile("inb %1,%0\n"
		"jmp 1f\n"
		"1:jmp 1f\n"
		"1:\n"
		:"=a"(result):"Nd"(portNo));
	
	return result;
}


















