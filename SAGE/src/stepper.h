#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

void Stepper_init(void);
void Stepper_setSpeed(int delayVal);
void Stepper_run(void);

#endif