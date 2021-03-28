#include"interrupt.h"
#include"printf.h"


InterruptHandler::InterruptHandler(u8 intrruptNo,InterruptManager* interruptManager){
	this->interruptNo = intrruptNo;
	this->interruptManager = interruptManager;
	interruptManager->handlers[intrruptNo] = this;
}
InterruptHandler::~InterruptHandler(){
	if(interruptManager->handlers[interruptNo] == this){
		interruptManager->handlers[interruptNo] = NULL;
	}
}


u32 InterruptHandler::handleInterrupt(u32 esp){
	return esp;
}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

InterruptManager* InterruptManager::ActiveInterruptManager = NULL;

InterruptManager::InterruptManager(u16 hardwareInterruptOffset,GlobalDescriptorTable* gdt)
:picMasterCommand(0x20)
,picMasterData(0x21)
,picSlaveCommand(0xA0)
,picSlaveData(0xA1)

{
	
	this->hardwareInterruptOffset = hardwareInterruptOffset;

	u16 codeSegment = gdt->CodeSegmentSelector();
	
	u8 IDT_INTERRUPT_GATE = 0xe;
	
	for(u16 i=0;i<256;i++){
		this->handlers[i] = NULL;
		SetInterruptDescriptorTableEntry(i,codeSegment,&InterruptIgnore,0,IDT_INTERRUPT_GATE);
	}
	
	
	
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
	
	
	
	picMasterCommand.write(0x11);
	picSlaveCommand.write(0x11);
	
	
	picMasterData.write(hardwareInterruptOffset);
	picSlaveData.write(hardwareInterruptOffset+8);
	
	picMasterData.write(0x04);
	picSlaveData.write(0x02);
	
	picMasterData.write(0x01);
	picSlaveData.write(0x01);
	
	picMasterData.write(0x00);
	picSlaveData.write(0x00);
	
	InterruptDescriptorTablePointer idt;
	idt.size = 256*sizeof(GateDescriptor)-1;
	idt.base = (u32)interruptDescriptorTable;
	
	
	asm volatile(
		"lidt %0"
		:
		:"m"(idt)
	);
	
}


InterruptManager::~InterruptManager(){}

void InterruptManager::Activate(){
	if(ActiveInterruptManager != NULL){
		ActiveInterruptManager->DeActivate();
	}
	ActiveInterruptManager = this;
	
	asm("sti");
}

void InterruptManager::DeActivate(){
	if(ActiveInterruptManager == this){
		ActiveInterruptManager = NULL;
		asm("cli");
	}

}



u32 InterruptManager::DoHandleInterrupt(u8 interruptNo,u32 esp){
	if(handlers[interruptNo] != 0){
		esp = handlers[interruptNo]->handleInterrupt(esp);
	}
	if(interruptNo != hardwareInterruptOffset)printf("interrupt");
	if(hardwareInterruptOffset <= interruptNo && interruptNo < hardwareInterruptOffset+16){
		picMasterCommand.write(0x20);
		if(hardwareInterruptOffset+8 <= interruptNo){
			picSlaveCommand.write(0x20);
		}
	}
	
	return esp;
}

u32 InterruptManager::handleInterrupt(u8 interruptNo,u32 esp){
	if(ActiveInterruptManager != NULL){
		return ActiveInterruptManager->DoHandleInterrupt(interruptNo,esp);
	}
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


