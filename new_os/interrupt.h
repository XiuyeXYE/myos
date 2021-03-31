#ifndef __INTERRUPT_H_
#define __INTERRUPT_H_

#include"types.h"
#include"port.h"
#include"gdt.h"
#include "util.h"

struct idt_r {
    u16 limit;
    u32 base;
} packed_it;

struct idt_desc {
    u16 offset0_15;
    u16 select;
    u16 type;
    u16 offset16_31;
} packed_it;

#define IDT_BASE    0x00000000
#define IDT_SIZE 0xFF
#define INT_GATE  0x8E00        /* utilise pour gerer les interruptions */
#define IDT_SIZE        0xFF    /* nombre max. de descripteurs dans la table */
#define TRAP_GATE 0xEF00        /* utilise pour faire des appels systemes */

void init_idt();

void init_pic();


#endif
