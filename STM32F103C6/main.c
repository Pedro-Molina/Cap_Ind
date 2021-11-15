#include <stm32f103x6.h>
#include <stdio.h>
#include <delay.h>
#include <lcd.h>
#include <math.h>
#include <rlc.h>
#include <rc.h>





volatile 	uint32_t L2=0,aux,j;
int main (void)
{
   
   RCC->APB2ENR |= 0xFC | (1<<9) | (1<<14);
   RCC->APB1ENR |= (1<<0);
   
   RLC_init();
   
   GPIOA->CRL = 0x44444804; //PA1 as analog input
   GPIOB->CRL = 0x44444443; //PB0 as output
   GPIOB->BRR = (1<<0);
   init_RC();
   lcd_init();
   clearLCD();
   while(1){
      medirRC();
      GPIOB->BRR |= (1<<0);
      delay_us(250000);
      
      L2 = 1000000.0*RLC_measure()-100;
      imprimir(L2,4,1,"uH");
      delay_us(250000);
   }

}   
 
 












