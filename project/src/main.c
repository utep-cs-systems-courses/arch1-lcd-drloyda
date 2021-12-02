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
#define SWITCHES 15

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
  }else if((p2val & SWITCHES) == 13){ //toggle sw2 on or off
    turnOff();
    sw2Down ^= 1;
  }else if((p2val & SWITCHES) == 11){
    turnOff();
    sw3Down ^= 1;
  }else if((p2val & SWITCHES) == 7){
    turnOff();
    sw4Down ^= 1;
  }
}

int playSong = 0;
void turnOff(){
  sw1Down &= ~sw1Down;
  sw2Down &= ~sw2Down;
  sw3Down &= ~sw3Down;
  sw4Down &= ~sw4Down;
  playSong &= ~playSong;
}

// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;
int secCount = 0;
void update_shape();


void main()
{
  
  led_init();		/**< Green led on when CPU on */
  configureClocks();
  lcd_init();
  switch_init();
  //buzzer_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  buzzer_init();
  clearScreen(COLOR_BLACK);
  drawString5x7(15,60,"Press Any Button", COLOR_WHITE, COLOR_BLACK);
  drawString5x7(40, 70, "To Start", COLOR_WHITE, COLOR_BLACK);
  
  while (1) {
    if(sw1Down == 1){ //if sw1 pressed
      turnOff();
      playSong = 1;
      drawTriforce(65,40);
    }else if(sw2Down == 1){ //if sw2 pressed
      turnOff();
      playSong = 2;
      drawFistBump(65,70);
    }else if(sw3Down == 1){ //if sw3 pressed
      turnOff();
      playSong = 3;
      drawPiano(65,40);
    }else if(sw4Down == 1){ //if sw4 pressed
      buzzer_set_period(0);
      clearScreen(COLOR_BLUE);
      turnOff();
      drawString5x7(10,70,"ERROR 404: PAGE NOT FOUND", COLOR_WHITE, COLOR_BLUE);
    }
    
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
