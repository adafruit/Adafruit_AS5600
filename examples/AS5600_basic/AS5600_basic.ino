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
  while (!Serial)
    delay(10);

  Serial.println("Adafruit AS5600 Basic Test");

  if (!as5600.begin()) {
    Serial.println("Could not find AS5600 sensor, check wiring!");
    while (1)
      delay(10);
  }

  Serial.println("AS5600 found!");


  as5600.enableWatchdog(false);
  // Normal (high) power mode
  as5600.setPowerMode(AS5600_POWER_MODE_NOM);
  // No Hysteresis
  as5600.setHysteresis(AS5600_HYSTERESIS_OFF);

  // analog output
  as5600.setOutputStage(AS5600_OUTPUT_STAGE_ANALOG_FULL);

  // OR can do pwm!
  // as5600.setOutputStage(AS5600_OUTPUT_STAGE_DIGITAL_PWM);
  // as5600.setPWMFreq(AS5600_PWM_FREQ_920HZ);

  // setup filters
  as5600.setSlowFilter(AS5600_SLOW_FILTER_16X);
  as5600.setFastFilterThresh(AS5600_FAST_FILTER_THRESH_SLOW_ONLY);

  // Reset position settings to defaults
  as5600.setZPosition(0);
  as5600.setMPosition(4095);
  as5600.setMaxAngle(4095);

  Serial.println("Waiting for magnet detection...");
}

void loop() {
  if (! as5600.isMagnetDetected()) {
    return;
  }

  // Continuously read and display angle values
  uint16_t rawAngle = as5600.getRawAngle();
  uint16_t angle = as5600.getAngle();

  Serial.print("Raw: ");
  Serial.print(rawAngle);
  Serial.print(" (0x");
  Serial.print(rawAngle, HEX);
  Serial.print(") | Scaled: ");
  Serial.print(angle);
  Serial.print(" (0x");
  Serial.print(angle, HEX);
  Serial.print(")");

  // Check status conditions
  if (as5600.isAGCminGainOverflow()) {
    Serial.print(" | MH: magnet too strong");
  }
  if (as5600.isAGCmaxGainOverflow()) {
    Serial.print(" | ML: magnet too weak");
  }

  Serial.println();
  delay(50);
}