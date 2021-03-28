#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_

#include"types.h"
#include"port.h"
#include"gdt.h"

class InterruptManager{


	public:
	
	InterruptManager(u16 hardwareInterruptOffset,GlobalDescriptorTable *gdt);
	~InterruptManager();
	
	protected:

		struct GateDescriptor{
			u16 handleAddressLowBits;
			u16 gdt_codeSegmentSelector;
			u8 reserved;
			u8 access;
			u16 handleAddressHighBits;
			
		}__attribute__((packed));
		
		static GateDescriptor interruptDescriptorTable[256];
		
		
		struct InterruptDescriptorTablePointer{
			u16 size;
			u32 base;
		}__attribute__((packed));
		
		
		static void SetInterruptDescriptorTableEntry(
			u8 interruptNo,
			u16 codeSegmentSelectorOffset,
			void (*handler)(),
			u8 DescriptorPrivilegelLevel,
			u8 DescriptorType
		);
		
		u16 hardwareInterruptOffset;
		
		static void InterruptIgnore();
		
		
		static u32 handleInterrupt(u8 interruptNo,u32 esp);
		
		static void HandleInterruptRequest0x00();
		static void HandleInterruptRequest0x01();
		static void HandleInterruptRequest0x02();
		static void HandleInterruptRequest0x03();
		static void HandleInterruptRequest0x04();
		static void HandleInterruptRequest0x05();
		static void HandleInterruptRequest0x06();
		static void HandleInterruptRequest0x07();
		static void HandleInterruptRequest0x08();
		static void HandleInterruptRequest0x09();
		static void HandleInterruptRequest0x0A();
		static void HandleInterruptRequest0x0B();
		static void HandleInterruptRequest0x0C();
		static void HandleInterruptRequest0x0D();
		static void HandleInterruptRequest0x0E();
		static void HandleInterruptRequest0x0F();
		
		static void HandleInterruptRequest0x31();
		
		
		static void HandleException0x00();
		static void HandleException0x01();
		static void HandleException0x02();
		static void HandleException0x03();
		static void HandleException0x04();
		static void HandleException0x05();
		static void HandleException0x06();
		static void HandleException0x07();
		static void HandleException0x08();
		static void HandleException0x09();
		static void HandleException0x0A();
		static void HandleException0x0B();
		static void HandleException0x0C();
		static void HandleException0x0D();
		static void HandleException0x0E();
		static void HandleException0x0F();
		
		static void HandleException0x31();
		
		

};

#endif
