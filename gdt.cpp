#include"gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable():nullSegmentDescriptor(0,0,0),
unusedSegmentDescriptor(0,0,0),
codeSegmentDescriptor(0,64*1024*1024,0x9a),
dataSegmentDescriptor(0,64*1024*1024,0x92)
{
	u32 i[2];
	i[0] = sizeof(GlobalDescriptorTable)<<16;
	i[1] = (u32)this;
	
	asm volatile("lgdt (%0)"::"p"(((u8*)i)+2));
	
}

GlobalDescriptorTable::~GlobalDescriptorTable(){
	
}

u16 GlobalDescriptorTable::DataSegmentDescriptor(){
	return (u8*)&dataSegmentDescriptor-(u8*)this;
}

u16 GlobalDescriptorTable::CodeSegmentDescriptor(){
	return (u8*)&codeSegmentDescriptor-(u8*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(u32 base,u32 limit,u8 type){
	u8 *target = (u8*)this;
	if(limit < 1048576){
		target[6]  = 0x40;
		
	}else{
		if((limit&0xfff)!=0xfff){
			limit = (limit>>12)-1;
		}else{
			limit = limit >> 12;
		}
		target[6] = 0xc0;
	}
	
	target[0] = limit & 0xff;
	
	target[1] = (limit>>8)&0xff;
	
	target[6] = (limit>>16)&0xf;
	
	
	target[2] = base & 0xff;
	target[3] = (base>>8) &0xff;
	target[4] = (base>>16) &0xff;
	target[7] = (base>>24) &0xff;
	
	target[5] = type;
	
	
}


u32 GlobalDescriptorTable::SegmentDescriptor::base(){
	u8* target = (u8*)this;
	u32 result = target[7];
	
	result = (result<<8)+target[4];
	result = (result<<8)+target[3];
	result = (result<<8)+target[2];
	
	return result;
	
	
}



u32 GlobalDescriptorTable::SegmentDescriptor::limit(){
	u8* target = (u8*)this;
	u32 result = target[6]&0xff;
	
	result = (result<<8)+target[1];
	result = (result<<8)+target[0];
	
	if((target[6]&0xc0)!=0xc0){
		result = (result<<12)|0xfff;
	}
	
	return result;
}






























