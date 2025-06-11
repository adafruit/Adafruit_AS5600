/*!
 * @file AS5600_basic.ino
 *
 * Basic example for the Adafruit AS5600 library
 *
 * Written by Limor Fried for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 */

#include <Adafruit_AS5600.h>

Adafruit_AS5600 as5600;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Adafruit AS5600 Basic Test");

  if (!as5600.begin()) {
    Serial.println("Could not find AS5600 sensor, check wiring!");
    while (1) delay(10);
  }

  Serial.println("AS5600 found!");
}

void loop() {
  // Basic test - we'll add actual sensor reading functions later
  Serial.println("AS5600 is connected");
  delay(1000);
}