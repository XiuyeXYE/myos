#include"interrupt.h"

idt_desc k_idt[IDT_SIZE];        /* IDT table */
idt_r k_idt_r;

void init_idt_desc(u16 select, u32 offset, u16 type, struct idt_desc *desc) {
    desc->offset0_15 = (offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset & 0xffff0000) >> 16;
}

extern void _asm_int_0();

extern void _asm_int_1();

extern void _asm_syscalls();

extern void _asm_exc_GP(void);

extern void _asm_exc_PF(void);

extern void _asm_schedule();

void isr_kbd_int(void) {
    u8 i;
    static int lshift_enable;
    static int rshift_enable;
    static int alt_enable;
    static int ctrl_enable;
    do {
        i = io.inb(0x64);
    } while ((i & 0x01) == 0);


    i = io.inb(0x60);
    i--;

    if (i < 0x80) {        /* touche enfoncee */
        switch (i) {
            case 0x29:
                lshift_enable = 1;
                break;
            case 0x35:
                rshift_enable = 1;
                break;
            case 0x1C:
                ctrl_enable = 1;
                break;
            case 0x37:
                alt_enable = 1;
                break;
            default:

                if (alt_enable == 1) {
                    io.putctty(kbdmap[i * 4 + 2]);
                    if (&io != io.current_io)
                        io.current_io->putctty(kbdmap[i * 4 + 2]);

                } else if (lshift_enable == 1 || rshift_enable == 1) {

                    io.putctty(kbdmap[i * 4 + 1]);
                    if (&io != io.current_io)
                        io.current_io->putctty(kbdmap[i * 4 + 1]);

                } else {
                    io.putctty(kbdmap[i * 4]);
                    if (&io != io.current_io)
                        io.current_io->putctty(kbdmap[i * 4]);

                }
                break;

                //io.print("sancode: %x \n",i * 4 + (lshift_enable || rshift_enable));
                /*io.putctty(kbdmap[i * 4 + (lshift_enable || rshift_enable)]);	//replac� depuis la 10.4.6
                if (&io != io.current_io)
                    io.current_io->putctty(kbdmap[i * 4 + (lshift_enable || rshift_enable)]);*/
                break;
        }
    } else {        /* touche relachee */
        i -= 0x80;
        switch (i) {
            case 0x29:
                lshift_enable = 0;
                break;
            case 0x35:
                rshift_enable = 0;
                break;
            case 0x1C:
                ctrl_enable = 0;
                break;
            case 0x37:
                alt_enable = 0;
                break;
        }
    }

    io.outb(0x20, 0x20);
    io.outb(0xA0, 0x20);
}


void isr_default_int(int id) {
    static int tic = 0;
    static int sec = 0;
    switch (id) {
        case 1:
            isr_kbd_int();
            break;


        default:
            return;

    }

    io.outb(0x20, 0x20);
    io.outb(0xA0, 0x20);
}


void isr_schedule_int() {
    static int tic = 0;
    static int sec = 0;
    tic++;
    if (tic % 100 == 0) {
        sec++;
        tic = 0;
    }
    schedule();
    io.outb(0x20, 0x20);
    io.outb(0xA0, 0x20);
}

void isr_GP_exc(void) {
    io.print("\n General protection fault !\n");
    if (arch.pcurrent != NULL) {
        io.print("The processus %s have to be killed !\n\n", (arch.pcurrent)->getName());
        (arch.pcurrent)->exit();
        schedule();
    } else {
        io.print("The kernel have to be killed !\n\n");
        asm("hlt");
    }
}

void isr_PF_exc(void) {
    u32 faulting_addr, code;
    u32 eip;
    struct page *pg;
    u32 stack;
    asm(" 	movl 60(%%ebp), %%eax	\n \
    		mov %%eax, %0		\n \
		mov %%cr2, %%eax	\n \
		mov %%eax, %1		\n \
 		movl 56(%%ebp), %%eax	\n \
    		mov %%eax, %2"
    : "=m"(eip), "=m"(faulting_addr), "=m"(code));
    asm("mov %%ebp, %0": "=m"(stack):);

    //io.print("#PF : %x \n",faulting_addr);

    //for (;;);
    if (arch.pcurrent == NULL)
        return;

    process_st *current = arch.pcurrent->getPInfo();

    if (faulting_addr >= USER_OFFSET && faulting_addr <= USER_STACK) {
        pg = (struct page *) kmalloc(sizeof(struct page));
        pg->p_addr = get_page_frame();
        pg->v_addr = (char *) (faulting_addr & 0xFFFFF000);
        list_add(&pg->list, &current->pglist);
        pd_add_page(pg->v_addr, pg->p_addr, PG_USER, current->pd);
    } else {
        io.print("\n");
        io.print("No autorized memory acces on : %p (eip:%p,code:%p)\n", faulting_addr, eip, code);
        io.print("heap=%x, heap_limit=%x, stack=%x\n", kern_heap, KERN_HEAP_LIM, stack);

        if (arch.pcurrent != NULL) {
            io.print("The processus %s have to be killed !\n\n", (arch.pcurrent)->getName());
            (arch.pcurrent)->exit();
            schedule();
        } else {
            io.print("The kernel have to be killed !\n\n");
            asm("hlt");
        }
    }

}


void init_idt() {
    /* Init irq */
    int i;
    for (i = 0; i < IDT_SIZE; i++)
        init_idt_desc(0x08, (u32) _asm_schedule, INT_GATE, &k_idt[i]); //

    /* Vectors  0 -> 31 are for exceptions */
    init_idt_desc(0x08, (u32) _asm_exc_GP, INT_GATE, &k_idt[13]);        /* #GP */
    init_idt_desc(0x08, (u32) _asm_exc_PF, INT_GATE, &k_idt[14]);     /* #PF */

    init_idt_desc(0x08, (u32) _asm_schedule, INT_GATE, &k_idt[32]);
    init_idt_desc(0x08, (u32) _asm_int_1, INT_GATE, &k_idt[33]);

    init_idt_desc(0x08, (u32) _asm_syscalls, TRAP_GATE, &k_idt[48]);
    init_idt_desc(0x08, (u32) _asm_syscalls, TRAP_GATE, &k_idt[128]); //48

    k_idt_r.limit = IDT_SIZE * 8;
    k_idt_r.base = IDT_BASE;


    /* Copy the IDT to the memory */
    memcpy((char *) k_idt_r.base, (char *) k_idt, k_idt_r.limit);

    /* Load the IDTR registry */
    asm("lidtl (k_idt_r)");
}
