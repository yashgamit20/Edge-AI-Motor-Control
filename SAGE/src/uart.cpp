#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdio.h>

SoftwareSerial mySerial(6, 5); // RX, TX

void UART_init(void) {
    mySerial.begin(4800);
}

void UART_sendchar(char c) {
    mySerial.write(c);
}

void UART_sendstring(const char *str) {
    while (*str) mySerial.write(*str++);
}

void UART_sendnumber(uint8_t num) {
    char buf[4];
    sprintf(buf, "%d", num);
    UART_sendstring(buf);
}