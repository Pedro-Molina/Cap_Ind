

#include "delay.h"



void delay_us (uint32_t t)
{
   volatile unsigned long l = 0;
   uint32_t i;
   for( i= 0; i < t; i++)
   for(l = 0; l < 6; l++)
   { }
}

void delay()
{
   TIM2->ARR = 64515;
   TIM2->SR = 0; /* clear the UIF flag */
   TIM2->CR1 = 1; /* up counting */
   while((TIM2->SR & (1<<0)) == 0); /* wait until the UIF flag is set */
   TIM2->CR1 = 0; /*stop counting */
}


void delayTimer(){
      uint32_t i;
      for(i=0;i<31;i++){
	    delay();
      }
}

