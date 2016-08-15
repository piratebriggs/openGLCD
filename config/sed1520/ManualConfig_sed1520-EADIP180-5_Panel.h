/*
 * ManualConfig_sed1520-EADIP180-5_Panel.h - Custom configuration for openGLCD library
 *
 * Use this file to set io pins and LCD panel parameters
 *
 *    This configuration file is for the DIP180-5 module manufactured by Electronic Assembly.
 *    This module uses 3 sed1520 chips each controlling one third of the display.
 *
 *    The datasheet can be downloaded from here:
 *    http://www.lcd-module.de/eng/pdf/grafik/dip180-5e.pdf
 *    
 *
 *                                  View from Front of LCD
 *
 *    <--------------------------------------------------- 180 Pixels --------------------------------------------------->
 *    +--------------------------------------+-------------------------------------+-------------------------------------+
 *    |                                      |                                     |                                     | ^
 *    |<------------ 60 Pixels ------------->|                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | 32 pixels
 *    |    Chip 0 controls these pixels      |    Chip 1 controls these pixels     |     Chip 2 Controls these pixels    | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | |
 *    |                                      |                                     |                                     | v
 *    +--------------------------------------+-------------------------------------+-------------------------------------+
 *
 *    Pins are on the back of the module and are labeled.
 *    There are nine pins vertically on each side of the module PCB.
 *
 *    +-------------------------------------------+
 *    |Pin|Symbol|        Function                | Hook To
 *    +-------------------------------------------+
 *    | 1 | Vss  | Ground                         | Ground
 *    +-------------------------------------------+
 *    | 2 | Vdd  | +5v (4ma max)                  | +5v
 *    +-------------------------------------------+
 *    | 3 | VEE  | Contrast input voltage         |
 *    +-------------------------------------------+
 *    | 4 | A0/DI| H = Data, L=instruction/Status | glcdPinDI
 *    +-------------------------------------------+
 *    | 5 | RW   | H = Read, L = Write            | glcdPinRW
 *    +-------------------------------------------+
 *    | 6 | E1   | chip 0 enable strobe           | glcdPinE1
 *    +-------------------------------------------+
 *    | 7 | DB0  | Data Bit 0                     | glcdPinData0
 *    +-------------------------------------------+
 *    | 8 | DB1  | Data Bit 1                     | glcdPinData1
 *    +-------------------------------------------+
 *    | 9 | DB2  | Data Bit 2                     | glcdPinData2
 *    +-------------------------------------------+
 *    |10 | DB3  | Data Bit 3                     | glcdPinData3
 *    +-------------------------------------------+
 *    |11 | DB4  | Data Bit 4                     | glcdPinData4
 *    +-------------------------------------------+
 *    |12 | DB5  | Data Bit 5                     | glcdPinData5
 *    +-------------------------------------------+
 *    |13 | DB6  | Data Bit 6                     | glcdPinData6
 *    +-------------------------------------------+
 *    |14 | DB7  | Data Bit 7                     | glcdPinData7
 *    +-------------------------------------------+
 *    |15 | E2   | chip 1 enable strobe           | glcdPinE2
 *    +-------------------------------------------+
 *    |16 | RES  | Reset (active low)             | glcdPinRES
 *    +-------------------------------------------+
 *    |17 | E3   | chip 2 enable strobe           | glcdPinE3
 *    +-------------------------------------------+
 *    |18 | C    | Backlight cathode (ground)     | through resistor to ground or
 *    +-------------------------------------------+ or use backlight circuit and glcdPinBL pin
 *
 * Sample Backlight curcuit:
 *
 * (LCD BL cathode)--[resistor]---+
 *                                |
 *                                C
 *                                |
 * (glcdPinBL)--[ Resistor ]---B-|> (NPN) 2N2222A/2N3904 etc...
 *                  1k            |
 *                                E
 *                                |
 *                              (GND)
 */

#ifndef GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for panel configuration
 */
#define glcd_ConfigName "sed1520-EADIP180-5-Manual"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 180
#define DISPLAY_HEIGHT 32

// panel controller chips
#define CHIP_WIDTH     60  // pixels per chip 
#define CHIP_HEIGHT    32  // pixels per chip 

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

/*
 * Pins can be assigned using arduino pin numbers 0-n
 * Pins can also be assigned using PIN_Pb 
 *    where P is port A-L and b is bit 0-7
 *     Example: port D bit 3 is PIN_D3
 *
 */

#define glcdPinData0	PIN_A0
#define glcdPinData1	PIN_A1
#define glcdPinData2	PIN_A4
#define glcdPinData3	PIN_A5
#define glcdPinData4	PIN_A6
#define glcdPinData5	PIN_A7
#define glcdPinData6	PIN_A6
#define glcdPinData7	PIN_A5

#define glcdPinRW	PIN_C3
#define glcdPinDI	PIN_C4

#define glcdPinE1	PIN_C5
#define glcdPinE2	PIN_C2
#define glcdPinE3	PIN_C1

#define glcdRES         PIN_C6

//#define glcdPinBL	PIN_C7 // optional backlight control (requires additional circuitry)

/*
 * Define for Backlight Control active level
 */
//                    BLpin    on   off
#define glcd_BLctl glcdPinBL, HIGH, LOW


// defines for panel specific timing 
#define GLCD_tDDR    290    /* tACC6: Data Delay time (E high to valid read data)             */
#define GLCD_tAS      20    /* tAW6:  Address setup time (ctrl line changes to E high)        */
#define GLCD_tDSW    200    /* tDS6:  Data setup time (Write data lines setup to dropping E)  */
#define GLCD_tWH     450    /* tEW:   E hi level width (minimum E hi pulse width)             */ 
#define GLCD_tWL     450    /* E lo level width (minimum E lo pulse width)                    */


// calculate number of chips & round up if width is not evenly divisable
#define glcd_CHIP_COUNT (((DISPLAY_WIDTH + CHIP_WIDTH - 1)  / CHIP_WIDTH) * ((DISPLAY_HEIGHT + CHIP_HEIGHT -1) / CHIP_HEIGHT))

#include "device/sed1520_Device.h"
#endif //GLCD_PANEL_CONFIG_H
