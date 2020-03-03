///////////////////////////////////////////////////////////////////////
//Project name: Set P1.0~P1.3 as input and set P1.4~P1.7 as output
//Title: main.h  
//Author: Sean Kim
//Date: 02.25.20
//Edited: 
//////////////////////////////////////////////////////////////////////


#include "main.h"
#include "reg51.h"

void delay(unsigned int a);

void main() //Poll mathod? ??? ??
{
    P1 = 0x0f; // 0b00001111 This is for set P1.0 to P1.4 as inputs.
               // If user press the button, pin connects to ground and the pin register turns 1 to 0. 
    while(1)
    {
     P1 = (P1<<4) | 0x0f; //4bit ??? ?? ??? ?? input?? ????. ?? ? ?? P1 reg? ???? ???? LED? ????.
     
     //??? ???? ???? ??? ???? LED? ??????? ??.
     //P1 = ((P1<<4) | 0x0f) & P1; //??? ?? ???.
    
     delay(100); //Debouncing? ?? ?? ??
    }
}

void delay(unsigned int a)
{
  while(a--);
}