/*
*Project name: 7-segment 4-digit
*File name: main.c
*Author: Sean Kim
*Date: 03.18.20
*Edited: 
*/

#include "at89x52.h"
#include "essen_prog.h"

unsigned char thsnd = 0, hndrd = 0, ten = 0, one = 0;
unsigned char count;
bit T_int_flag = 0;
unsigned char i=0, j=0, k=0, l=0;

void display()
{
	P0 = (thsnd) | 0x80;
	delay(1);
	P0 = (hndrd) | 0x40;
	delay(1);
	P0 = (ten) | 0x20;
	delay(1);
	P0 = (one) | 0x10;
	delay(1);
	return;
}

void main()
{
	/*Basic setting for timer interrupt*/
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF0 = 0; // Timer/counter 0 interrupt flag clear
	TL0 = 0xc3 ;
	TH0 = 0x50 ; // Crystal oscillator = 12MHz. -> 1us/MC. 
	             // TI occurs every 0.05 sec 
	IE = 0x82; // IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
	IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	           // Should have to consider which register(btw IE & IP) comes first. 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	
	
	count = 20; // 0.05*20 = 1sec.
	
	
	/*Infinite loop*/
	while(1) // Stay for interrupt
	{
		if(T_int_flag)
		{
				i++;
      	j++;
	      k++;
	      l++;
      if(i==1)
			{
				one++;
				i=0;
			}
			
			if(j==10)
			{
				ten++;
				j=0;
			}
			if(k==100)
			{
				hndrd++;
				k=0;
			}
			if(l==1000)
			{
				thsnd++;
				l=0;
			}
			if((thsnd>9)&&(hndrd>9)&&(ten>9)&&(one>9))
			{
				thsnd = 0;
				hndrd = 0;
				ten = 0;
				one = 0;
			}
			
			display();
			
			count = 50; // Counter reset.
			T_int_flag = 0; // Flag reset.
		}
	}

}

void T_int() interrupt 1 // void [user name]() interrupt [vector num.]
{
	count--; // Since the const. count is 50, T_int_flag is set until count decreased to zero. 
	         
	if(!count) T_int_flag = 1;
	
	TL0 = 0xc3 ;
	TH0 = 0x50 ; // Reset of these two register is necessary for periodic interrupt since it is mode 1.
	EA = 1; // Interrupt enables
	return;
}

