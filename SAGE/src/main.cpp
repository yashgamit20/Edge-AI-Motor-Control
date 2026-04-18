#include <Arduino.h>
#include <stdlib.h>
#include "uart.h"
#include "stepper.h"
#include "adc.h"
#include "oled_gui.h"

extern SoftwareSerial mySerial;   // RX=6, TX=5

#define LM35_CHANNEL 0

unsigned long lastReadTime = 0;
uint16_t prev_adc = 0;

float current_temp = 0.0;
int current_rpm = 0;
int current_speed = 0;

// UART buffer
char rx_buffer[10];
uint8_t rx_index = 0;

void setup() {
    UART_init();
    Stepper_init();
    ADC_init();
    OLED_init();

    delay(1000);

    UART_sendstring("Temp\r\n");
}

void loop() {

    Stepper_run();

    // 🔹 Read temperature
    if (millis() - lastReadTime > 2000) {

        lastReadTime = millis();

        uint32_t sum = 0;
        for (int i = 0; i < 20; i++) {
            sum += ADC_read(LM35_CHANNEL);
            delay(2);
        }

        uint16_t adcValue = sum / 20;

        adcValue = (prev_adc + adcValue) / 2;
        prev_adc = adcValue;

        uint16_t temp_x10 = (adcValue * 5000UL) / 1023;
        uint16_t temp_int = temp_x10 / 10;
        uint16_t temp_dec = temp_x10 % 10;
        
        current_temp = temp_int + (temp_dec / 10.0);

        // 🔹 Send temp to ESP32
        UART_sendnumber(temp_int);
        UART_sendchar('.');
        UART_sendnumber(temp_dec);
        UART_sendstring("\r\n");
        
        OLED_show(current_temp, current_rpm, current_speed);
    }

    // 🔹 Receive speed from ESP32
    if (mySerial.available()) {
        char firstChar = mySerial.peek();
        
        int speed = mySerial.parseInt();

        // Clear trailing newlines or extra chars
        while(mySerial.available() > 0) {
            char junk = mySerial.read();
            if (junk == '\n') break;
        }

        if (speed >= 1 && speed <= 8) {
            current_speed = speed;
            Stepper_setSpeed(speed);
            
            // 🔹 RPM
            current_rpm = 60000 / (4096 * speed);
            
            OLED_show(current_temp, current_rpm, current_speed);
        } else {
            // Unhandled gibberish fallback
        }
    }
}