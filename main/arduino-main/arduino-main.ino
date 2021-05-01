#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE    DHT11


// ======================== PERIPHERALS ========================================
// 4 Relay Shield --------------------------------------------------------------
#include "RELAY.h"
#define LAMP 1
#define FAN 4

// Photo Electric Liquid Level Sensor ------------------------------------------
#include "PEWLL.h"

// BUZZER ----------------------------------------------------------------------
#define BUZZER 5


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(9600);

  dht.begin();

  RELAY_init();

  //BUZZER SETUP;
  pinMode(BUZZER ,OUTPUT);

}

// ISR for BUZZER
// ISR(TCA0_OVF_vect)
// {
//   //USART3_sendString("ISR\n");
//   PORTB.OUTTGL |= PIN2_bm;
//   // clear interrupt overflow flag
//   TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
// }

void loop() {

  // WATER LEVEL

  if (!PEWLL_in_water())
  {
    Serial.println("not in water");
    tone(BUZZER, 500);
  }
  else
  {
    Serial.println("in water");
    noTone(BUZZER);

  }


  // TEMPERATURE & HUMIDITY
  sensors_event_t event;
  float temperature = 0;
  float humidity = 0;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));

  }
  else {
    temperature = event.temperature;
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    humidity = event.relative_humidity;
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  if (temperature && humidity) {


    Serial.println(temperature);
    Serial.println(humidity);

    if (temperature >= 40) {
      RELAY_high(LAMP); // OFF
      RELAY_high(FAN);  // ON
    }
    else if (temperature >= 30 || humidity >= 50) {
      RELAY_low(LAMP);  // ON
      RELAY_high(FAN);  // ON
    }
    else {
      RELAY_low(LAMP);  // ON
      RELAY_low(FAN);   // OFF
    }

  }

  delay(1000);
  // digitalWrite(LED_BUILTIN, HIGH);
  // // digitalWrite(4, HIGH);
  // RELAY_toggle(LAMP);  // OFF
  // RELAY_toggle(FAN);  // ON
  // Serial.print("high\n");
  //
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  // digitalWrite(4, LOW);
  Serial.print("loop\n");
}
