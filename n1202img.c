/* n1202img --- display an image on the Nokia 1202 LCD      2012-02-22 */

#include <msp430.h>

#include "dorkdemo.h"
#include "popup.h"

#define SDA     BIT5
#define SCK     BIT7
#define CS      BIT4
#define RESET   BIT2

#define LCD_DATA 0x100

void n1202init(void);
void n1202clear(void);
void n1202goto(const int row, const int col);
void n1202write(int d);
void dally(const int dally);


int main(void)
{
   int i;
   int row, col;
   
   WDTCTL = WDTHOLD | WDTPW;   // Disable watchdog timer

   P1SEL = 0x00;               // Set up GPIO pins
   P1DIR = SDA | SCK | CS | RESET;

   n1202init();
   
   n1202goto(0, 0);

   // Display 96x68 pixel image
   for (i = 0; i < (9 * 96); i++)
      n1202write(LCD_DATA | Dorkdemo[i]);
      
   for (i = 0; i < 100; i++)
      dally(10000);
   
   // Display popup image
   for (row = 0; row < 4; row++) {
      n1202goto(row + 2, (96 - 48) / 2);
      
      for (col = 0; col < 48; col++)
         n1202write(LCD_DATA | Popup[(row * 48) + col]);
   }
   
   while (1)
      ;
   
   // Never returns
}


/* n1202init --- initialise the Nokia 1202 LCD (STE2007 controller) */

void n1202init(void)
{
   P1OUT |= RESET;
   
   n1202write(0xE2);      // Software reset
   
   n1202write(0xA4);      // Power saver OFF
   n1202write(0x2F);      // Power control set
   n1202write(0xAF);      // Display ON
   
   n1202write(0xC0);      // Display common driver normal
   
   n1202write(0x80 | 16); // Electronic volume to 16
   
   n1202clear();
   
   n1202write(0xef);      // Set refresh rate
   n1202write(3);         // 65 Hz
   
   n1202write(0x3d);      // Set Charge Pump multiply factor
   n1202write(0);         // 5x
   
   n1202write(0x36);      // Bias ratio 1/4
   
   n1202write(0xad);      // set contrast
   n1202write(0x20 | 20); // 20/32
   
   n1202write(0xe1);
   n1202write(0);
   
   n1202write (0xa6);     // Display normal
}


/* n1202clear --- clear the LCD display memory */

void n1202clear(void)
{
   int i;

   n1202goto(0, 0);

   for (i = 0; i < (9 * 96); i++) {
      n1202write(LCD_DATA | 0x00);
   }
}


/* n1202goto --- move the cursor in the STE2007 to a given row, column */

void n1202goto(const int row, const int col)
{
   n1202write(0xB0 | (row & 0x0F)); // Set page address
   n1202write(0x10 | (col >> 4));   // Set DDRAM column addr: upper 3-bits
   n1202write(0x00 | (col & 0x0F)); // ...lower 4-bits
}


/* n1202write --- write a 9-bit word to the STE2007 via SPI */

void n1202write(int d)
{
   unsigned char i;
   
   P1OUT &= ~CS;
   
   for (i = 0; i < 9; i++) {
      P1OUT &= ~SDA;
      
      if (d & 0x100)
         P1OUT |= SDA;
      
      P1OUT &= ~SCK;
      P1OUT |= SCK;
      
      d <<= 1;
   }
   
   P1OUT |= CS;
}


/* dally --- rudimentary delay loop */

void dally(const int dally)
{
   volatile int i;
   
   for (i = 0; i < dally; i++)
      ;
}

