#include "oled_gui.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C ///< Typically 0x3C for 128x64 I2C OLEDs

// Allocate display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static uint8_t fanFrame = 0;

// Internal function to draw a modular animated fan
void OLED_drawFan(int x, int y, int radius, uint8_t frame) {
    display.drawCircle(x, y, radius, SSD1306_WHITE);
    
    if (frame == 0 || frame == 2) {
        display.drawLine(x - radius + 2, y, x + radius - 2, y, SSD1306_WHITE);
        display.drawLine(x, y - radius + 2, x, y + radius - 2, SSD1306_WHITE);
    } else {
        // Diagonal blades
        int offset = (radius - 2) * 0.707; // sin(45) ~ 0.707
        display.drawLine(x - offset, y - offset, x + offset, y + offset, SSD1306_WHITE);
        display.drawLine(x - offset, y + offset, x + offset, y - offset, SSD1306_WHITE);
    }
}

void OLED_init(void) {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        // Failed to allocate or communicate
        return; 
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 28);
    display.print(F("SAGE BOOT..."));
    display.display();
    
    delay(1000);
}

void OLED_show(float temp, int rpm, int speed) {
    display.clearDisplay();

    // --- Top Section: Temperature ---
    display.setTextSize(2); // Slightly larger for temp to stand out
    display.setCursor(0, 0);
    display.print(F("T:"));
    display.print(temp, 1);
    display.print(F("C"));
    
    // Draw Separator Line
    display.drawLine(0, 18, 128, 18, SSD1306_WHITE);

    // --- Middle Section: RPM & Speed ---
    display.setTextSize(1);
    display.setCursor(0, 22);
    display.print(F("RPM: "));
    
    // Format RPM padding
    if(rpm < 100) display.print(F("0"));
    if(rpm < 10)  display.print(F("0"));
    display.print(rpm);

    display.setCursor(70, 22);
    display.print(F("Spd:0"));
    display.print(speed);
    
    display.drawLine(0, 34, 128, 34, SSD1306_WHITE);

    // --- Visual Elements Section ---
    
    // Horizontal Bar Graph for Speed
    display.setCursor(0, 40);
    display.print(F("PWR:"));
    
    int maxBarWidth = 60; // Leave room for fan
    int currentBarWidth = map(speed, 1, 8, 1, maxBarWidth);
    if(currentBarWidth < 0) currentBarWidth = 0;
    if(currentBarWidth > maxBarWidth) currentBarWidth = maxBarWidth;

    display.drawRect(26, 38, maxBarWidth + 2, 11, SSD1306_WHITE);
    display.fillRect(27, 39, currentBarWidth, 9, SSD1306_WHITE);

    // Animated Fan (Bottom Right)
    // Update frame (only spins if speed > 0)
    if(speed >= 1) {
       fanFrame = (fanFrame + 1) % 4;
    }
    
    OLED_drawFan(108, 48, 12, fanFrame);

    // Push buffer to SSD1306
    display.display();
}
