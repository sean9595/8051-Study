/*
*Project name: WDT example 01
*File name: main.c
*Author: Sean Kim
*Date: 03.19.20
*Edited: 
*/

#include "main.h"
#include "at89x52.h"

unsigned char LED = 0xfe; //0b1111 1110
unsigned char count = 0;
bit TI_01=0, TI_02=0;


void main()
{
  TMOD = 0x11; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF0 = 0; // Timer/counter 0 interrupt flag clear
	TF1 = 0; // TI1
	TL0 = 0xc3 ;
	TH0 = 0x50 ; // Crystal oscillator = 12MHz. -> 1us/MC. 
	             // TI0 occurs every 0.05 sec
	TL1 = 0x13 ;
	TH1 = 0x88 ; // TI1(WDT reset signal) occurs every 0.005 sec.
	
	IE = 0x8a; // TI0 & TI1 enable & entire interrupt enable.
	
	P1 = LED;
	
  TR0 = 1; //TI0 starts
	TR1 = 1; //TI1 starts
  
	count = 10; // Apply this variable at TI0. 0.05 * 10 = 0.5 sec.
 	
	WDTRST = 0x1e;
	WDTRST = 0xe1; //WDT enables.
	
	while(1)
	{
		if(TI_01)
		{
		LED = (LED<<1) | 0x01; // Shift one bit to the left and fill 1 at LSB.
	  }
		
		if(TI_02)
		{
			WDTRST = 0x1e;
	    WDTRST = 0xe1; //WDT resets.
			
			
		}
	}
}

void Turn_on() interrupt 1 //TI0 ISR
{
	count --;
	
	if(!count) TI_01 = 1;
	
	TL0 = 0xc3 ;
	TH0 = 0x50 ;
	EA = 1;
}

void WDT_reset() interrupt 3 //TI1 ISR
{
	TI_02 = 1;
	
	TL1 = 0x13 ;
	TH1 = 0x88 ;
	EA = 1;
}