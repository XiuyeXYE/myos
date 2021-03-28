#ifndef __GDT_H_
#define __GDT_H_
#include"types.h"

class GlobalDescriptorTable{
	
public:

	class SegmentDescriptor{
	public:
		SegmentDescriptor(u32 base,u32 limit,u8 type);
		u32 base();
		u32 limit();
	private:
		u16 limit_lo;
		u16 base_lo;
		u8 base_hi;
		u8 type;
		u8 flags_limit_hi;
		u8 base_vhi;
		
	}__attribute__((packed));
	
	SegmentDescriptor nullSegmentDescriptor;
	SegmentDescriptor unusedSegmentDescriptor;
	SegmentDescriptor codeSegmentDescriptor;
	SegmentDescriptor dataSegmentDescriptor;
public:
	GlobalDescriptorTable();
	~GlobalDescriptorTable();
	
	u16 CodeSegmentSelector();
	u16 DataSegmentSelector();

};



#endif

