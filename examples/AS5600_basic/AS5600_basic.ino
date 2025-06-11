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

  // Test getZMCount function
  uint8_t zmCount = as5600.getZMCount();
  Serial.print("ZM Count (burn count): ");
  Serial.println(zmCount);

  // Test getZPosition function
  uint16_t zPos = as5600.getZPosition();
  Serial.print("Z Position: ");
  Serial.println(zPos);

  // Test setZPosition function (XOR current value with 0xADA to change it)
  uint16_t testPos = zPos ^ 0xADA; // XOR with 0xADA to get different value
  testPos &= 0x0FFF;               // Keep within 12-bit range
  Serial.print("Setting Z Position to ");
  Serial.print(testPos);
  Serial.print(" (0x");
  Serial.print(testPos, HEX);
  Serial.print(")... ");
  if (as5600.setZPosition(testPos)) {
    Serial.println("Success");
    uint16_t newZPos = as5600.getZPosition();
    Serial.print("New Z Position: ");
    Serial.print(newZPos);
    Serial.print(" (0x");
    Serial.print(newZPos, HEX);
    Serial.println(")");
  } else {
    Serial.println("Failed");
  }

  // Test getMPosition function
  uint16_t mPos = as5600.getMPosition();
  Serial.print("M Position: ");
  Serial.println(mPos);

  // Test setMPosition function (XOR current value with 0xBEE)
  uint16_t testMPos = mPos ^ 0xBEE;
  testMPos &= 0x0FFF;
  Serial.print("Setting M Position to ");
  Serial.print(testMPos);
  Serial.print(" (0x");
  Serial.print(testMPos, HEX);
  Serial.print(")... ");
  if (as5600.setMPosition(testMPos)) {
    Serial.println("Success");
    uint16_t newMPos = as5600.getMPosition();
    Serial.print("New M Position: ");
    Serial.print(newMPos);
    Serial.print(" (0x");
    Serial.print(newMPos, HEX);
    Serial.println(")");
  } else {
    Serial.println("Failed");
  }

  // Test getMaxAngle function
  uint16_t maxAngle = as5600.getMaxAngle();
  Serial.print("Max Angle: ");
  Serial.println(maxAngle);

  // Test setMaxAngle function (XOR current value with 0xCAB)
  uint16_t testMaxAngle = maxAngle ^ 0xCAB;
  testMaxAngle &= 0x0FFF;
  Serial.print("Setting Max Angle to ");
  Serial.print(testMaxAngle);
  Serial.print(" (0x");
  Serial.print(testMaxAngle, HEX);
  Serial.print(")... ");
  if (as5600.setMaxAngle(testMaxAngle)) {
    Serial.println("Success");
    uint16_t newMaxAngle = as5600.getMaxAngle();
    Serial.print("New Max Angle: ");
    Serial.print(newMaxAngle);
    Serial.print(" (0x");
    Serial.print(newMaxAngle, HEX);
    Serial.println(")");
  } else {
    Serial.println("Failed");
  }

  // Test watchdog functions
  Serial.print("Enabling watchdog... ");
  if (as5600.enableWatchdog(true)) {
    Serial.println("Success");
    Serial.print("Watchdog status: ");
    Serial.println(as5600.getWatchdog() ? "ENABLED" : "DISABLED");
  } else {
    Serial.println("Failed");
  }

  Serial.print("Disabling watchdog... ");
  if (as5600.enableWatchdog(false)) {
    Serial.println("Success");
    Serial.print("Watchdog status: ");
    Serial.println(as5600.getWatchdog() ? "ENABLED" : "DISABLED");
  } else {
    Serial.println("Failed");
  }

  // Test power mode functions
  Serial.print(
      "Setting power mode to Normal (options: NOM=0, LPM1=1, LPM2=2, "
      "LPM3=3)... ");
  if (as5600.setPowerMode(AS5600_POWER_MODE_NOM)) {
    Serial.println("Success");
    as5600_power_mode_t mode = as5600.getPowerMode();
    Serial.print("Power mode: ");
    switch (mode) {
      case AS5600_POWER_MODE_NOM:
        Serial.println("Normal");
        break;
      case AS5600_POWER_MODE_LPM1:
        Serial.println("Low Power Mode 1");
        break;
      case AS5600_POWER_MODE_LPM2:
        Serial.println("Low Power Mode 2");
        break;
      case AS5600_POWER_MODE_LPM3:
        Serial.println("Low Power Mode 3");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Test hysteresis functions
  Serial.print(
      "Setting hysteresis to OFF (options: OFF=0, 1LSB=1, 2LSB=2, 3LSB=3)... ");
  if (as5600.setHysteresis(AS5600_HYSTERESIS_OFF)) {
    Serial.println("Success");
    as5600_hysteresis_t hysteresis = as5600.getHysteresis();
    Serial.print("Hysteresis: ");
    switch (hysteresis) {
      case AS5600_HYSTERESIS_OFF:
        Serial.println("OFF");
        break;
      case AS5600_HYSTERESIS_1LSB:
        Serial.println("1 LSB");
        break;
      case AS5600_HYSTERESIS_2LSB:
        Serial.println("2 LSB");
        break;
      case AS5600_HYSTERESIS_3LSB:
        Serial.println("3 LSB");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Test output stage functions
  Serial.print(
      "Setting output stage to Analog Full (options: ANALOG_FULL=0, "
      "ANALOG_REDUCED=1, DIGITAL_PWM=2, RESERVED=3)... ");
  if (as5600.setOutputStage(AS5600_OUTPUT_STAGE_ANALOG_FULL)) {
    Serial.println("Success");
    as5600_output_stage_t outputStage = as5600.getOutputStage();
    Serial.print("Output stage: ");
    switch (outputStage) {
      case AS5600_OUTPUT_STAGE_ANALOG_FULL:
        Serial.println("Analog Full (0% to 100%)");
        break;
      case AS5600_OUTPUT_STAGE_ANALOG_REDUCED:
        Serial.println("Analog Reduced (10% to 90%)");
        break;
      case AS5600_OUTPUT_STAGE_DIGITAL_PWM:
        Serial.println("Digital PWM");
        break;
      case AS5600_OUTPUT_STAGE_RESERVED:
        Serial.println("Reserved");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Test PWM frequency functions
  Serial.print(
      "Setting PWM frequency to 115Hz (options: 115HZ=0, 230HZ=1, 460HZ=2, "
      "920HZ=3)... ");
  if (as5600.setPWMFreq(AS5600_PWM_FREQ_115HZ)) {
    Serial.println("Success");
    as5600_pwm_freq_t pwmFreq = as5600.getPWMFreq();
    Serial.print("PWM frequency: ");
    switch (pwmFreq) {
      case AS5600_PWM_FREQ_115HZ:
        Serial.println("115 Hz");
        break;
      case AS5600_PWM_FREQ_230HZ:
        Serial.println("230 Hz");
        break;
      case AS5600_PWM_FREQ_460HZ:
        Serial.println("460 Hz");
        break;
      case AS5600_PWM_FREQ_920HZ:
        Serial.println("920 Hz");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Test slow filter functions
  Serial.print(
      "Setting slow filter to 16x (options: 16X=0, 8X=1, 4X=2, 2X=3)... ");
  if (as5600.setSlowFilter(AS5600_SLOW_FILTER_16X)) {
    Serial.println("Success");
    as5600_slow_filter_t slowFilter = as5600.getSlowFilter();
    Serial.print("Slow filter: ");
    switch (slowFilter) {
      case AS5600_SLOW_FILTER_16X:
        Serial.println("16x");
        break;
      case AS5600_SLOW_FILTER_8X:
        Serial.println("8x");
        break;
      case AS5600_SLOW_FILTER_4X:
        Serial.println("4x");
        break;
      case AS5600_SLOW_FILTER_2X:
        Serial.println("2x");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Test fast filter threshold functions
  Serial.print(
      "Setting fast filter threshold to Slow Only (options: SLOW_ONLY=0, "
      "6LSB=1, 7LSB=2, 9LSB=3, 18LSB=4, 21LSB=5, 24LSB=6, 10LSB=7)... ");
  if (as5600.setFastFilterThresh(AS5600_FAST_FILTER_THRESH_SLOW_ONLY)) {
    Serial.println("Success");
    as5600_fast_filter_thresh_t fastThresh = as5600.getFastFilterThresh();
    Serial.print("Fast filter threshold: ");
    switch (fastThresh) {
      case AS5600_FAST_FILTER_THRESH_SLOW_ONLY:
        Serial.println("Slow filter only");
        break;
      case AS5600_FAST_FILTER_THRESH_6LSB:
        Serial.println("6 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_7LSB:
        Serial.println("7 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_9LSB:
        Serial.println("9 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_18LSB:
        Serial.println("18 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_21LSB:
        Serial.println("21 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_24LSB:
        Serial.println("24 LSB");
        break;
      case AS5600_FAST_FILTER_THRESH_10LSB:
        Serial.println("10 LSB");
        break;
    }
  } else {
    Serial.println("Failed");
  }

  // Reset position settings to defaults
  as5600.setZPosition(0);
  as5600.setMPosition(4095);
  as5600.setMaxAngle(4095);
}

void loop() {
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
  if (as5600.isMagnetDetected()) {
    Serial.print(" | Magnet: YES");
  }
  if (as5600.isAGCminGainOverflow()) {
    Serial.print(" | MH: magnet too strong");
  }
  if (as5600.isAGCmaxGainOverflow()) {
    Serial.print(" | ML: magnet too weak");
  }

  // Get AGC and Magnitude values
  uint8_t agc = as5600.getAGC();
  uint16_t magnitude = as5600.getMagnitude();
  Serial.print(" | AGC: ");
  Serial.print(agc);
  Serial.print(" | Mag: ");
  Serial.print(magnitude);

  Serial.println();
  delay(250);
}