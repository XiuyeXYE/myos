#include"interrupt.h"
#include"printf.h"


InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

InterruptManager::InterruptManager(u16 hardwareInterruptOffset,GlobalDescriptorTable* gdt){
	
	this->hardwareInterruptOffset = hardwareInterruptOffset;

	u16 codeSegment = gdt->CodeSegmentSelector();
	
	u8 IDT_INTERRUPT_GATE = 0xe;
	
	for(u16 i=0;i<256;i++){
		SetInterruptDescriptorTableEntry(i,codeSegment,&InterruptIgnore,0,IDT_INTERRUPT_GATE);
	}
	InterruptDescriptorTablePointer idt;
	idt.size = 256*sizeof(GateDescriptor)-1;
	idt.base = (u32)in
	
	SetInterruptDescriptorTableEntry(0x00,codeSegment,&HandleException0x00,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x01,codeSegment,&HandleException0x01,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x02,codeSegment,&HandleException0x02,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x03,codeSegment,&HandleException0x03,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x04,codeSegment,&HandleException0x04,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x05,codeSegment,&HandleException0x05,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x06,codeSegment,&HandleException0x06,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x07,codeSegment,&HandleException0x07,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x08,codeSegment,&HandleException0x08,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x09,codeSegment,&HandleException0x09,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0A,codeSegment,&HandleException0x0A,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0B,codeSegment,&HandleException0x0B,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0C,codeSegment,&HandleException0x0C,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0D,codeSegment,&HandleException0x0D,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0E,codeSegment,&HandleException0x0E,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0F,codeSegment,&HandleException0x0F,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x31,codeSegment,&HandleException0x31,0,IDT_INTERRUPT_GATE);
	
	
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x00,codeSegment,&HandleInterruptRequest0x00,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x01,codeSegment,&HandleInterruptRequest0x01,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x02,codeSegment,&HandleInterruptRequest0x02,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x03,codeSegment,&HandleInterruptRequest0x03,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x04,codeSegment,&HandleInterruptRequest0x04,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x05,codeSegment,&HandleInterruptRequest0x05,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x06,codeSegment,&HandleInterruptRequest0x06,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x07,codeSegment,&HandleInterruptRequest0x07,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x08,codeSegment,&HandleInterruptRequest0x08,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x09,codeSegment,&HandleInterruptRequest0x09,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0A,codeSegment,&HandleInterruptRequest0x0A,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0B,codeSegment,&HandleInterruptRequest0x0B,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0C,codeSegment,&HandleInterruptRequest0x0C,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0D,codeSegment,&HandleInterruptRequest0x0D,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0E,codeSegment,&HandleInterruptRequest0x0E,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x0F,codeSegment,&HandleInterruptRequest0x0F,0,IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset+0x31,codeSegment,&HandleInterruptRequest0x31,0,IDT_INTERRUPT_GATE);
	
	
	
}




u32 InterruptManager::handleInterrupt(u8 interruptNo,u32 esp){
	printf("interrupt");
	return esp;
}


void InterruptManager::SetInterruptDescriptorTableEntry(
		u8 interruptNo,
		u16 codeSegmentSelectorOffset,
		void (*handler)(),
		u8 DescriptorPrivilegelLevel,
		u8 DescriptorType
		
	
	){
	u8 IDT_DESC_PRESENT = 0X80;
	interruptDescriptorTable[interruptNo].handleAddressLowBits = ((u32)handler)&0xffff;	
	interruptDescriptorTable[interruptNo].handleAddressHighBits = ((u32)handler>>16)&0xffff;
	interruptDescriptorTable[interruptNo].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	interruptDescriptorTable[interruptNo].access = IDT_DESC_PRESENT | (DescriptorPrivilegelLevel<<5) | DescriptorType;
	interruptDescriptorTable[interruptNo].reserved = 0;
	
	
	
}


