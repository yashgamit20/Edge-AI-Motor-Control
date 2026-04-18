#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial2.begin(4800, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 STARTED");
}

void loop() {

  if (Serial2.available()) {

    String data = Serial2.readStringUntil('\n');
    data.trim();

    float temp = data.toFloat();

    // smoothing
    static float filteredTemp = 0;
    filteredTemp = (0.7 * filteredTemp) + (0.3 * temp);

    // mapping (Edge AI Polynomial Regression logic)
    // Speed = 0.0005*T^3 - 0.1339*T^2 + 7.5310*T - 115.6969
    float t = filteredTemp;
    float speed_f = (0.0005 * t * t * t) - (0.1339 * t * t) + (7.5310 * t) - 115.6969;
    
    int speed = (int)(speed_f + 0.5); // Round to nearest integer

    if (speed < 1) speed = 1;
    if (speed > 8) speed = 8;

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" -> Speed: ");
    Serial.println(speed);

    // Give Arduino's SoftwareSerial time to finish transmitting and switch to receive mode
    delay(50);

    // send speed
    Serial2.print(speed);
    Serial2.print('\n');
  }
}
