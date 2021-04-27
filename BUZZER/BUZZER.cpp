#include "BUZZER.h"


void BUZZER_init(void) {
  // BUZZER setup
  PORTB.DIRSET |= PIN2_bm;
  PORTB.OUTCLR |= PIN2_bm;

  //enable interrupt
  TCA0.SINGLE.INTCTRL &= ~(TCA_SINGLE_OVF_bm);
  // normal mode
  TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
  TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);
  // set period to 0
  TCA0.SINGLE.PER = 6900;

  TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;
}

void BUZZER_on(void)
{
  TCA0.SINGLE.INTCTRL |= TCA_SINGLE_OVF_bm;
}

void BUZZER_off(void)
{
  TCA0.SINGLE.INTCTRL &= ~(TCA_SINGLE_OVF_bm);
}
