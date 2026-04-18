#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <Arduino.h> 
void I2C_init(void);
void I2C_start(void);
void I2C_write(uint8_t data);
void I2C_stop(void);

#endif