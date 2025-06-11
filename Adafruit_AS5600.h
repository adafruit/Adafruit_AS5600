/*!
 * @file Adafruit_AS5600.h
 *
 * This is the documentation for Adafruit's AS5600 library
 *
 * @section license License
 *
 * Written by Limor Fried for Adafruit Industries.
 *
 * MIT license, all text above must be included in any redistribution
 */

#ifndef _ADAFRUIT_AS5600_H
#define _ADAFRUIT_AS5600_H

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#include "Arduino.h"

#define AS5600_DEFAULT_ADDR 0x36

#define AS5600_REG_ZMCO 0x00
#define AS5600_REG_ZPOS_H 0x01
#define AS5600_REG_ZPOS_L 0x02
#define AS5600_REG_MPOS_H 0x03
#define AS5600_REG_MPOS_L 0x04
#define AS5600_REG_MANG_H 0x05
#define AS5600_REG_MANG_L 0x06
#define AS5600_REG_CONF_H 0x07
#define AS5600_REG_CONF_L 0x08
#define AS5600_REG_STATUS 0x0B
#define AS5600_REG_RAWANGLE_H 0x0C
#define AS5600_REG_RAWANGLE_L 0x0D
#define AS5600_REG_ANGLE_H 0x0E
#define AS5600_REG_ANGLE_L 0x0F
#define AS5600_REG_AGC 0x1A
#define AS5600_REG_MAGNITUDE_H 0x1B
#define AS5600_REG_MAGNITUDE_L 0x1C
#define AS5600_REG_BURN 0xFF

/*!
 * @brief Power mode settings for AS5600
 */
typedef enum {
  AS5600_POWER_MODE_NOM = 0x00,  ///< Normal mode (default)
  AS5600_POWER_MODE_LPM1 = 0x01, ///< Low power mode 1
  AS5600_POWER_MODE_LPM2 = 0x02, ///< Low power mode 2
  AS5600_POWER_MODE_LPM3 = 0x03  ///< Low power mode 3
} as5600_power_mode_t;

/*!
 * @brief Hysteresis settings for AS5600
 */
typedef enum {
  AS5600_HYSTERESIS_OFF = 0x00,  ///< Hysteresis off (default)
  AS5600_HYSTERESIS_1LSB = 0x01, ///< 1 LSB hysteresis
  AS5600_HYSTERESIS_2LSB = 0x02, ///< 2 LSB hysteresis
  AS5600_HYSTERESIS_3LSB = 0x03  ///< 3 LSB hysteresis
} as5600_hysteresis_t;

/*!
 * @brief Output stage settings for AS5600
 */
typedef enum {
  AS5600_OUTPUT_STAGE_ANALOG_FULL = 0x00,    ///< Analog (0% to 100%)
  AS5600_OUTPUT_STAGE_ANALOG_REDUCED = 0x01, ///< Analog (10% to 90%)
  AS5600_OUTPUT_STAGE_DIGITAL_PWM = 0x02,    ///< Digital PWM
  AS5600_OUTPUT_STAGE_RESERVED = 0x03        ///< Reserved
} as5600_output_stage_t;

/*!
 * @brief PWM frequency settings for AS5600
 */
typedef enum {
  AS5600_PWM_FREQ_115HZ = 0x00, ///< 115 Hz (default)
  AS5600_PWM_FREQ_230HZ = 0x01, ///< 230 Hz
  AS5600_PWM_FREQ_460HZ = 0x02, ///< 460 Hz
  AS5600_PWM_FREQ_920HZ = 0x03  ///< 920 Hz
} as5600_pwm_freq_t;

/*!
 * @brief Slow filter settings for AS5600
 */
typedef enum {
  AS5600_SLOW_FILTER_16X = 0x00, ///< 16x (default)
  AS5600_SLOW_FILTER_8X = 0x01,  ///< 8x
  AS5600_SLOW_FILTER_4X = 0x02,  ///< 4x
  AS5600_SLOW_FILTER_2X = 0x03   ///< 2x
} as5600_slow_filter_t;

/*!
 * @brief Fast filter threshold settings for AS5600
 */
typedef enum {
  AS5600_FAST_FILTER_THRESH_SLOW_ONLY = 0x00, ///< Slow filter only (default)
  AS5600_FAST_FILTER_THRESH_6LSB = 0x01,      ///< 6 LSB
  AS5600_FAST_FILTER_THRESH_7LSB = 0x02,      ///< 7 LSB
  AS5600_FAST_FILTER_THRESH_9LSB = 0x03,      ///< 9 LSB
  AS5600_FAST_FILTER_THRESH_18LSB = 0x04,     ///< 18 LSB
  AS5600_FAST_FILTER_THRESH_21LSB = 0x05,     ///< 21 LSB
  AS5600_FAST_FILTER_THRESH_24LSB = 0x06,     ///< 24 LSB
  AS5600_FAST_FILTER_THRESH_10LSB = 0x07      ///< 10 LSB
} as5600_fast_filter_thresh_t;

/*!
 * @brief Main AS5600 class for 12-bit contactless position sensor
 */
class Adafruit_AS5600 {
 public:
  Adafruit_AS5600();
  ~Adafruit_AS5600();

  bool begin(uint8_t i2c_addr = AS5600_DEFAULT_ADDR, TwoWire* wire = &Wire);

  uint8_t getZMCount();
  uint16_t getZPosition();
  bool setZPosition(uint16_t position);
  uint16_t getMPosition();
  bool setMPosition(uint16_t position);
  uint16_t getMaxAngle();
  bool setMaxAngle(uint16_t angle);
  uint16_t getRawAngle();
  uint16_t getAngle();
  bool isAGCminGainOverflow();
  bool isAGCmaxGainOverflow();
  bool isMagnetDetected();
  uint8_t getAGC();
  uint16_t getMagnitude();
  bool enableWatchdog(bool enable);
  bool getWatchdog();
  bool setPowerMode(as5600_power_mode_t mode);
  as5600_power_mode_t getPowerMode();
  bool setHysteresis(as5600_hysteresis_t hysteresis);
  as5600_hysteresis_t getHysteresis();
  bool setOutputStage(as5600_output_stage_t output);
  as5600_output_stage_t getOutputStage();
  bool setPWMFreq(as5600_pwm_freq_t freq);
  as5600_pwm_freq_t getPWMFreq();
  bool setSlowFilter(as5600_slow_filter_t filter);
  as5600_slow_filter_t getSlowFilter();
  bool setFastFilterThresh(as5600_fast_filter_thresh_t thresh);
  as5600_fast_filter_thresh_t getFastFilterThresh();

 private:
  Adafruit_I2CDevice* i2c_dev;
};

#endif