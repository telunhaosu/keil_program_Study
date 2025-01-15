#include <REGX51.H>
typedef unsigned int uint;
typedef unsigned char uchar;

void DelayMs(unit Xms);

void main()
{
	
}

void DelayMs(uint Xms)
{
	uchar i;
	while(Xms--)
	{
		for(i = 0; i < 123; i++);
	}
}