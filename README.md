# Adafruit AS5600 Library [![Build Status](https://github.com/adafruit/Adafruit_AS5600/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_AS5600/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_AS5600/html/index.html)

Arduino library for the AS5600 12-bit contactless magnetic rotary position sensor.

## About the AS5600

The AS5600 is a contactless magnetic rotary position sensor for accurate angular measurement over a full 360-degree rotation. It features:

- 12-bit resolution (4096 positions per revolution)
- I2C interface (address 0x36)
- Analog output (ratiometric to VDD)
- PWM output option
- Magnetic field strength detection
- Programmable zero position and angular range
- Low power modes
- Temperature range: -40°C to 125°C

## Installation

Download and install the library using the Arduino Library Manager or by downloading the latest release from GitHub.

### Dependencies

This library requires:
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)

## Hardware

The AS5600 requires a diametrically magnetized magnet positioned above the sensor. The magnet should be centered over the chip with an air gap of 0.5-3mm.

## License

MIT License. See LICENSE file for details.

## Contributing

Contributions are welcome! Please read the contributing guidelines and submit pull requests to the main repository.