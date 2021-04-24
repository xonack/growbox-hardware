#ifndef PEWLL_H
#define PEWLL_H

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

//  CONNECT CQRobots Ocean PEWLL (CQRSENYW002)
//  RED is VCC 5V
//  BLACK is GND
//  GREEN is Data to PORT A1 --> D7 on WIFIrev2

int PEWLL_read(void);
bool PEWLL_in_water(void);


#endif
