#include <Arduino.h>
#include "Wire.h"                         // Needed for I2C bus
#include "include\glcd_io_i2c.h"                         // Needed for I2C bus

static uint8_t porta_dir;
static uint8_t portb_data = 0;

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
    if(pinval) {
        portb_data |= _BV(pin);
    } else {
        portb_data &= ~_BV(pin);
    }
    // Serial.print("gpio_writepinB: ");
    // Serial.println(lastValue, HEX);

    Wire.beginTransmission(GPIOEXP_ADDR);
    Wire.write(GPIOB_REG);                // Select GPIOB
    Wire.write(portb_data);                   // Write value
    Wire.endTransmission();
}


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

    if(pullup) {
        Wire.beginTransmission(GPIOEXP_ADDR);
        Wire.write(GPPUA_REG);                // Select GPIOB
        Wire.write(0xff);                   // Write value
        Wire.endTransmission();
    } else {
        Wire.beginTransmission(GPIOEXP_ADDR);
        Wire.write(GPPUA_REG);                // Select GPIOB
        Wire.write(0x00);                   // Write value
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

void glcdio_i2c_init()
{
    // Wire.begin();
}
