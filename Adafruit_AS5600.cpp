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
bool Adafruit_AS5600::begin(uint8_t i2c_addr, TwoWire* wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_addr, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  return true;
}

/*!
 * @brief Get the ZMCO count - number of times ZPOS and MPOS have been burned
 * @return Number of times ZPOS/MPOS have been permanently written (0-3)
 */
uint8_t Adafruit_AS5600::getZMCount() {
  Adafruit_BusIO_Register zmco_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_ZMCO, 1);

  uint8_t zmco_value = zmco_reg.read();
  return zmco_value & 0x03; // Only bits 1:0 are used
}

/*!
 * @brief Get the zero position (start position) - 12-bit value
 * @return Zero position value (0-4095)
 */
uint16_t Adafruit_AS5600::getZPosition() {
  Adafruit_BusIO_Register zpos_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_ZPOS_H, 2, MSBFIRST);

  uint16_t zpos_value = zpos_reg.read();
  return zpos_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Set the zero position (start position) - 12-bit value
 * @param position Zero position value (0-4095)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setZPosition(uint16_t position) {
  position &= 0x0FFF; // Ensure only 12 bits are used

  Adafruit_BusIO_Register zpos_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_ZPOS_H, 2, MSBFIRST);

  return zpos_reg.write(position);
}

/*!
 * @brief Get the maximum position (stop position) - 12-bit value
 * @return Maximum position value (0-4095)
 */
uint16_t Adafruit_AS5600::getMPosition() {
  Adafruit_BusIO_Register mpos_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_MPOS_H, 2, MSBFIRST);

  uint16_t mpos_value = mpos_reg.read();
  return mpos_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Set the maximum position (stop position) - 12-bit value
 * @param position Maximum position value (0-4095)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setMPosition(uint16_t position) {
  position &= 0x0FFF; // Ensure only 12 bits are used

  Adafruit_BusIO_Register mpos_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_MPOS_H, 2, MSBFIRST);

  return mpos_reg.write(position);
}

/*!
 * @brief Get the maximum angle range - 12-bit value
 * @return Maximum angle value (0-4095, representing 0-360 degrees)
 */
uint16_t Adafruit_AS5600::getMaxAngle() {
  Adafruit_BusIO_Register mang_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_MANG_H, 2, MSBFIRST);

  uint16_t mang_value = mang_reg.read();
  return mang_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Set the maximum angle range - 12-bit value
 * @param angle Maximum angle value (0-4095, representing 0-360 degrees)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setMaxAngle(uint16_t angle) {
  angle &= 0x0FFF; // Ensure only 12 bits are used

  Adafruit_BusIO_Register mang_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_MANG_H, 2, MSBFIRST);

  return mang_reg.write(angle);
}

/*!
 * @brief Get the raw angle reading - 12-bit value (unscaled/unmodified)
 * @return Raw angle value (0-4095)
 */
uint16_t Adafruit_AS5600::getRawAngle() {
  Adafruit_BusIO_Register rawangle_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_RAWANGLE_H, 2, MSBFIRST);

  uint16_t rawangle_value = rawangle_reg.read();
  return rawangle_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Get the scaled angle reading - 12-bit value
 * @return Angle value (0-4095, scaled according to ZPOS/MPOS/MANG settings)
 */
uint16_t Adafruit_AS5600::getAngle() {
  Adafruit_BusIO_Register angle_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_ANGLE_H, 2, MSBFIRST);

  uint16_t angle_value = angle_reg.read();
  return angle_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Check if AGC minimum gain overflow occurred (magnet too strong)
 * @return true if MH bit is set (magnet too strong), false otherwise
 */
bool Adafruit_AS5600::isAGCminGainOverflow() {
  Adafruit_BusIO_Register status_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_STATUS, 1);
  Adafruit_BusIO_RegisterBits mh_bit =
      Adafruit_BusIO_RegisterBits(&status_reg, 1, 3);

  return mh_bit.read();
}

/*!
 * @brief Check if AGC maximum gain overflow occurred (magnet too weak)
 * @return true if ML bit is set (magnet too weak), false otherwise
 */
bool Adafruit_AS5600::isAGCmaxGainOverflow() {
  Adafruit_BusIO_Register status_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_STATUS, 1);
  Adafruit_BusIO_RegisterBits ml_bit =
      Adafruit_BusIO_RegisterBits(&status_reg, 1, 4);

  return ml_bit.read();
}

/*!
 * @brief Check if magnet is detected
 * @return true if MD bit is set (magnet detected), false otherwise
 */
bool Adafruit_AS5600::isMagnetDetected() {
  Adafruit_BusIO_Register status_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_STATUS, 1);
  Adafruit_BusIO_RegisterBits md_bit =
      Adafruit_BusIO_RegisterBits(&status_reg, 1, 5);

  return md_bit.read();
}

/*!
 * @brief Get the AGC (Automatic Gain Control) value
 * @return AGC value (0-255 in 5V mode, 0-128 in 3.3V mode)
 */
uint8_t Adafruit_AS5600::getAGC() {
  Adafruit_BusIO_Register agc_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_AGC, 1);

  return agc_reg.read();
}

/*!
 * @brief Get the magnitude value from the CORDIC processor
 * @return Magnitude value (0-4095)
 */
uint16_t Adafruit_AS5600::getMagnitude() {
  Adafruit_BusIO_Register magnitude_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_MAGNITUDE_H, 2, MSBFIRST);

  uint16_t magnitude_value = magnitude_reg.read();
  return magnitude_value & 0x0FFF; // Only 12 bits are used
}

/*!
 * @brief Enable or disable watchdog timer
 * @param enable true to enable watchdog, false to disable
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::enableWatchdog(bool enable) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 2, MSBFIRST);
  Adafruit_BusIO_RegisterBits wd_bit =
      Adafruit_BusIO_RegisterBits(&conf_reg, 1, 13);

  return wd_bit.write(enable ? 1 : 0);
}

/*!
 * @brief Get watchdog timer status
 * @return true if watchdog is enabled, false otherwise
 */
bool Adafruit_AS5600::getWatchdog() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 2, MSBFIRST);
  Adafruit_BusIO_RegisterBits wd_bit =
      Adafruit_BusIO_RegisterBits(&conf_reg, 1, 13);

  return wd_bit.read();
}

/*!
 * @brief Set power mode
 * @param mode Power mode to set (AS5600_POWER_MODE_NOM, LPM1, LPM2, LPM3)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setPowerMode(as5600_power_mode_t mode) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits pm_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 0);

  return pm_bits.write((uint8_t)mode);
}

/*!
 * @brief Get current power mode
 * @return Current power mode setting
 */
as5600_power_mode_t Adafruit_AS5600::getPowerMode() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits pm_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 0);

  return (as5600_power_mode_t)pm_bits.read();
}

/*!
 * @brief Set hysteresis setting
 * @param hysteresis Hysteresis to set (AS5600_HYSTERESIS_OFF, 1LSB, 2LSB, 3LSB)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setHysteresis(as5600_hysteresis_t hysteresis) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits hyst_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 2);

  return hyst_bits.write((uint8_t)hysteresis);
}

/*!
 * @brief Get current hysteresis setting
 * @return Current hysteresis setting
 */
as5600_hysteresis_t Adafruit_AS5600::getHysteresis() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits hyst_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 2);

  return (as5600_hysteresis_t)hyst_bits.read();
}

/*!
 * @brief Set output stage configuration
 * @param output Output stage to set (ANALOG_FULL, ANALOG_REDUCED, DIGITAL_PWM,
 * RESERVED)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setOutputStage(as5600_output_stage_t output) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits outs_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 4);

  return outs_bits.write((uint8_t)output);
}

/*!
 * @brief Get current output stage configuration
 * @return Current output stage setting
 */
as5600_output_stage_t Adafruit_AS5600::getOutputStage() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits outs_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 4);

  return (as5600_output_stage_t)outs_bits.read();
}

/*!
 * @brief Set PWM frequency
 * @param freq PWM frequency to set (115Hz, 230Hz, 460Hz, 920Hz)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setPWMFreq(as5600_pwm_freq_t freq) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits pwmf_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 6);

  return pwmf_bits.write((uint8_t)freq);
}

/*!
 * @brief Get current PWM frequency setting
 * @return Current PWM frequency setting
 */
as5600_pwm_freq_t Adafruit_AS5600::getPWMFreq() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_L, 1);
  Adafruit_BusIO_RegisterBits pwmf_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 6);

  return (as5600_pwm_freq_t)pwmf_bits.read();
}

/*!
 * @brief Set slow filter setting
 * @param filter Slow filter to set (16x, 8x, 4x, 2x)
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setSlowFilter(as5600_slow_filter_t filter) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 1);
  Adafruit_BusIO_RegisterBits sf_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 0);

  return sf_bits.write((uint8_t)filter);
}

/*!
 * @brief Get current slow filter setting
 * @return Current slow filter setting
 */
as5600_slow_filter_t Adafruit_AS5600::getSlowFilter() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 1);
  Adafruit_BusIO_RegisterBits sf_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 2, 0);

  return (as5600_slow_filter_t)sf_bits.read();
}

/*!
 * @brief Set fast filter threshold
 * @param thresh Fast filter threshold to set
 * @return true if write was successful, false otherwise
 */
bool Adafruit_AS5600::setFastFilterThresh(as5600_fast_filter_thresh_t thresh) {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 1);
  Adafruit_BusIO_RegisterBits fth_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 3, 2);

  return fth_bits.write((uint8_t)thresh);
}

/*!
 * @brief Get current fast filter threshold setting
 * @return Current fast filter threshold setting
 */
as5600_fast_filter_thresh_t Adafruit_AS5600::getFastFilterThresh() {
  Adafruit_BusIO_Register conf_reg =
      Adafruit_BusIO_Register(i2c_dev, AS5600_REG_CONF_H, 1);
  Adafruit_BusIO_RegisterBits fth_bits =
      Adafruit_BusIO_RegisterBits(&conf_reg, 3, 2);

  return (as5600_fast_filter_thresh_t)fth_bits.read();
}