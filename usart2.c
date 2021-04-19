#define F_CPU 3333333
#define USART2_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void USART2_init(void);
void USART2_sendChar(char c);
void USART2_sendString(char *str);

void USART2_init(void)
{
    PORTF.DIR &= ~PIN1_bm;
    PORTF.DIR |= PIN0_bm;

    USART2.BAUD = (uint16_t)USART2_BAUD_RATE(9600);

    USART2.CTRLB |= USART_TXEN_bm;
}

void USART2_sendChar(char c)
{
    while (!(USART2.STATUS & USART_DREIF_bm))
    {
        ;
    }
    USART2.TXDATAL = c;
}

void USART2_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART2_sendChar(str[i]);
    }
}

int main(void)
{
    USART2_init();

    while (1)
    {
        USART2_sendString("Hello World!\r\n");
        PORTD.OUTTGL |= PIN6_bm;
        _delay_ms(500);
    }
}
