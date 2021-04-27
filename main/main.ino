
//#define F_CPU 16000000UL
#define F_CPU 2666666

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define CLK_PER 2666666
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(CLK_PER * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// serial communication include

char string_buffer[64];

// USB USART -------------------------------------------------------------------

#include "usart3.h"

// DHT11 -----------------------------------------------------------------------

#include "DHT11.h"

// Photo Electric Liquid Level -------------------------------------------------

#include "PEWLL.h"

// 4 Relay Shield --------------------------------------------------------------

#include "RELAY.h"

// WIFI --------------------------------------------------------------

//#include "WIFI.h"

// BUZZER --------------------------------------------------------------

#include "BUZZER.h"


void initialize() {

  cli();

  // CLK_MAIN defaults to 16MHz
  USART3_init();
  USART3_sendString("USART initialized !\r\n");

  DHT_setup();
  USART3_sendString("DHT initialized!\n");

  RELAY_init();
  USART3_sendString("RELAYS initialized!\n");

  BUZZER_init();
  USART3_sendString("BUZZER initialized!\n");

  sei();
}


// ISR for BUZZER
ISR(TCA0_OVF_vect)
{
  //USART3_sendString("ISR\n");
  PORTB.OUTTGL |= PIN2_bm;
  // clear interrupt overflow flag
  TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}


int main(void)
{

  initialize();
  int count = 0;
  int dht_status = -1;

  while (1)
  {

    PORTD.OUTTGL |= PIN6_bm;

    sprintf(string_buffer, "TCA0 CNT: %d\r\n", TCA0.SINGLE.CNT);
    USART3_sendString(string_buffer);


    // WATER LEVEL TEST

    // Connect to Arduino D7 --> PA1
    int water_level = PEWLL_read();

    sprintf(string_buffer, "Water Level: %u\r\n", water_level);
    USART3_sendString(string_buffer);


    // DHT11 TEST ------------------------------------

    // sprintf(string_buffer, "%d!\r\n", count++);
    // USART3_sendString(string_buffer);
    //
    // int8_t temperature = 0;
    // int8_t humidity = 0;
    //
    // cli();
    //
    // dht_status = DHT11_read(&temperature, &humidity);
    // sprintf(string_buffer, "temp: %u; humidity: %u; DHT_status: %u\r\n", temperature, humidity, dht_status);
    // USART3_sendString(string_buffer);
    //
    // sei();
    //
    // if (temperature >= 24 || humidity >= 50) {
    //   PORTD.OUTSET |= PIN6_bm;
    // }
    // else {
    //   PORTD.OUTCLR |= PIN6_bm;
    // }

    //  ----------------------------------------------


    // DHT11 request Test ----------------------------

    //Send data request
    // sprintf(string_buffer, "PRE: %u; DIR %u\r\n", (PORTA.IN & PIN0_bm), PORTA.DIR);
    // USART3_sendString(string_buffer);
    //
		// PORTA.DIRSET |= PIN0_bm;         //PIN A0 as OUT
    // PORTA.OUTCLR |= PIN0_bm;         //PIN A0 = 0
    // // sprintf(string_buffer, "PULL LOW %u; DIR %u\r\n", (PORTA.IN & PIN0_bm), PORTA.DIR);
    // // USART3_sendString(string_buffer);
    // _delay_ms(20);
    //
    // //Set up A0 as input and pull-up
    // PORTA.DIRCLR |= PIN0_bm;         // PIN A0 as IN
		// PORTA.PIN0CTRL |= PIN3_bm;			 // PIN A0 enable pullup
    //
    // // sprintf(string_buffer, "PULL HIGH %u; DIR %u\r\n", (PORTA.IN & PIN0_bm), PORTA.DIR);
    // // USART3_sendString(string_buffer);
    //
    // while(PORTA.IN &= PIN0_bm)
    // {
    // }
    //
    //
    // USART3_sendString("Response!\n");

    // -----------------------------------------

    // RELAY TEST ------------------------------

    // RELAY_high(4);
    // _delay_ms(1000);
    // RELAY_low(4);
    // _delay_ms(1000);
    // RELAY_toggle(4);
    // _delay_ms(1000);
    // RELAY_toggle(4);

    // ------------------------------------------

    // WIFI TEST --------------------------------

    // ------------------------------------------

    // BUZZER TEST --------------------------------

    // init
    // set D6 as output
    // set D6 low
    // enable TCA0 interrupt
    // set compare value to 0

    // ISR
    // if TCA0 is triggered --> toggle pin D5

    if (!PEWLL_in_water())
    {
      //TCA0.SINGLE.PER = 888;
      BUZZER_on();
    }
    else
    {
      BUZZER_off();
    }







    _delay_ms(2000);
  }
}
