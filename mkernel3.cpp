

extern "C"
void printf(char *str){
	//0xb8000内存地址是显示器地址，往这里写数据就直接能够输出到屏幕上
	unsigned short *monitor_io_memory=(unsigned short *)0xb8000;
	//写入字符串，取或0xff00的意思是我们需要把屏幕高四位拉低，
	//否则就是黑色的字体，黑色的字体黑色的屏幕是啥也看不到的
	for(int i=0;str[i]!='\0';++i){
		monitor_io_memory[i]=(monitor_io_memory[i] & 0xff00) | str[i];
	}
}

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

	printf("Hello world");
	
	for(;;);// jmp here for ever	

}
