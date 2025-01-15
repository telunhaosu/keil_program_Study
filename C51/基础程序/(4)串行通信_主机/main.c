#include <reg51.h>	//单片机头文件
//宏定义
#define uint unsigned int	
#define uchar unsigned char
uchar ii;
//位声明
sbit k1=P2^0;
sbit k2=P2^1;
sbit k3=P2^2;
sbit k4=P2^3;
sbit k5=P2^4;
sbit k6=P2^5;
sbit k7=P2^6;
sbit k8=P2^7;
//灯声明
sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;
//函数声明
void Usart_Init(void);
void DelayMs(uint xms);
void Send_Data(uchar Key_val);
void Keyscan(void);

//主函数
void main()
{
	Usart_Init();
	while(1)	//循环
	{
		 Keyscan();
	}
}

//串口中断初始化
void Usart_Init(void)
{
    TMOD=0X20;//定时器1方式2
    TH1=0xF3;         //计数器初始值设置，注意波特率是4800
    TL1=0xF3;
    TR1=1;//打开定时器
		SM0=0;//设置串口工作方式
    SM1=1;
		REN = 1;
    EA=1;//打开总中断
    ES=1;//打开串口中断
}

//延时函数
void DelayMs(uint xms)
{   
	uchar i,j;                        
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

//发送数据函数
void Send_Data(uchar Key_val)
{
    SBUF=Key_val;      //将要发送的数据存入发送缓冲器中
    while(!TI);        //若发送中断标志位没有置1(正在发送数据)，就等待
    TI=0;	//若发送完成，TI自动置1，这里把它清零
}
 
//按键函数
void Keyscan(void)
{
	uchar Val;	//定义局部变量
	if(k1==0)		//如果按下k1
	{
		DelayMs(10);//消抖
		if(k1==0)	//确认按下k1
		{
					Val=0;

		}
		while(!k1){};	//等待按键释放
		Send_Data(Val);	//发送“0”
	}
	if(k2==0)		//如果按下k2
	{
		DelayMs(10);//消抖
		if(k2==0)	//确认按下k2
		{
				Val=1;
		}
		while(!k2);	//等待按键释放
		Send_Data(Val);	//发送“1”
	}
	if(k3==0)		//如果按下k3
	{
		DelayMs(10);//消抖
		if(k3==0)	//确认按下k3
		{
				Val=2;	//发送“2”
		}
		while(!k3);	//等待按键释放
		Send_Data(Val);
	}
	if(k4==0)		//如果按下k4
	{
		DelayMs(10);//消抖
		if(k4==0)	//确认按下k4
		{
				Val=3;	//发送“3”
		}
		while(!k4);	//等待按键释放
		Send_Data(Val);
	}
	if(k5==0)		//如果按下k5
	{
		DelayMs(10);//消抖
		if(k5==0)	//确认按下k5
		{
				Val=4;
		}
		while(!k5){};	//等待按键释放
		Send_Data(Val);	//发送“4”
	}
	if(k6==0)		//如果按下k6
	{
		DelayMs(10);//消抖
		if(k6==0)	//确认按下k6
		{
				Val=5;
		}
		while(!k6);	//等待按键释放
		Send_Data(Val);	//发送“6”
	}
	if(k7==0)		//如果按下k7
	{
		DelayMs(10);//消抖
		if(k7==0)	//确认按下k7
		{
				Val=6;
		}
		while(!k7);	//等待按键释放
		Send_Data(Val);	//发送“7”
	}
	if(k8==0)		//如果按下k8
	{
		DelayMs(10);//消抖
		if(k8==0)	//确认按下k8
		{
				Val=7;
		}
		while(!k8);	//等待按键释放
		Send_Data(Val);	//发送“7”
	}
}
void uart() interrupt 4
{
	if(RI)
	{
			uchar receiveData;
	ii=SBUF;                   
	 switch(ii)
	{
		case 0:	//收到“0”
			led0=~led0;
			break;
		case 1:	//收到“1”
			led1=~led1;
			break;
		case 2:	//收到“2”
			led2=~led2;
			break;
		case 3:	//收到“3”
			led3=~led3;
			break;
		case 4:	//收到“4”
			led4=~led4;
			break;
		case 5:	//收到“5”
			led5=~led5;
			break;
		case 6:	//收到“6”
			led6=~led6;
			break;
		case 7:	//收到“7”
			led7=~led7;
			break;
		default:
			break;
	}
	receiveData=SBUF;        //出去接收到的数据
	RI=0;                    //清除接收中断标志位
	}
}

