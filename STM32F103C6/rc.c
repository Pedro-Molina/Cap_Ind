   #include "rc.h"

   volatile uint16_t adcResult=0,time=0;
   volatile uint32_t capacitancia;

   void medirRC(){
      TIM2->CNT=0;
      TIM2->CR1=1;
      GPIOB->BSRR |= (1<<0);
      while(adcResult<2580){
	 ADC1->SQR3 = 1; //choose channel 1 as input
	 ADC1->CR2 = 1; //ADCON = 1 star conversion
	 while((ADC1->SR&(1<<1)) == 0);
	 adcResult=ADC1->DR;
      }
      time=TIM2->CNT;
      adcResult=0;
      capacitancia= time/(8);	//divido 8 porque el micro esta en 8MHz por problemas de simulacion
      imprimir(capacitancia,4,0,"nF");
      TIM2->CR1=0;
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