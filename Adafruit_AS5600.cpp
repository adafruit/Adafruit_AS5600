/*!
 * @file Adafruit_AS5600.cpp
 *
 * @mainpage Adafruit AS5600 12-bit contactless position sensor library
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's AS5600 driver for the
 * Arduino platform.  It is designed specifically to work with the
 * Adafruit AS5600 breakout:
 *
 * These sensors use I2C to communicate, 2 pins are required to interface.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing products
 * from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution
 */

#include "Adafruit_AS5600.h"

/*!
 * @brief Instantiates a new AS5600 class
 */
Adafruit_AS5600::Adafruit_AS5600() {}

/*!
 * @brief Destructor for AS5600 class
 */
Adafruit_AS5600::~Adafruit_AS5600() {
  if (i2c_dev) {
    delete i2c_dev;
  }
}

/*!
 * @brief Initializes the sensor
 * @param i2c_addr The I2C address to use (default AS5600_DEFAULT_ADDR)
 * @param wire The Wire object to use for I2C communication
 * @return true if initialization was successful, false otherwise
 */
bool Adafruit_AS5600::begin(uint8_t i2c_addr, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_addr, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}