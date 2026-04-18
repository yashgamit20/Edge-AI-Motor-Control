#include "stepper.h"

static int IN1 = 9;
static int IN2 = 10;
static int IN3 = 11;
static int IN4 = 12;

static int stepIndex = 0;
static int stepDelay = 3;  // speed control (ms)
static unsigned long lastStepTime = 0;

// Half-step sequence (SMOOTH)
void stepMotor(int step) {
    switch(step) {
        case 0: digitalWrite(IN1,1); digitalWrite(IN2,0); digitalWrite(IN3,0); digitalWrite(IN4,0); break;
        case 1: digitalWrite(IN1,1); digitalWrite(IN2,1); digitalWrite(IN3,0); digitalWrite(IN4,0); break;
        case 2: digitalWrite(IN1,0); digitalWrite(IN2,1); digitalWrite(IN3,0); digitalWrite(IN4,0); break;
        case 3: digitalWrite(IN1,0); digitalWrite(IN2,1); digitalWrite(IN3,1); digitalWrite(IN4,0); break;
        case 4: digitalWrite(IN1,0); digitalWrite(IN2,0); digitalWrite(IN3,1); digitalWrite(IN4,0); break;
        case 5: digitalWrite(IN1,0); digitalWrite(IN2,0); digitalWrite(IN3,1); digitalWrite(IN4,1); break;
        case 6: digitalWrite(IN1,0); digitalWrite(IN2,0); digitalWrite(IN3,0); digitalWrite(IN4,1); break;
        case 7: digitalWrite(IN1,1); digitalWrite(IN2,0); digitalWrite(IN3,0); digitalWrite(IN4,1); break;
    }
}

void Stepper_init(void) {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void Stepper_setSpeed(int delayVal) {
    stepDelay = delayVal;
}

void Stepper_run(void) {
    unsigned long now = millis();

    if (now - lastStepTime >= stepDelay) {
        lastStepTime = now;

        stepMotor(stepIndex);
        stepIndex = (stepIndex + 1) % 8;  // 8-step sequence
    }
}