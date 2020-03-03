/*
*Project name: External interrupt
*File name: main.c
*Author: Sean Kim
*Date: 02.28.20
*Edited:
*/

#include "reg51.h"
#include "main.h"
unsigned char led;

void delay(unsigned int ms);
void interrupt_init();

void main()
{
    // interrupt_init();
    TCON =0x01;
	  delay(1000)
    EX0 = 1; //External interrupt '0' enable.
    EA= 1; //This bit is for athorizing interrupt. ?? ???? ????.
    PX0 =1;
	  led=0xfe;
	  P1=led;
    while(1)
    {
    }
}

/*void interrupt_init()
{
    IE = 0x0;
}*/ //useless

void delay(unsigned int ms)
{
	unsigned int i, j;
    for
}

void EXT0_int() interrupt 0
{
	EA = 0;
	led=(led<<1)|0x01;
	if(led==0xff) led=0xfe;
	P1=led;
	delay(200);
	EA=1;
	return;
}