# MSP430N1202Img #

Display a bit-mapped image on the Nokia 1202 LCD.
This LCD is a monochrome, backlit, 96x68 pixel display.
It uses the ST Microelectronics STE2007 driver chip.

The image was originally drawn for a demo at Dorkbot Bristol in 2012.
The PPM file is converted into a C header file by a small utility program
'ppm2h' which is built and executed by the Makefile.

The program is in C and may be compiled with GCC on Linux.

## Connections ##

| Name   | Port | Pin | Activity    |
|:-------|:-----|:----|:------------|
| CS     | P1.4 |  6  | Chip Select |
| SCK    | P1.7 |  9  | SPI Clock   |
| SDA    | P1.5 |  7  | SPI Data    |
| RESET  | P1.2 |  4  | Unused      |

## Building and Programming ##

First of all, we'll need the MSP430 cross-compiler:

`sudo apt install gcc-msp430`

To program the chip, we need 'mspdebug':

`sudo apt install mspdebug`

To build the PPM conversion tool, we'll need 'build-essential':

`sudo apt install build-essential`

Finally, to compile and link the code:

`make`

An additional Makefile target is used to program the chip:

`make prog`

