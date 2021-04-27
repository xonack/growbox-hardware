#ifndef BUZZER_H
#define BUZZER_H

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

//Connect passive module activated by NPN PN2222 to pin D5 --> PB2

void BUZZER_init(void);
void BUZZER_on(void);
void BUZZER_off(void);

#endif
