#include "RELAY.h"
#include "usart3.h"

// Library for Arduino 4 Relay Shield on the Arduino UNO WIFI Rev2
// RELAY1 = D4 = PC6
// RELAY2 = D7 = PA1
// RELAY3 = D8 = PE3
// RELAY4 = D12 = PE1


// Set up the relevant pins as low outputs

void RELAY_init()
{
  // RELAY1 on PC6
  PORTC.DIRSET |= PIN6_bm;
  PORTC.OUTCLR |= PIN6_bm;

  // RELAY2 on PA1
  PORTA.DIRSET |= PIN1_bm;
  PORTA.OUTCLR |= PIN1_bm;

  // RELAY3 on PE3
  PORTE.DIRSET |= PIN3_bm;
  PORTE.OUTCLR |= PIN3_bm;

  // RELAY4 on PE1
  PORTE.DIRSET |= PIN1_bm;
  PORTE.OUTCLR |= PIN1_bm;
}


// Turns desired relay HIGH
// Param: int 1-4 indicating RELAY
// Return : 0 if success; 1 if invalid argument
int RELAY_high(int relay)
{
  switch (relay) {
    case 1:
      PORTC.OUTSET |= PIN6_bm;
      break;
    case 2:
       PORTA.OUTSET |= PIN1_bm;
       break;
     case 3:
       PORTE.OUTSET |= PIN3_bm;
       break;
     case 4:
       PORTE.OUTSET |= PIN1_bm;
       break;
    default:
      return 1;
  }

  return 0;
}


// Turns desired relay LOW
// Param: int 1-4 indicating RELAY
// Return : 0 if success; 1 if invalid argument
int RELAY_low(int relay)
{
    switch (relay) {
      case 1:
        PORTC.OUTCLR |= PIN6_bm;
          break;
       case 2:
         PORTA.OUTCLR |= PIN1_bm;
            break;
       case 3:
         PORTE.OUTCLR |= PIN3_bm;
         break;
       case 4:
         PORTE.OUTCLR |= PIN1_bm;
         break;
      default:
        return 1;
    }

    return 0;
}


// TOGGLES desired relay
// Param: int 1-4 indicating RELAY
// Return : 0 if success; 1 if invalid argument
int RELAY_toggle(int relay)
{
    switch (relay) {
      case 1:
        PORTC.OUTTGL |= PIN6_bm;
        break;
       case 2:
         PORTA.OUTTGL |= PIN1_bm;
         break;
       case 3:
         PORTE.OUTTGL |= PIN3_bm;
         break;
       case 4:
         PORTE.OUTTGL |= PIN1_bm;
         break;
      default:
        return 1;
    }

    return 0;
}
