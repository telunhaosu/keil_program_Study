#include <REGX51.H>
#include <intrins.h>
sbit p30 = P3^0;
sbit p31 = P3^1;
typedef unsigned char u8;
typedef unsigned int u16;    //typedef定义数据类型
typedef unsigned long u32;    //typedef定义数据类型
u32 blink[]={0x00000001,0x00080002,0x00040004,0x00020008,0x00010010,
						 0x00008020,0x00004040,0x00002080,0x00001100,0x00000a00,0x00000400};  
 void delay(u16 x)
 {
	 u16 i;
	 while(x--)
		 for(i = 0; i < 123; i++);
 }
 void set_led_20(u32 res)//仅低20位有效
 {
	 res &= 0x000fffff;
	 P0 = (res &  0x000000ff) >> (0*8);
	 P1 = (res &  0x0000ff00) >> (1*8);
	 P2 = (res &  0x000f0000) >> (2*8) ; //与或保证P2高4位不受影响
 }
void main()                //主函数
{
	unsigned char flow1[4] = {0xe7, 0xdb, 0xbd, 0x7e};	//中->边
	unsigned char flow2[4] = {0xdb, 0xe7, 0x7e, 0xbd };	//边->中
	u32 res1 =  0x00000000;
	u32 res2 = ~0x00000001;
	u32 res3 = ~0x00000001;
	u32 res4 = 0;
	while(1)
	{
		if (p30 == 1 & p31 == 1)
		{
			res1 =  0x00000000;
			while(p30 == 1 & p31 == 1)
			{
			set_led_20(res1);
			res1 = ~res1;
			delay(300);
			}
		}
		else if(p30 == 0 & p31 == 1)
		{
			res2 = ~0x00000001;
			while(p30 == 0 & p31 == 1)
			{
			set_led_20(res2);
			delay(300);
			res2 = _lrol_(res2, 1);
			if (res2 == ~0x00100000)
			{
				res2 = ~0x00000001;
			}
			}

		}
		else if(p30 == 1 & p31 == 0)
		{
			res3 = ~0x00000001;
			while(p30 == 1 & p31 == 0)
			{
			set_led_20(res3);
			delay(300);
			res3 = _lror_(res3, 1);
			if (res3 == ~0x80000000)
			{
				res3 = ~0x00080000;
			}
			}

		}
		else if(p30 == 0 & p31 == 0)
		{
			res4 = 0;
			while (p30 == 0 & p31 == 0)
			{
				set_led_20(~blink[res4]);
				delay(300);
				res4 = (res4+1) % 11;
			}
		}
	}
}

