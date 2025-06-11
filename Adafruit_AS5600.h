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

#include "Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

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
 * @brief Main AS5600 class for 12-bit contactless position sensor
 */
class Adafruit_AS5600 {
public:
  Adafruit_AS5600();
  ~Adafruit_AS5600();

  bool begin(uint8_t i2c_addr = AS5600_DEFAULT_ADDR, TwoWire *wire = &Wire);

private:
  Adafruit_I2CDevice *i2c_dev;
};

#endif