
#define F_CPU 3333333
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(3333333 * 64 / (16 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


void USART0_init(void)
{
  PORTA.DIR &= ~PIN1_bm;
  PORTA.DIR |= PIN0_bm;
  USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
  USART0.CTRLB |= USART_TXEN_bm;
}
void USART0_sendChar(char c)
{
  while (!(USART0.STATUS & USART_DREIF_bm))
  {
    ;
  }
  USART0.TXDATAL = c;
}
void USART0_sendString(char *str)
{
  for(size_t i = 0; i < strlen(str); i++)
  {
  USART0_sendChar(str[i]);
  }
}
