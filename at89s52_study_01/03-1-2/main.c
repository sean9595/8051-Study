/*
*Project name: 4_digit 7-segment timer (with two timer interrupts)                                                                                                                                                                                                                                                                  
*File name: main.c
*Author: Sean Kim
*Date: 03.19.20
*Edited: 
*/

#include "main.h"
#include "at89x52.h"
#include "essen_prog.h"

bit T_int_flag_01 = 0;
bit T_int_flag_02 = 0;

//unsigned char 4_dig=0, 3_dig=0, 2_dig=0, 1_dig=0;
unsigned char a=0, b=0, c=0, d=0;
unsigned char i=0, j=0, k=0, l=0;
unsigned char num[] = {0x40, 0x79, 0x34, 0x30, 0x1c, 0x12, 0x02, 0x78, 0x00, 0x10}; 
                          //7-segment? common cathod
                          //0 = "0b01000000", 1 = "0b10000110", 2 = "0b11001011", 3 = "0b11001111", 4 = "0b11100011", 5 = "0b11101101"
                          //6 = "0b11111101", 7 = "0b10000111", 8 = "0b11111111", 9 = "0b11101111"
unsigned char count;
	
void display()
	{
		P0 = 0x0e;
		P1 = num[a];
    delay(1);
		
		P0 = 0x0d;
		P1 = num[b];
		delay(1);
		
		P0 = 0x0b;
		P1 = num[c];
		delay(1);
		
		P0 = 0x07;
		P1 = num[d];
    delay(1);
		
		return;
	}		
	
void main()
{
	
	TMOD = 0x11; //GATE = 0, C/T = 0, Timer/counter mode 1, Use timer/counter 0 & 1.
	TF0 = 0; // Timer/counter 0 interrupt flag clear
	TF1 = 0; // Timer/counter 1 interrupt flag clear
	
	TL0 = 0xc3 ;
	TH0 = 0x50 ; 
	TL1 = 0xc3 ;
	TH1 = 0x50 ; // Crystal oscillator = 12MHz. -> 1us/MC. 
	             // TI occurs every 0.05 sec 
	IE = 0x8a; // 0b1000 1010 IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
   
	//IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	             // Should have to consider which register(btw IE & IP) comes first. 
	             //This code is unnecessary, since the priority of TI0 is higher than the priority of TI1(by internal polling). 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	TR1 = 1; // Timer interrupt 1 RUN.
	
	count = 20; // 0.05*20 = 1sec. 
	
	while(1)
	{
		if(T_int_flag_01)
		{
			i++;
			j++;
			k++;
			l++;
			
			if(i==1000)
			{
				a++;
				i=0;
			}
			
			if(j==100)
			{
				b++;
				j=0;
			}
			
			if(k==10)
			{
				c++;
				k=0;
			}
			
			if(l==1)
			{
				d++;
				l=0;
			}
			
			if((a>9) && (b>9) && (c>9) && (d>9))
			{
				a=0;
				b=0;
				c=0; 
				d=0;
			}
		
			
			count = 20;
		  T_int_flag_01 = 0;
		}
		
		else if(T_int_flag_02)
		{
			display();
		
		T_int_flag_02 = 0;
		}
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

void T_int_02() interrupt 3 // void [user name]() interrupt [vector num.]
{
	T_int_flag_02 = 1;
	
	TL1 = 0xc3 ;
	TH1 = 0x50 ; // Reset of these two register is necessary for periodic interrupt since it is mode 1.
	EA = 1; // Interrupt enables
	return;
}


