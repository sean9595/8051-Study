/*
*File name: time.c
*Author: Sean Kim
*Date: 03.25.20
*Edited: 
*/

#include <time.h>
#include <at89x52.h>

void mode0_timer00_init()
{
	TMOD = 0x00; //GATE = 0, C/T = 0, Timer/counter mode 0
	TF0 = 0; // Timer/counter 0 interrupt flag clear
}

void mode0_timer01_init()
{
	TMOD = 0x00; //GATE = 0, C/T = 0, Timer/counter mode 0
	TF1 = 0; // Timer/counter 1 interrupt flag clear
}

void mode1_timer00_init()
{
	TMOD = 0x01; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF0 = 0; // Timer/counter 0 interrupt flag clear
}

void mode1_timer01_init()
{
	TMOD = 0x10; //GATE = 0, C/T = 0, Timer/counter mode 1
	TF1 = 0; // Timer/counter 1 interrupt flag clear
}

void mode2_timer00_init()
{
	TMOD = 0x02; //GATE = 0, C/T = 0, Timer/counter mode 2
	TF0 = 0; // Timer/counter 0 interrupt flag clear
}

void mode2_timer01_init()
{
	TMOD = 0x20; //GATE = 0, C/T = 0, Timer/counter mode 2
	TF1 = 0; // Timer/counter 1 interrupt flag clear
}

void mode3_timer00_init()
{
	TMOD = 0x03; //GATE = 0, C/T = 0, Timer/counter mode 3
	TF0 = 0; // Timer/counter 0 interrupt flag clear
}

void mode3_timer01_init()
{
	TMOD = 0x30; //GATE = 0, C/T = 0, Timer/counter mode 3
	TF1 = 0; // Timer/counter 1 interrupt flag clear
}

