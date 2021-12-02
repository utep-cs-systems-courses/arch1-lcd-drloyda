#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

void buzzer_init()
{
  /* 

       Direct timer A output "TA0.1" to P2.6.  

        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output

  */

  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone)*/
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}
extern secCount;
int secondCount = 0;
int i = 0;
int j = 0;
int k = -1;
int notes[64] = {2272, 3407, 4291, 5115, 2554, 3407, 4291, 5115, 2706, 3407, 4291, 5155,
		 2554, 3407, 4291, 5115, 2554, 3824, 4545, 5730, 2865, 3824, 4545, 5730,
		 3034, 3824, 4545, 5730, 2865, 3824, 4545, 5730, 2865, 4291, 5115, 6079,
		 3034, 4291, 5115, 6079, 3215, 4291, 5115, 6079, 3034, 4291, 5115, 6079,
		 3034, 4545, 5730, 6825, 3407, 4545, 5730, 6825, 3610, 4545, 5730, 6825,
		 3407, 4545, 5730, 6825};
int notes2[26] = {5115, 0, 5115, 0, 5115, 0, 5115, 0, 5115, 4819, 5730, 0, 5730, 0, 5730,
		  0, 5730, 0, 5730, 0 ,5730, 0 , 5730, 5115, 4291, 5115};

int notes3[37] = {1517, 1607, 1517, 1607, 1517, 2025, 1703, 1910, 2273, 3822, 3034, 2273,
		  2025, 3034, 2408, 2025, 1910, 3034, 1517, 1607, 1517, 1607, 1517, 1607,
		  2025, 1703, 1910, 2273, 3822, 3034, 2273, 2025, 3034, 1910, 2025, 227};

int time[26] = {62, 31, 62, 31, 62, 31, 62, 31, 62, 31, 31, 62, 31, 125, 31, 62, 31, 62,
		31, 31, 31, 62, 31, 31, 31, 125};

int time2[37] = {0,46, 46, 46, 46, 46, 46, 46, 46, 92, 46, 46, 46, 92, 46, 46, 46, 92, 46,
		 46, 46, 46, 46, 46, 46, 46, 46 ,46 ,92, 46, 46, 46, 92, 46, 46, 46, 92};
//plays the buzzer based on notes in notes array at every second
void playSongOne(){
  if(secCount >= 46){
    secCount = 0;

    if(i >= 64){
      i = 0;
    }
    toggle();
    buzzer_set_period(notes[i]);
    i++;
  }
}

//plays the buzzer based on notes in second notes array
//based on the timing for each note
void playSongTwo(){
  if(secCount >= time[j]){
    secCount = 0;
    if(j >= 26){
      j = -1;
    }
    greenBeat(secCount);
    buzzer_set_period(notes2[j]);
    j++;
  }
}

void playSongThree(){
  if(secCount >= time2[k]){
    secCount = 0;
    if(k >= 37){
      k = -1;
    }
    greenBeat(secCount);
    buzzer_set_period(notes3[k]);
    k++;
  }
}
