/*
 *  delay_cycles_esp32.h
 *
 * Provides accurate cycle delays for a given number of i/o clocks.
 * This version is for the esp32 and is part of the openGLCD library.
 */


#ifndef _DELAY_CYCLES_ESP32_H_
#define _DELAY_CYCLES_ESP32_H_

#include <inttypes.h>

/*
 *
 *  _delay_cycles(uint32 _IOticks)
 *
 *  Perform an accurate delay of a given number of i/o cycles.
 *
 */

static __inline__ void
_delay_cycles(uint32_t _IOticks)
{
// Sleeps for the specified number of clock cycles
// Source: https://www.reddit.com/r/esp32/comments/i07em9/comment/fzowgv6/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
	uint32_t i = _IOticks >> 3;
    i += _IOticks >> 7;
	while (--i);
}

#endif /* _DELAY_CYCLES_ESP32 */
