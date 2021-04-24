#include "DHT11.h"



//  Library for  DHT11 (humidity/temperature) sensor for the ATmega 4809
//  CONNECT DHT11 data to PORT A PIN 0 --> D2 on Arduino 2 on WIFIrev2
//  TIME SENSITIVE!! disable interrupts
//
//  CREDITS to efthymios-ks:
//  This is a stripped down version of his repo https://github.com/efthymios-ks/AVR-DHT


//Status variable
enum DHT_Status_t __DHT_STATUS;
char DHT11_string_buffer[64];


// FUNCTIONS -------------------------------------------------------------------

//Setup sensor.
void DHT_setup()
{
	_delay_ms(__DHT_Delay_Setup);
	__DHT_STATUS = DHT_Ok;
}

//Get sensor status.
enum DHT_Status_t DHT_get_status()
{
	return (__DHT_STATUS);
}


//Get raw sensor data
enum DHT_Status_t DHT_read_raw(uint8_t data[4])
{

  uint8_t buffer[5] = {0, 0, 0, 0, 0};
  uint8_t useconds, i;
	int8_t j;
  __DHT_STATUS = DHT_Ok;
	useconds = i = j = 0;

	sprintf(DHT11_string_buffer, "read raw status 0: %d!\r\n", __DHT_STATUS);
	USART3_sendString(DHT11_string_buffer);

  // ---- 1. Initiate Communication ---------
  if(__DHT_STATUS == DHT_Ok)
  {

    //Send data request
		PORTA.DIRSET |= PIN0_bm;         //PIN A0 as OUT
    PORTA.OUTCLR |= PIN0_bm;         //PIN A0 = 0
    _delay_ms(__DHT_Delay_Read);		// 20 ms

    //Set up A0 as input and pull-up
    PORTA.DIRCLR |= PIN0_bm;         // PIN A0 as IN
		PORTA.PIN0CTRL |= PIN3_bm;			 // PIN A0 enable pullup
		//PORTA.OUTSET |= PIN0_bm;         // PIN A0 = 1

    //Wait for response 20-40us
    while(PORTA.IN &= PIN0_bm)
    {
      _delay_us(2);
      useconds += 2;
      if (useconds > 60)
			{
				__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
				break;
			}
    }
  }

  // ----------------------------------------

	// sprintf(DHT11_string_buffer, "read raw status 1: %d; after %u useconds\r\n", __DHT_STATUS, useconds);
	// USART3_sendString(DHT11_string_buffer);

  // ---- 2. Await Response -----------------


  if(__DHT_STATUS == DHT_Ok)
  {

    // First response; LOW for 80us
    useconds = 0;
    while(!(PORTA.IN &= PIN0_bm))
    {
      _delay_us(2);
			useconds += 2;
			if (useconds > 100)
			{
				__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
				break;
			}
    }

    // Second response; HIGH for 80us
    useconds = 0;
    while(PORTA.IN &= PIN0_bm)
    {
      _delay_us(2);
			useconds += 2;
			if (useconds > 100)
			{
				__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
				break;
			}
    }

  }

  // ----------------------------------------

	sprintf(DHT11_string_buffer, "read raw status 2: %d!\r\n", __DHT_STATUS);
	USART3_sendString(DHT11_string_buffer);

  // ---- 3. Data Transmisson ---------------

  if (__DHT_STATUS == DHT_Ok)
	{
		//Reading 5 bytes, bit by bit
		for (i = 0 ; i < 5 ; i++)
			for (j = 7 ; j >= 0 ; j--)
			{
				//There is always a leading LOW level of 50 us
				useconds = 0;
				while(!(PORTA.IN &= PIN0_bm))
				{
					_delay_us(2);
					useconds += 2;
					if (useconds > 70)
					{
						__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
						j = -1;								//Break inner for-loop
						i = 5;								//Break outer for-loop
						break;								//Break while loop
					}
				}

				if (__DHT_STATUS == DHT_Ok)
				{
					//We read data bit || 26-28us means '0' || 70us means '1'
					_delay_us(35);							//Wait for more than 28us
					if (PORTA.IN &= 1)	{			//If HIGH
						buffer[i] |= (1UL<<j);				//bit = '1'
          }
					useconds = 0;
					while(PORTA.IN &= PIN0_bm)
					{
						_delay_us(2);
						useconds += 2;
						if (useconds > 100)
						{
							__DHT_STATUS = DHT_Error_Timeout;	//Timeout error
							break;
						}
					}
				}
			}
	}


  // ----------------------------------------

	sprintf(DHT11_string_buffer, "read raw status 4: %d!\r\n", __DHT_STATUS);
	USART3_sendString(DHT11_string_buffer);

  // ---- 4. Checksum -----------------------
  if(__DHT_STATUS == DHT_Ok)
  {
    if (((uint8_t)(buffer[0] + buffer[1] + buffer[2] + buffer[3])) != buffer[4])
		{
			__DHT_STATUS = DHT_Error_Checksum;	//Checksum error
		}
		else
		{
			//Build returning array
			//data[0] = humidity		(int)
			//data[1] = humidity		(dec)
			//data[2] = temperature		(int)
			//data[3] = temperature		(dec)
			//data[4] = Checksum
			for (i = 0 ; i < 4 ; i++)
				data[i] = buffer[i];
		}
  }

	// -----------------------------------------

	sprintf(DHT11_string_buffer, "read raw status X: %d!\r\n", __DHT_STATUS);
	USART3_sendString(DHT11_string_buffer);

  return DHT_get_status();
}


//Read temperature and humidity
enum DHT_Status_t DHT11_read(int8_t *temperature, int8_t *humidity)
{

  // pass out temp and humidity
  int8_t data[4] = { 0, 0, 0, 0 };

  //Read data

	enum DHT_Status_t status =  DHT_read_raw(data);

  if (status == DHT_Ok)
	{

		*temperature = data[2];
		*humidity = data[0];

		//Check values
		if ((*temperature < __DHT_Temperature_Min) || (*temperature > __DHT_Temperature_Max))
			__DHT_STATUS = DHT_Error_Temperature;
		else if ((*humidity < __DHT_Humidity_Min) || (*humidity > __DHT_Humidity_Max))
			__DHT_STATUS = DHT_Error_Humidity;
	}
	//
	// sprintf(DHT11_string_buffer, "read %u!\r\n", __DHT_STATUS);
	// USART3_sendString(DHT11_string_buffer);
	//
	// sprintf(DHT11_string_buffer, "read get status %u!\r\n", DHT_get_status());
	// USART3_sendString(DHT11_string_buffer);

  return DHT_get_status();
}


//Pass out humidity
enum DHT_Status_t DHT11_get_humidity(int8_t *humidity)
{
  int8_t *waste = 0;
  return DHT11_read(waste, humidity);
}


//Pass out temperature
enum DHT_Status_t DHT11_get_temperature(int8_t *temperature)
{
  int8_t *waste = 0;
  return DHT11_read(temperature, waste);
}
