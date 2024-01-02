#ifndef GLCD_IO_I2C_H
#define GLCD_IO_I2C_H

#include <Arduino.h>
#include "Wire.h"                         // Needed for I2C bus

#define GPIOEXP_ADDR  0x20  // I2C module address (see datasheet)
#define IODIRA_REG    0x00  // MCP23017 internal register IODIRA  (see datasheet)
#define IODIRB_REG    0x01  // MCP23017 internal register IODIRB  (see datasheet)
#define GPPUA_REG     0x0C  // MCP23017 internal register GPPUA  (see datasheet)
#define GPPUB_REG     0x0D  // MCP23017 internal register GPPUB  (see datasheet)
#define GPIOA_REG     0x12  // MCP23017 internal register GPIOA  (see datasheet)
#define GPIOB_REG     0x13  // MCP23017 internal register GPIOB  (see datasheet)
#define OLATA_REG     0x14  // MCP23017 internal register OLATA  (see datasheet)
#define OLATB_REG     0x15  // MCP23017 internal register OLATB  (see datasheet)


/// @brief Sets pin to pinval on GPIOB
/// @param pin 
/// @param pinval 
void gpio_writepinB(uint8_t pin, uint8_t pinval);

void gpio_setdirB(uint8_t dirData);

void gpio_setpuB(uint8_t puData);

/// @brief Writes 8 bits to GPIOA
/// @param data 
void gpio_writebyteA(uint8_t data);

/// @brief Reads 8 bits from GPIOA
/// @return 
uint8_t gpio_readbyteA();

/// @brief Read pin from GPIOA (Only used for Status pin)
/// @param pin 
/// @return 
uint8_t gpio_readpinA(uint8_t pin);
void gpio_dirinA(uint8_t pullup);
void gpio_diroutA();
void glcdio_i2c_init();

#define glcdio_ReadPin(pin)				gpio_readpinA(pin)
#define glcdio_WritePin(pin, pinval) 	gpio_writepinB(pin, pinval)
#define glcdio_PinMode(pin, mode)
#define glcdio_WriteByte(data)			gpio_writebyteA(data)
#define glcdio_ReadByte()				gpio_readbyteA()

#define glcdio_DataDirIn(_ENpullups)	gpio_dirinA(_ENpullups)
#define glcdio_DataDirOut()				gpio_diroutA()

#endif //GLCD_IO_I2C_H
