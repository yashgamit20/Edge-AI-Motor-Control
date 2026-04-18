#include <Arduino.h>
#include "i2c.h"

#define SCL_CLOCK 100000L

void I2C_init(void){
   TWSR = 0x00;
   TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;
}

void I2C_start(void){
   TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
   while(!(TWCR & (1<<TWINT)));
}

void I2C_write(uint8_t data){
   TWDR = data;
   TWCR = (1<<TWINT) | (1<<TWEN);
   while (!(TWCR & (1<<TWINT)));
}

void I2C_stop(void){
   TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}