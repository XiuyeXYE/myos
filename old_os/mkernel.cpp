#include"printf.h"
#include"gdt.h"
#include"interrupt.h"


//操作系统构造函数委托方法
typedef void(*constructor)();
//全局定义构造委托
constructor start_ctors;
//全局定义析构委托
constructor end_ctors;
 
//轮询函数，并且执行
extern "C" void system_constructors(){
	for(constructor* i=&start_ctors;i!=&end_ctors;i+=1){
		(*i)();
	}
}

extern "C"
void kernel_main(void *multiboot_structure,unsigned int magicnumber){

    printf("Hello world\n");
    printf("C++ Operating System\n");
    printf("End");

    GlobalDescriptorTable gdt;

    InterruptManager interrupt(0x20, &gdt);

    //interrupt.Activate();

    //for(;;){
    //	printf("C++ Operating System");
    //}

    for (;;);// jmp here for ever

}



