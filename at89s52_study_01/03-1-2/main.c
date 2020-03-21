/*
*Project name: 4_digit 7-segment timer                                                                                                                                                                                                                                                                  
*File name: main.c
*Author: Sean Kim
*Date: 03.19.20
*Edited: 03.20.20
*/

#include "main.h"
#include "at89x52.h"


bit T_int_flag_01 = 0;
bit T_int_flag_02 = 0;


unsigned char a=0, b=0, c=0, d=0;

unsigned char num[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
                          //7-segment common cathod.
                          //Use PNP TR for suppling proper amount of current.
              
unsigned char count;
unsigned char count_01=0; //This code is for displaying each digit st the same time.
	
void display()
	{
		if(count_01 == 0)
		{
		P0 = 0x0e;
		P1 = num[a];
		}
		
		else if(count_01 == 1)
		{
		P0 = 0x0d;
		P1 = num[b];
		}
		
		else if(count_01 == 2)
		{
		P0 = 0x0b;
		P1 = num[c];
		}
		
		else if(count_01 == 3)
		{
		P0 = 0x07;
		P1 = num[d];
		
		}
		
		return;
	}		
	
void main()
{
	
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1, Use timer/counter 0 & 1.
	TF0 = 0; // Timer/counter 0 interrupt flag clear

	
	TH0 = 0xec ;
	TL0 = 0x78 ; // TI0 occurs every 5 ms 
	             // 1us/MC -> (0xffff-0xec78) = 5,000
	
	IE = 0x82; // 0b1000 0010 IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
   
	IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	             // Should have to consider which register(btw IE & IP) comes first. 
	             //This code is unnecessary, since the priority of TI0 is higher than the priority of TI1(by internal polling). 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	
	count = 200; // 0.005*200 = 1sec. 

	
	while(1)
	{
		if(T_int_flag_01)
		{
			
		d++;
			
      if (d > 9) 
		  {
       d = 0;
       c++; // 0009 -> 0010, 0019 -> 0020, ...
        
				if (c > 9)
				{
         c = 0;
         b++;
					
          if (b > 9) 
					{
            b = 0;
            a++;
						
            if (a > 9) 
						{
                a = 0;
            }
          }
        }
      }
			count = 200;
		  T_int_flag_01 = 0;
		}
		
			display();
 
	}
}


void T_int_01() interrupt 1 // void [user name]() interrupt [vector num.]
{
	count--; // Since the const. count is 50, T_int_flag is set until count decreased to zero. 
	         
	if(!count) T_int_flag_01 = 1;

  count_01++;
	if(count_01>3) count_01 = 0; //count increment & count initialization have to be placed at the same place.
	
	TH0 = 0xec ;
	TL0 = 0x78 ;// Reset of these two register is necessary for pe riodic interrupt since it is mode 1.
	EA = 1; // Interrupt enables
	return;
}
