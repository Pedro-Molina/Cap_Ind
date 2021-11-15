

#include "lcd.h"
void lcd_init()
{
   GPIOB->CRL = 0x33333333;
   GPIOB->CRH = 0x33333333;
   GPIOB->BRR = (1<<LCD_EN); //same as GPIOB>ODR &= ~(1<<LCD_EN); /* LCD_EN = 0 */
   GPIOB->BRR = (1<<LCD_RW); //same as GPIOB>ODR &= ~(1<<LCD_RW); /* LCD_RW = 0 */
   delay_us(3000); /* wait 3ms */
   lcd_sendCommand(0x38); /* init. LCD 2 line,5´7 matrix */
   lcd_sendCommand(0x0C); /* display on, cursor on */
   lcd_sendCommand(0x01); /* clear LCD */
   delay_us(2000); /* wait 2ms */
   lcd_sendCommand(0x06); /* shift cursor right */
}

void lcd_sendCommand (uint8_t cmd)
{
   GPIOB->BRR = (1<<LCD_RS); /* RS = 0 for command */
   lcd_putValue(cmd);
}
/**************************
Prints in LCD display
***************************/
void lcd_sendData (uint8_t data)
{
   GPIOB->BSRR = (1<<LCD_RS); /* RS = 1 for data */
   lcd_putValue(data);
}

void lcd_putValue (uint8_t value)// 8-bit
{
   GPIOB->BRR = 0x1FE0; /* clear PB4-PB12 */
   GPIOB->BSRR = (value<<5)&0x1FE0; /* put value on PB4-PB12 , shidteo 5 para poder enmascarar correctamente el valor*/ 
   GPIOB->BSRR = (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
   delay_us(2); /* make EN pulse wider */
   GPIOB->BRR = (1<<LCD_EN); /* EN = 0 for H-to-L pulse */
   delay_us(100); /* wait */
}

void lcd_string(uint8_t* data, uint8_t nBytes)	//Outputs string to LCD
{
register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		lcd_sendData(data[i]);
	}
}

void lcd_gotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	lcd_sendCommand(1<<LCD_DDRAM | DDRAMAddr);
	
}

void lcd_clr(void)	//Clears LCD
{
	lcd_sendCommand (1<<LCD_CLR);
}


void imprimir(uint32_t dato, uint32_t x, uint32_t y, char* medida){
   int aux,cont=0;
   unsigned char vec[16];
   lcd_gotoXY(x,y);
   while (dato > 0){
      aux = dato - ((dato / 10)*10);
      dato=dato / 10;
      vec[cont++] = (uint32_t)(aux + '0'); 
   }
   while(cont>0){
      lcd_sendData((uint8_t)vec[--cont]);
   }
   lcd_string(medida,2);
}

void clearLCD(){
   lcd_clr();
   lcd_gotoXY(0,0);
   lcd_string("C: ",3);
   lcd_gotoXY(0,1);
   lcd_string("L: ",3);
}



