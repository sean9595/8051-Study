/*
*Project name: PWM
*File name: main.c
*Author: Sean Kim
*Date: 03.31.20
*Edited: 04.02.20
*/

#include <main.h>
#include <math.h>
#include <at89x52.h>

/*Pin definition*/
sbit PWM_out = P0^0; // 

/*Flag definition*/
bit PWM_High_flag = 0;
bit PWM_int_flag_High = 0;
bit PWM_int_flag_Low = 0;

/*typedef unsigned short = uint16_t;*/
unsigned short period = 20000; //unit: us (valid range: 0~65535)
unsigned char duty = 20; //unit: percentage
unsigned short CCR_01 = 0;
unsigned short CCR_02 = 0;

void main()
{
	
  CCR_01 = (65536 - ((65536 - period)*(duty/100)));
  //  CCR_02 = (65536 - ((65536 - period)*((100-duty)/100)));
  CCR_02 = period - CCR_01;
	
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF0 = 0; // Timer/counter 0 interrupt flag clear
	TL0 =  0;
	TH0 =  0; 
	IE = 0x82; // IE -> interrupt enable reg. Timer interrupt enables & entire interrupt enable.
	IP = 0x02; // IP -> interrupt priority. Set timer interrupt 0 as the highest priority. 
	           // Should have to consider which register(btw IE & IP) comes first. 
	
	TR0 = 1; // Timer interrupt 0 RUN.
	
	while(PWM_int_flag_High)
	{
		PWM_out = 1;
		PWM_int_flag_High = 0;
	}
	
	while(PWM_int_flag_Low)
	{
		PWM_out = 0;
		PWM_int_flag_Low = 0;
	}
}

void PWM_int() interrupt 1 // void [user name]() interrupt [vector num.]
{
	if(PWM_High_flag == 0)
	{
		PWM_int_flag_High = 1;
		PWM_High_flag = 1;
		TL0 = ((CCR_01>>8) & 0xff);
		TH0 = (CCR_01 & 0xff);
	}
	
	else
	{
		PWM_int_flag_Low = 1;
		PWM_High_flag = 0;
		TL0 = ((CCR_02>>8) & 0xff);
		TH0 = (CCR_02 & 0xff);
	}
		
	EA = 1; // Interrupt enables
	return;
}