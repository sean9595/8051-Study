/*
*Project name: Use timer interrupt to control LEDs.
*File name: main.c
*Author: Sean Kim
*Date: 03.08.20
*Edited: 
*/

#include "main.h"
#include "at89x52.h"


unsigned char LED, count;
bit T_int_flag = 0;

void main()
{
	/*Basic setting for timer interrupt*/
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF0 = 0; // Timer/counter 0 interrupt flag clear
	TL0 = 0x82 ;
	TH0 = 0x35 ; //Time const. for 0.02s. // 0x8235*0.6us is approximately equal to 0.02s.
	IE = 0x82; // IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
	IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	           // Should have to consider which register(btw IE & IP) comes first. 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	
	/*Code for set led*/
	LED = 0xfe; // 0b11111110
	P1 = LED;
	
	count = 50; // 0.02*50 = 1sec.
	
	/*Infinite loop*/
	while(1) // Stay for interrupt
	{
		if(T_int_flag)
		{
			LED = (LED<<1) | 0x01; // 1 bit shifting
			
			if (LED == 0xff) LED = 0xfe;
			P1 = LED;
			
			count = 50; // Counter reset.
			T_int_flag = 0; // Flag reset.
		}
	}

}

void T_int() interrupt 1 // void [user name]() interrupt [vector num.]
{
	count--; // Since the const. count is 50, T_int_flag is set until count decreased to zero. 
	         // This operation delays LED shifting 1sec.
	if(!count) T_int_flag = 1;
	
	TL0 = 0x82 ;
	TH0 = 0x35 ; // Reset of these two register is necessary for periodic interrupt since it is mode 1.
	EA = 1; // Interrupt enables
	return;
}
