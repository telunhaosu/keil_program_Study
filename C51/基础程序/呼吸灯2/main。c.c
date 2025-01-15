/*-----------------------------------------------
Function: 用渐变的PWM信号实现LED呼吸灯
Description: LED由暗逐渐变亮，再由亮逐渐变暗循环
Author: Zhang Kaizhou
Date: 2019-6-11 17:47:35
-----------------------------------------------*/

#include <REGX52.H>
#include <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int
#define PERIOD 500
/*全局变量定义*/
uint low = 0;
	
/*端口定义*/
//sbit led = P2^7;

/*函数声明*/
void delay(uint xus);

/*主函数*/
void main(){
	while(1){
		P2 = 0xFF;
			delay(5000);
		for(low = 0; low < PERIOD; low++){
			P2 = 0x00;
			delay(low);
			P2 = 0xFF;
			delay(PERIOD - low);
		}
		P2 = 0x00;
			delay(5000);
		for(low = PERIOD - 1; low > 0; low--){
			P2 = 0x00;
			delay(low);
			P2 = 0xFF;
			delay(PERIOD - low);
		}
	}
}

/*延时函数*/
void delay(uint xus){ // 延时9.766us * x + 8.682us(仿真测的数据)
	while(xus--);
}



