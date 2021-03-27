
#include"printf.h"

//screen only here size
#define screen_width 80
#define screen_height 25



extern "C" void print_char(u8 x,u8 y,char c){
	
	//wait x,y outcome ,then output str[i] !!!
	//very important algorithm processs!!!
	//0xb8000内存地址是显示器地址，往这里写数据就直接能够输出到屏幕上
	static u16 *monitor_io_memory=(u16 *)0xb8000;
	u32 idx = y*screen_width+x;
	//using '&' not '|' ,otherwise blink letters!!!
	monitor_io_memory[idx] = (monitor_io_memory[idx]&0xFF00)|c;
}

extern "C" void clear_screen(){
	//rows
	for(u8 y=0;y<screen_height;y++){
		//cols
		for(u8 x=0;x<screen_width;x++){
			print_char(x,y,'\0');
		}
	}
}

extern "C"
void printf(char *str){


	
	
	//y-->rows,x-->cols
	static u8 x=0,y=0;
	
	//写入字符串，取或0xff00的意思是我们需要把屏幕高四位拉低，
	//否则就是黑色的字体，黑色的字体黑色的屏幕是啥也看不到的
	for(int i=0;str[i]!='\0';++i){
		//fistly check letter
		switch(str[i]){
			case '\n':
				y++;//checkout rows not output!!!
				x=0;
				break;
			default:
				//firstly,check pos
				if(x>=screen_width){
					y++;
					x=0;			
				}
				if(y>=screen_height){
					clear_screen();	
					x=0;
					y=0;
				}
				//wait x,y outcome ,then output str[i] !!!
				//very important algorithm processs!!!	
				print_char(x,y,str[i]);
				x++;
				
		}
		
			
		
		
	}
}

