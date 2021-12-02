#include <msp430.h>
#include "libTimer.h"
#define LED (BIT6)
void led_init() {
  P1DIR |= LED;/**< Green led on when CPU on */
  P1OUT |= LED;
  
//or_sr(0x8);          // CPU off;
}
void toggle(){
  P1OUT ^= LED;
}

void greenBeat(int secondCount){
  if(secondCount <= 125){
    P1OUT ^=LED;
  }
}
