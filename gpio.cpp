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

void gpio_setdirB(uint8_t dirData)
{
    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(IODIRB_REG);                // Select GPIOB
    Wire.write(dirData);                   // Write value
    Wire.endTransmission();
}

void gpio_setpuB(uint8_t puData)
{
    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(GPPUB_REG);                // Select GPIOB
    Wire.write(puData);                   // Write value
    Wire.endTransmission();
}

/// @brief Sets pin to pinval on GPIOB
/// @param pin 
/// @param pinval 
void gpio_writepinB(uint8_t pin, uint8_t pinval)
{
    static uint8_t lastValue = 0;
    if(pinval) {
        lastValue |= _BV(pin);
    } else {
        lastValue &= ~_BV(pin);
    }
    // Serial.print("gpio_writepinB: ");
    // Serial.println(lastValue, HEX);

    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(GPIOB_REG);                // Select GPIOB
    Wire.write(lastValue);                   // Write value
    Wire.endTransmission();
}

uint8_t porta_dir;

/// @brief Writes 8 bits to GPIOA
/// @param data 
void gpio_writebyteA(uint8_t data) {
    if(porta_dir != 0x00) {
        Serial.println("Invalid Write!");
    }


    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(GPIOA_REG);                // Select GPIOA
    Wire.write(data);                   // Write value
    Wire.endTransmission();
}



/// @brief Reads 8 bits from GPIOA
/// @return 
uint8_t gpio_readbyteA() {

    if(porta_dir != 0xff) {
        Serial.println("Invalid Read!");
    }

    // Serial.println("gpio_readbyteA");
    // Set MCP23017 pointer to GPIOA
    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(GPIOA_REG);
    Wire.endTransmission();
    // Read GPIOA
    // Serial.println("Before request");
    Wire.requestFrom(GPIOEXP_ADDR, 1);
	while ( Wire.available()<1 )
        Serial.println("Wire not available");
    uint8_t result = Wire.read();
    // Serial.println("After read");
    // Serial.println(result,HEX);
    return result;
}

/// @brief Read pin from GPIOA (Only used for Status pin)
/// @param pin 
/// @return 
uint8_t gpio_readpinA(uint8_t pin) {
    return (gpio_readbyteA() & _BV(pin));
}

void gpio_dirinA(uint8_t pullup)
{
    porta_dir = 0xFF;
    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(IODIRA_REG);                 // Select IODIRA
    Wire.write(0xFF);                       // Write value
    Wire.endTransmission();

    if(false) {
        Wire.beginTransmission(GPIOEXP_ADDR);
        Wire.write(GPPUA_REG);                // Select GPIOB
        Wire.write(0xff);                   // Write value
        Wire.endTransmission();
    }
}

void gpio_diroutA()
{
    porta_dir = 0x00;

    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(IODIRA_REG);                 // Select IODIRA
    Wire.write(0x00);                       // Write value
    Wire.endTransmission();
}

