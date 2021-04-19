#define F_CPU 16000000UL
#define F_CPU 3333333
#define BAUD_RATE 9600

//ports
#define PINC3 3

#define PIND5 5
#define PIND6 6

#define PINE2 2
#define PINE3 3

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// serial communication include
//#include "inc/usart.h"

char String[25];


//USART
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 *(float)BAUD_RATE)) + 0.5)

void USART0_init(void)
{
  PORTA.DIR = PIN1_bm;
  PORTA.DIR |= PIN0_bm;

  
  USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
  USART0.CTRLB |= USART_TXEN_bm;
  
  // set frame format
  //USART0.CTRLC = ;
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


void initialize() {
  cli();
  
  // select OSC20M freq = 16MHz
  FUSE.OSCCFG = 0x01;
  
  sei();
}


int main(void)
{

  USART0_init();
  initialize();

  /* Replace with your application code */
  while (1)
  {
    PORTD.OUTTGL |= PIN6_bm;
    USART0_sendString("Hello World!\r\n");
    _delay_ms(200);
  }
}
