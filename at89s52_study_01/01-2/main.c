///////////////////////////////////////////////////////////////////////
//Title: main.c  
//Author: Sean Kim
//Date: 02.24.20
//Edited: 02.25.20
//////////////////////////////////////////////////////////////////////

#include "main.h"
#include "reg51.h" 

unsigned char num[] = {0xbf, 0x86, 0xcb, 0xcf, 0xe3, 0xed, 0xfd, 0x87, 0xff, 0xef}; //? ?? 7-segment? 0~9?? ???? ?? ?.
                          //7-segment? common cathod
                          //0 = "0b10111111", 1 = "0b10000110", 2 = "0b11001011", 3 = "0b11001111", 4 = "0b11100011", 5 = "0b11101101"
                          //6 = "0b11111101", 7 = "0b10000111", 8 = "0b11111111", 9 = "0b11101111"

                          

void delay(unsigned int a);

void main() 
{
    while(1)
    {
			unsigned int i;
      for(i=0;i<=9;i++)
      {
          P1 = num[i]; 
          delay(0x59200); //5000ms
      }
    }
}

void delay(unsigned int a)
{
    while(a--);
}