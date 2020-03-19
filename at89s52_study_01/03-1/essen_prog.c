/*
*File name: essen_prog.c
*Author: Sean Kim
*Date: 03.01.20
*Edited: 
*/

#include "essen_prog.h"


void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i=1;i<=ms;i++)
    {
        for(j=1;j<=125;j++); //1ms
    }
}