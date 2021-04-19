#define F_CPU 3333333
#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void USART1_init(void);
void USART1_sendChar(char c);
void USART1_sendString(char *str);

void USART1_init(void)
{
    PORTC.DIR &= ~PIN1_bm;
    PORTC.DIR |= PIN0_bm;

    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(9600);

    USART1.CTRLB |= USART_TXEN_bm;
}

void USART1_sendChar(char c)
{
    while (!(USART1.STATUS & USART_DREIF_bm))
    {
        ;
    }
    USART1.TXDATAL = c;
}

void USART1_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART1_sendChar(str[i]);
    }
}

int main(void)
{
    USART1_init();

    while (1)
    {
        USART1_sendString("Hello World!\r\n");
        PORTD.OUTTGL |= PIN6_bm;
        _delay_ms(500);
    }
}
