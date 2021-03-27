#include"interrupt.h"
#include"printf.h"

u32 InterruptManager::handleInterrupt(u8 interruptNo,u32 esp){
	printf("interrupt");
	return esp;
}

void InterruptManager::HandleInterruptRequest0x00(){
}


void InterruptManager::HandleException0x00(){
}

