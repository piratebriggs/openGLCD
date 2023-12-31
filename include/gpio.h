#include <Arduino.h>

#define I2C_ADDR      0x20  // I2C module address (see datasheet)
#define IODIRA_REG    0x00  // MCP23017 internal register IODIRA  (see datasheet)
#define IODIRB_REG    0x01  // MCP23017 internal register IODIRB  (see datasheet)
#define GPPUA_REG     0x0C  // MCP23017 internal register GPPUA  (see datasheet)
#define GPPUB_REG     0x0D  // MCP23017 internal register GPPUB  (see datasheet)
#define GPIOA_REG     0x12  // MCP23017 internal register GPIOA  (see datasheet)
#define GPIOB_REG     0x13  // MCP23017 internal register GPIOB  (see datasheet)
#define OLATA_REG     0x14  // MCP23017 internal register OLATA  (see datasheet)
#define OLATB_REG     0x15  // MCP23017 internal register OLATB  (see datasheet)

void gpio_writepinB(uint8_t pin, uint8_t pinval);
void gpio_setdirB(uint8_t dirData);
void gpio_setpuB(uint8_t puData);

uint8_t gpio_readpinA(uint8_t pin);

void gpio_writebyteA(uint8_t data);
uint8_t gpio_readbyteA();

void gpio_dirinA(uint8_t pullup);
void gpio_diroutA();

