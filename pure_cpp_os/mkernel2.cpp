/**
 * compiler option -w ignore all warning
 * compiler option -W visible all warning
 */

#include"printf.h"

#define MAGIC 0x1badb002
#define FLAGS (1<<0 | 1<<1)
#define CHECKSUM -(MAGIC + FLAGS)
#define asv(v) asm volatile(v)
#define seg(v) __attribute__((section(#v)))
#define packed_it __attribute__((packed))

struct multiboot_struct {
    u32 magic;
    u32 flags;
    u32 checksum;
}packed_it;

seg(.multiboot)
multiboot_struct multiboot = {
        .magic=MAGIC,
        .flags=FLAGS,
        .checksum=CHECKSUM
};


//操作系统构造函数委托方法
typedef void(*constructor)();

//全局定义构造委托
constructor start_ctors;
//全局定义析构委托
constructor end_ctors;

//轮询函数，并且执行
extern "C" void system_constructors() {
    for (constructor *i = &start_ctors; i != &end_ctors; i += 1) {
        (*i)();
    }
}

extern "C"
void kernel_main(void *multiboot_structure, unsigned int magicnumber) {

    printf("Hello world\n");
    printf("C++ Operating System\n");
    printf("End");


    //for(;;){
    //	printf("C++ Operating System");
    //}

    for (;;);// jmp here for ever

}

seg(.text) void stop() {

    for (;;) {
        asv("cli;hlt");
    }

}

extern u8 stack[2 * 1024 * 1024];

extern "C" seg(.text) void loader() {

    asv("mov %0,%%esp;"
        "call system_constructors;"
        "push %%eax;"
        "push %%ebx;"
        "call kernel_main;"
                ::"r"((u32) stack));

    stop();


}

seg(.bss) u8 space[2 * 1024 * 1024] = {0};

seg(.stack) packed_it u8 stack[2 * 1024 * 1024] = {0};



