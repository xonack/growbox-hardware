#ifndef DHT11_H
#define DHT11_H

#define F_CPU 2666666

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

//CONNECT DHT11 data to PA0 --> D2 on WIFIrev2


#define DHT_ReadInterval			1500
#define __DHT_Delay_Setup			1
#define __DHT_Temperature_Min	0
#define __DHT_Temperature_Max	50
#define __DHT_Humidity_Min		20
#define __DHT_Humidity_Max		90
#define __DHT_Delay_Read		  20

enum DHT_Status_t
{
	DHT_Ok,
	DHT_Error_Humidity,
	DHT_Error_Temperature,
	DHT_Error_Checksum,
	DHT_Error_Timeout
};

void DHT_setup(void);
enum DHT_Status_t DHT_get_status(void);
enum DHT_Status_t DHT11_read_raw(uint8_t data[4]);
enum DHT_Status_t DHT11_read(int8_t *temperature, int8_t *humidity);
enum DHT_Status_t DHT11_get_humidity(int8_t *humidity);
enum DHT_Status_t DHT11_get_temperature(int8_t *temperature);

#endif
