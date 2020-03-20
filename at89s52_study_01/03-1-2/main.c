/*
*Project name: 4_digit 7-segment timer (with two timer interrupts)                                                                                                                                                                                                                                                                  
*File name: main.c
*Author: Sean Kim
*Date: 03.19.20
*Edited: 
*/

#include "main.h"
#include "at89x52.h"


bit T_int_flag_01 = 0;
bit T_int_flag_02 = 0;


unsigned char a=0, b=0, c=0, d=0;
unsigned char i=0, j=0, k=0;
unsigned char num[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10}; 
                          //7-segment common cathod
              
unsigned char count;
unsigned char count_1;
	
void display()
	{
		if(count_1 == 1)
		{
		P0 = 0x0e;
		P1 = num[a];
		}
		
		if(count_1 == 2)
		{
		P0 = 0x0d;
		P1 = num[b];
		}
		
		if(count_1 == 3)
		{
		P0 = 0x0b;
		P1 = num[c];
		}
		
		if(count_1 == 4)
		{
		P0 = 0x07;
		P1 = num[d];
			
		count_1 = 0;
		}
		
		return;
	}		
	
void main()
{
	
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1, Use timer/counter 0 & 1.
	TF0 = 0; // Timer/counter 0 interrupt flag clear

	
	TL0 = 0xc3 ;
	TH0 = 0x50 ; // TI0 occurs every 0.05 sec 
	
	IE = 0x82; // 0b1000 0010 IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
   
	IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	             // Should have to consider which register(btw IE & IP) comes first. 
	             //This code is unnecessary, since the priority of TI0 is higher than the priority of TI1(by internal polling). 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	
	count = 20; // 0.05*20 = 1sec. 
	count_1 = 0;
	
	while(1)
	{
		if(T_int_flag_01)
		{
			j++;
			k++;
			
			if(i==10)
			{
				a++;
				
			if(a>9)	a=0;
					
				i=0;
			}
			
			if(j==100)
			{
				b++;
				
			if(b>9)	b=0;
			  i++;	
				j=0;
			}
			
			if(k==10)
			{
				c++;
					
			if(c>9)	c=0;
					
				k=0;
			}
			
				d++;
				
			if(d>9)	d=0;
		
			
			count = 20;
		  T_int_flag_01 = 0;
		}
		
		//else if(T_int_flag_02)
		  count_1++;
		
			display();
		
	}
}


void T_int_01() interrupt 1 // void [user name]() interrupt [vector num.]
{
	count--; // Since the const. count is 50, T_int_flag is set until count decreased to zero. 
	         
	if(!count) T_int_flag_01 = 1;
	
	TL0 = 0xc3 ;
	TH0 = 0x50 ; // Reset of these two register is necessary for periodic interrupt since it is mode 1.
	EA = 1; // Interrupt enables
	return;
}
