/*
*Project name: Louiseclock
*File name: main.c
*Author: Sean Kim
*Date: 03.25.20
*Edited: 
*/

#include "main.h"
#include "at89x52.h"
//#include "essen_prog.h" 
#include "time.h"

void main()
{
  void mode1_timer00_init();
	
	
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