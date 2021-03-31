#include"gdt.h"


tss default_tss;
gdt_desc k_gdt[GDT_SIZE];
gdt_r k_gdt_r;                /* GDTR */


void init_gdt_desc(u32 base, u32 limit, u8 acces, u8 other, struct gdt_desc *desc) {
    desc->limit0_15 = (limit & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (base & 0xff0000) >> 16;
    desc->access = acces;
    desc->limit16_19 = (limit & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base24_31 = (base & 0xff000000) >> 24;
}


void init_gdt() {

    default_tss.debug_flag = 0x00;
    default_tss.io_map = 0x00;
    default_tss.esp0 = 0x1FFF0;
    default_tss.ss0 = 0x18;

    /* initialize gdt segments */
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &k_gdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &k_gdt[1]);    /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &k_gdt[2]);    /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &k_gdt[3]);        /* stack */

    init_gdt_desc(0x0, 0xFFFFF, 0xFF, 0x0D, &k_gdt[4]);    /* ucode */
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &k_gdt[5]);    /* udata */
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &k_gdt[6]);        /* ustack */

    init_gdt_desc((u32) &default_tss, 0x67, 0xE9, 0x00, &k_gdt[7]);    /* descripteur de tss */

    /* initialize the gdtr structure */
    k_gdt_r.limit = GDT_SIZE * 8;
    k_gdt_r.base = GDT_BASE;

    /* copy the gdtr to its memory area */
    memcpy((char *) k_gdt_r.base, (char *) k_gdt, k_gdt_r.limit);

    /* load the gdtr registry */
    asm("lgdtl (k_gdt_r)");

    /* initiliaz the segments */
    asm("   movw $0x10, %ax    \n \
            movw %ax, %ds    \n \
            movw %ax, %es    \n \
            movw %ax, %fs    \n \
            movw %ax, %gs    \n \
            ljmp $0x08, $next    \n \
            next:        \n");
}








