/*
 * ManualConfig_pt6520-BugDisplay_Panel.h - Custom configuration for openGLCD library
 *
 * Use this file to set io pins and LCD panel parameters
 *
 *    This configuration file is for the display module from a Pure TheBug radio.
 * 
 *    This module uses 2 SED1520 chips each controlling one half of the 
 *    display. There is a blue LED backlight, and you must provide a current
 *    limiting resistor. It also contains an onboard contrast pot.
 * 
 *    The module also hosts 6 buttons that can be read using only 2 
 *    additional pins. When any button is pressed, pin BIN is taken low.
 *    To read which button(s) are depressed, make sure E1 & E2 are low and
 *    that the data pins are in INPUT mode then set pin BOE to LOW and read the
 *    data pins. Bits 0-6 indicate the button(s) pressed (LOW = pressed).
 *    After reading data pins, set pin BOE to HIGH before continuing with sketch.
 * 
 *    This Display is very easy to hook up as it needs no additional components 
 *    other than a current limiting resistor for the backlight.
 * 
 *    WARNING: pins BOE & BIN must be pulled high if buttons are not being used.
 *
 *    Left (Brown) socket (viewed from back of module)
 *    +-------------------------------------------+
 *    |Pin|Symbol|        Function                | Hook To
 *    +-------------------------------------------+
 *    | 1 | Vss  | Ground                         | Ground
 *    +-------------------------------------------+
 *    | 2 | Vdd  | +5v (?ma max)                  | +5v
 *    +-------------------------------------------+
 *    | 3 | A0/DI| H = Data, L=instruction/Status | glcdPinDI
 *    +-------------------------------------------+
 *    | 4 | RW   | H = Read, L = Write            | glcdPinRW
 *    +-------------------------------------------+
 *    | 5 | E1   | chip 0 enable strobe           | glcdPinE1
 *    +-------------------------------------------+
 *    | 6 | E2   | chip 1 enable strobe           | glcdPinE2
 *    +-------------------------------------------+
 *    | 7 | Unk  | +5v returned from the module?  | N/C
 *    +-------------------------------------------+
 *    | 8 | DB0  | Data Bit 0                     | glcdPinData0
 *    +-------------------------------------------+
 *    | 9 | DB1  | Data Bit 1                     | glcdPinData1
 *    +-------------------------------------------+
 *    |10 | Vss  | Ground                         | Ground
 *    +-------------------------------------------+

 *    Right (White) socket (viewed from back of module)
 *    +-------------------------------------------+
 *    | 1 | DB2  | Data Bit 2                     | glcdPinData2
 *    +-------------------------------------------+
 *    | 2 | DB3  | Data Bit 3                     | glcdPinData3
 *    +-------------------------------------------+
 *    | 3 | DB4  | Data Bit 4                     | glcdPinData4
 *    +-------------------------------------------+
 *    | 4 | DB5  | Data Bit 5                     | glcdPinData5
 *    +-------------------------------------------+
 *    | 5 | DB6  | Data Bit 6                     | glcdPinData6
 *    +-------------------------------------------+
 *    | 6 | DB7  | Data Bit 7                     | glcdPinData7
 *    +-------------------------------------------+
 *    | 7 | BLK  | Backlight LED Cathode          | Connect to GND through resistor
 *    +-------------------------------------------+ (5v. Bright=50 Ohms, Med=100 Ohms, Low=1k Ohms)
 *    | 8 | BOE  | Output enable for button latch | H=Latch in Hi-Z, L=output latch to data pins
 *    +-------------------------------------------+ (Weak pull up if buttons not being read)
 *    | 9 | BIN  | L = Button pressed             | Weak pull up. 
 *    +-------------------------------------------+
 *    |10 | Vss  | Ground                         | Ground
 *    +-------------------------------------------+
 *
 */

#ifndef GLCD_PANEL_CONFIG_H
#define GLCD_PANEL_CONFIG_H

/*
 * define name for panel configuration
 */
#define glcd_ConfigName "Pure TheBug Display"

/*********************************************************/
/*  Configuration for LCD panel specific configuration   */
/*********************************************************/
#define DISPLAY_WIDTH 122
#define DISPLAY_HEIGHT 32

// panel controller chips
#define CHIP_WIDTH     61  // pixels per chip 
#define CHIP_HEIGHT    32  // pixels per chip 

// calculate number of chips & round up if width is not evenly divisable
#define glcd_CHIP_COUNT (((DISPLAY_WIDTH + CHIP_WIDTH - 1)  / CHIP_WIDTH) * ((DISPLAY_HEIGHT + CHIP_HEIGHT -1) / CHIP_HEIGHT))

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

/*
 * Pins can be assigned using arduino pin numbers 0-n
 * Pins on AVR devices can also be assigned using AVRPIN_Pb
 *    where P is port A-L and b is bit 0-7
 *     Example: port D bit 3 is AVRPIN_D3
 *
 * Pins on AVR devices can also be assigned using 0xPb for ports A to F
 *     Example: port D bit 3 is 0xD3
 */
#define NBR_CHIP_SELECT_PINS 0 // fill in with how many chip selects

#if defined(__AVR_ATmega2560__)
#define glcdPinData0    8
#define glcdPinData1    9
#define glcdPinData2   10
#define glcdPinData3   11
#define glcdPinData4    4
#define glcdPinData5    5
#define glcdPinData6    6
#define glcdPinData7    7

#define glcdPinRW      A4
#define glcdPinDI      A5    // Ao glcd pin

#define glcdPinE1      A0
#define glcdPinE2      A1

#else
// ESP32 Dev Kit

#define glcdPinData0   13
#define glcdPinData1   12
#define glcdPinData2   14
#define glcdPinData3   27
#define glcdPinData4   26
#define glcdPinData5   25
#define glcdPinData6   33
#define glcdPinData7   32

#define glcdPinRW      16
#define glcdPinDI      4    // Ao glcd pin

#define glcdPinE1      18
#define glcdPinE2      19

#endif


//#define glcdPinBL       3 // optional backlight control pin

/*********************************************************/
/*   Backlight Active Level Configuration                */
/*   Defines level on glcdPinBL pin to turn on backlight */
/*********************************************************/

#define glcd_BLactlevel HIGH

// defines for panel specific timing (times in nano seconds)
#define GLCD_tDDR    290    /* tACC6: Data Delay time (E high to valid read data)             */
#define GLCD_tAS      20    /* tAW6:  Address setup time (ctrl line changes to E high)        */
#define GLCD_tDSW    200    /* tDS6:  Data setup time (Write data lines setup to dropping E)  */
#define GLCD_tWH     450    /* tEW:   E hi level width (minimum E hi pulse width)             */ 
#define GLCD_tWL     450    /* E lo level width (minimum E lo pulse width)                    */


#include "device/sed1520_Device.h"
#endif //GLCD_PANEL_CONFIG_H
