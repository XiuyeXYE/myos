#ifndef __GDT_H_
#define __GDT_H_

#include"types.h"
#include "util.h"


#define GDT_BASE 0x00000800
#define GDT_SIZE 0xFF

//register
struct gdt_r {
    u16 limit;
    u32 base;
}packed_it;

//gdt entity
struct gdt_desc {
    u16 limit0_15;
    u16 base0_15;
    u8 base16_23;
    u8 access;
    u8 limit16_19: 4;
    u8 other: 4;
    u8 base24_31;
}packed_it;


struct tss {
    u16 previous_task, __previous_task_unused;
    u32 esp0;
    u16 ss0, __ss0_unused;
    u32 esp1;
    u16 ss1, __ss1_unused;
    u32 esp2;
    u16 ss2, __ss2_unused;
    u32 cr3;
    u32 eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    u16 es, __es_unused;
    u16 cs, __cs_unused;
    u16 ss, __ss_unused;
    u16 ds, __ds_unused;
    u16 fs, __fs_unused;
    u16 gs, __gs_unused;
    u16 ldt_selector, __ldt_sel_unused;
    u16 debug_flag, io_map;
} packed_it;


void init_gdt();

#endif

