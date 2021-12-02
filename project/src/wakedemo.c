#include <msp430.h>
#include <libTimer.h>
#include <math.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;
int sw1Down = 0;
int sw2Down = 0;
int sw3Down = 0;
int sw4Down = 0;
void
switch_interrupt_handler()
{
  char p2val = P2IN;/* switch is in P2 */
  /* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  /* up=no sequence, down=sequence */
 
  if((p2val & SWITCHES) == 14){ //toggle sw1 on or off
    turnOff();
    sw1Down ^= 1;
    // clearScreen(COLOR_DARK_GREEN);
    //drawHeart(65,40);
  }else if((p2val & SWITCHES) == 13){ //toggle sw2 on or off
    turnOff();
    sw2Down ^= 1;
    //clearScreen(COLOR_RED);
    //drawHexagon(65,40);
  }else if((p2val & SWITCHES) == 11){
    turnOff();
    sw3Down ^= 1;
  }else if((p2val & SWITCHES) == 7){
    turnOff();
    sw4Down ^= 1;
  }
}

int playOne = 0;
int playTwo = 0;
int playThree = 0;
void turnOff(){
  sw1Down &= ~sw1Down;
  sw2Down &= ~sw2Down;
  sw3Down &= ~sw3Down;
  sw4Down &= ~sw4Down;
  playOne &= ~playOne;
  playTwo &= ~playTwo;
  playThree &= ~playThree;
}

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;
int secCount = 0;
int ps1 = 0;
void wdt_c_handler()
{
  //static int secCount = 0;

  secCount ++;
  if(playOne){
    playSongOne();
  }else if(playTwo){
    playSongTwo();
  }else if(playThree){
    playSongThree();
  }else{
    buzzer_set_period(0);
  }
  //if (secCount >= 250) {		/* 10/sec */
    // secCount = 0;
    // redrawScreen = 1;
    //}
}
void update_shape();


void main()
{
  
  led_init();		/**< Green led on when CPU on */
  // buzzer_init();
  configureClocks();
  lcd_init();
  switch_init();
  //buzzer_init(); 
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  buzzer_init();
  clearScreen(COLOR_BLACK);
  // buzzer_set_period(5000);
  // playSongOne(secCount);
  // clearScreen(COLOR_DARK_GREEN);
  
  while (1) {
    if(sw1Down == 1){ //if sw1 pressed
      turnOff();
      playOne = 1;
      drawTriforce(65,40);
    }else if(sw2Down == 1 ){ //if sw2 pressed
      turnOff();
      playTwo = 1;
      drawFistBump(65,70);
    }else if(sw3Down == 1){
      turnOff();
      playThree = 1;
      drawPiano(65,40);
    }else if(sw4Down ==1){
      clearScreen(COLOR_BLUE);
      turnOff();
    }
    // turnOff();
   } 
}

    
    
void
update_shape()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static int colStep = 5, rowStep = 5;
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0;
    if (step <= 1) {
    row = row + step;
    clearScreen(COLOR_DARK_GREEN);
    drawTriforce(65, 40);
    step++;
  } else {
    clearScreen(COLOR_BLACK);
    step = 0;
  }
}


/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this iterrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
