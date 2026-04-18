#ifndef OLED_GUI_H
#define OLED_GUI_H

#include <Arduino.h>

void OLED_init(void);
void OLED_show(float temp, int rpm, int speed);

#endif
