#ifndef UART_H
#define UART_H
#include <SoftwareSerial.h>
extern SoftwareSerial mySerial;
#include <Arduino.h>   // ✅ recommended

void UART_init(void);
void UART_sendchar(char c);
void UART_sendstring(const char *str);
void UART_sendnumber(uint8_t num);

#endif