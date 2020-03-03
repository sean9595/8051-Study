/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Title: Project01-1 LED indicating sys
//Author: Sean Kim
//Date: 2.21.2020
//Edited: 2.24.2020 (managed for 20MHz clock source)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<reg51.h>

void delay(unsigned int i);

void main()
{
	unsigned char led = 0xfe; //111111110(2)
	
	while(1)
	{
	 P1 = led; //Set initial dat. '11111110' on 8bit P1 reg.special function reg.
   led = (led<<1) | 0x01; //1bit left shifting & set LSB 1. 
		                      //11111110 -> 11111101 -> 11111011 -> 11110111 -> 11101111 -> 11011111 -> 10111111 -> 01111111
   if(led == 0xff) //led == 11111111
	 {
		 led = 0xfe;
	 }
	  delay(0x12800); //R6 is equal to aprox. 296.
	}
}

void delay(unsigned int i) //Delay func.
{
	while(i--);
}
//DON'T WRITE STATEMENT FOR CALCULATE TIME TO HEX.
//12MHz oscillator, '1 machine cycle = 1us' 
//20MHz oscillator, '1 machime cycle = 0.6us'
	