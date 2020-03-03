/*
*Project name: External interrupt
*File name: main.c
*Author: Sean Kim
*Date: 02.28.20
*Edited:
*/
#include "main.h"
#include "reg51.h"
#include "essen_prog.h"

sbit flag_interrupt_01 = 0;



void main()
{
    TCON = 0x01; //Timer control register. 
	               //0x00000000 => reset value
	               //IT0 reg. = 1 -> Set external interrupt 0. 
	               //IE0 reg. -> When external interrupt occurs, this flag sets as 1. This makes the system jumps to the ISR.

    delay(1000); 
    
    EX0 = 1; //External interrupt '0' enable.
    EA= 1; //This bit is for athorizing interrupt. Has to put this code back. 
    PX0 = 1; //
    led = 0xfe;
    P1 = led;

    while(1)
    {
        if(flag_interrupt_01)
        {
        EA = 0;
        led = (led<<1) | 0x01;

        if(led == 0xff) led = 0xfe;

        P1 = led;
        delay(20); //Delay for 20ms. This is for debouncing.
        EA = 1;
        flag_interrupt_01 = 0;
        }
    }
}

void EXT0_int() interrupt 0
{
    flag_interrupt_01 = 1; //Don't let the ISR code unnecessarily long. 
}