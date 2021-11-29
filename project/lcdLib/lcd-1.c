/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);
  short col = 30, row = 30;
  short startc = 60, startr = 60;
  
  for (col = 0; col < 30;){
    drawPixel(startc+col, startr+row, COLOR_PINK);
    drawPixel(startc-col, startr+row, COLOR_PINK);
    row += 1;
    col +=1;
  }
}
