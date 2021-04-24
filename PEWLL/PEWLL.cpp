#include "PEWLL.h"
#include "usart3.h"


int PEWLL_read()
{
  int water_level = (PORTF.IN & PIN4_bm)>>4;
  return water_level;
}

bool PEWLL_in_water()
{
  return (PEWLL_read() == 1);
}
