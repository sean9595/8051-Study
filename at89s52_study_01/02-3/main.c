/*
*Project name: Serial communication 01 (without interrupt)
*File name: main.h
*Author: Sean Kim
*Date: 03.11.20
*Edited: 03.15.20
*/

#include "main.h"
#include "at89x52.h"
#include "essen_prog.h" 

#define LF 0x0a; // ASCII CODE LF 
#define CR 0x0d; // ASCII CODE CR

void main()
{
	unsigned int i;
	
	/*Baudrate generation*/
	TMOD = 0x20;//T/C mode 2, timer 1
	TH1 = 0xfa;  // (256-TH1)={(osc*10^6)*(2^SMOD value)}/(32*12*9600) for baudrate 9600bps
               //11.0592MHz	
	
	/*Serial communication setting*/
	PCON = 0x80; //SMOD=0
	TR1 = 1; //Timer 1 running.
	SCON = 0x40; // 0b0100\0000 -> Serial mode 1, SM2=0, REN=0(only transmitting)

	/*Infinite loop*/
	while(1)
	{
		for(i=0;i<=25;i++) // a~z
		{
			SBUF = 'a' + i;
			delay(50); //Delay for 0.05s
		}
		
		SBUF = LF; 
		delay(50);
		
		SBUF = CR;
		delay(50);
		
		for(i=0;i<=25;i++) // A~     Z
    {
			SBUF = 'A' + i;
			delay(50);
		}
	  SBUF = LF;
		delay(50);
		
		SBUF = CR;
		delay(50);
		
		delay(500);
	}
}
