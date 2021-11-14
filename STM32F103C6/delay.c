

#include "delay.h"
void delay_us (uint32_t t)
{
   volatile unsigned long l = 0;
   uint32_t i;
   for( i= 0; i < t; i++)
   for(l = 0; l < 6; l++)
   { }
}

