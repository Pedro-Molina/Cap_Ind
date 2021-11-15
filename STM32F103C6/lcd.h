
#define LCD_RS 15
#define LCD_RW 14
#define LCD_EN 13

#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

#define LCD_DDRAM           7	

#define LCD_CLR             0

#include <stm32f103x6.h>
#include "delay.h"
#include <stdint.h>

void lcd_init(void);
void lcd_sendCommand (uint8_t);
void lcd_sendData (uint8_t );
void lcd_putValue (uint8_t );
void lcd_string(uint8_t* , uint8_t );
void lcd_gotoXY(uint8_t x, uint8_t y);
void lcd_clr(void);

void imprimir(uint32_t, uint32_t, uint32_t,char*);
void clearLCD(void);

