#define F_CPU 2666666
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void USART3_init(void);
void USART3_sendChar(char c);
void USART3_sendString(char *str);

void USART3_init(void)
{
  // set alternate pins for USART3
    PORTMUX.USARTROUTEA &= ~PIN7_bm;
    PORTMUX.USARTROUTEA |= PIN6_bm;

    PORTB.DIR &= ~PIN5_bm;
    PORTB.DIR |= PIN4_bm;

    USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);

    USART3.CTRLB |= USART_TXEN_bm;
}

void USART3_sendChar(char c)
{
    while (!(USART3.STATUS & USART_DREIF_bm))
    {
        ;
    }
    USART3.TXDATAL = c;
}

void USART3_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART3_sendChar(str[i]);
    }
}

int main(void)
{
    USART3_init();

    while (1)
    {
        USART3_sendString("Hello World!\r\n");
        PORTD.OUTTGL |= PIN6_bm;
        _delay_ms(500);
    }
}
