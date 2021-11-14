#include <stm32f103x6.h>
#include <stdio.h>
#include <delay.h>
#include <lcd.h>
#include <math.h>
#include <rlc.h>

void init_RC(void);
void calculate_RC(void);
void calculateC(void);
void imprimir(uint32_t);

volatile uint16_t adcResult=0,time=0;
volatile uint32_t capacitancia;

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
   while(1){
      TIM2->CNT=0;
      TIM2->CR1=1;
      GPIOB->BSRR |= (1<<0);
      while(adcResult<2589){
         ADC1->SQR3 = 1; //choose channel 1 as input
         ADC1->CR2 = 1; //ADCON = 1 star conversion
         while((ADC1->SR&(1<<1)) == 0);
         adcResult=ADC1->DR;
      }
      time=TIM2->CNT;
      adcResult=0;
      capacitancia= time/(8);
      //imprimir(capacitancia);
      TIM2->CR1=0;
      GPIOB->BRR |= (1<<0);
      delay_us(500000);
      
      L2 = 1000000.0*RLC_measure()-100;
      
      delay_us(5000);
   }

}   
 

void init_RC(){
   TIM2->CCMR2 = 0x001;
   TIM2->CCER = (1<<8);
   //TIM2->PSC = 7200-1;
   TIM2->ARR = 50000-1;
   ADC1->CR2 = 1; //ADON = 1 (power-up)
   ADC1->SMPR2 = 1<<3; // SMP1 = 001 (7.5 ADC clock cycles)
   delay_us(10000);
}

void imprimir(uint32_t dato){
   uint32_t aux,div=0,i,div10=1;
   lcd_clr();
   lcd_gotoXY(0, 0);
   while(dato != 0){
      aux = dato;
      div=0;
      while((aux /(int) 10) != 0){
         aux = aux / (int)10;
         div++;
      }
      lcd_sendData('0'+aux);
      delay_us(50);
      if (div==0)
         div=1;
      div10=1;
      for(i=0;i<div;i++){
         div10= div10*10;
      }
      dato = dato / div10;
   }
}


