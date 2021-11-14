
void imprimir(uint32_t);
void init_RC(void);
void calculate_RC(void);
void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendInt(unsigned int i);
void usart1_sendStr(char *str);

volatile uint32_t adcResult=0,cont=0;
volatile float capacitancia= 0;

int main (void)
{
   init_RC();
   while(1){
      calculate_RC();
      imprimir(capacitancia);
      delay_us(10000);
   }
}   



void init_RC(){
   RCC->APB2ENR |= 0xFC | (1<<9); // enable clocks for GPIO and ADC1
   RCC->APB1ENR |= (1<<0); /* enable TIM2 clock */
   GPIOA->CRL &= 0xFFFFFF0F; //PA1 as analog input 
   ADC1->CR2 = 1; //ADON = 1 (power-up)
   ADC1->SMPR2 = 5<<3; // SMP1 = 101 (55.5 ADC clock cycles)
   delay_us(1);   //necesario en este punto
   TIM2->ARR = 50000;
}

void calculate_RC(){
   adcResult=0;
   cont=0;
   TIM2->CNT=0; //Reset count
   GPIOB->ODR=(1<<0);       //active PB0
   TIM2->CR1 = 1;    //Start count
   while(adcResult < 2607){
      ADC1->SQR3 = 1; //choose channel 1 as input
      ADC1->CR2 |= 1; //ADCON = 1 star conversion
      while((ADC1->SR) & (1<<1) == 0);
      adcResult= ADC1->SR;
   }
   cont= TIM2->CNT;
   TIM2->CR1 = 0; //stop count
   capacitancia = cont / 72000000.0;
   capacitancia = capacitancia / 1000;
   GPIOB->BRR=(1<<0);       //active PB0
}

void usart1_init( ) {
	GPIOA->ODR |= (1<<10); //pull-up PA10
	GPIOA->CRH = 0x444448B4; // RX1=input with pull-up, TX1=alt. func output
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500; // 72MHz/9600bps = 7500
}
void usart1_sendByte(unsigned char c) {
	while((USART1->SR&(1<<6)) == 0); //wait until the TC flag is set
	USART1->DR = c;
}

void usart1_sendStr(char *str) {
	while(*str != 0) {
	usart1_sendByte(*str);
	str++;
	}
}
/* The function sends a number through USART1 */
void usart1_sendInt(unsigned int i) {
	char str[10];
	sprintf(str,"%d",i);
	usart1_sendStr(str);
}