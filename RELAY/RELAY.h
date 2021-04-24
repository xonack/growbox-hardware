#ifndef RELAY_H
#define RELAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart3.h"

// Library for Arduino 4 Relay Shield on the Arduino UNO WIFI Rev2
// RELAY1 = D4 = PC6
// RELAY2 = D7 = PA1
// RELAY3 = D8 = PE3
// RELAY4 = D12 = PE1

void RELAY_init(void);
int RELAY_high(int relay);
int RELAY_low(int relay);
int RELAY_toggle(int relay);


#endif
