/**
 * @file        i2c.hpp
 * @brief       I2C bus hardware abstraction
 * @author      Jeevan Sanchez
 * @date        2026-11-05
 */

#pragma once

#include <Wire.h>

/**
 * @brief Thin I2C bus wrapper around an Arduino TwoWire instance.
 *
 * This class provides basic transfers and common 8-bit register access
 * helpers. Addresses are 7-bit I2C addresses.
 */
class I2CBus {
    public:
        /**
         * @brief Creates a bus wrapper for an existing TwoWire instance.
         * @param wire Arduino I2C bus instance, such as Wire.
         */
        I2CBus(TwoWire& wire);

        /**
         * @brief Starts the bus and sets its clock frequency.
         * @param data_pin SDA pin.
         * @param clock_pin SCL pin.
         * @param frequency Clock frequency in hertz.
         * @return true if the bus starts successfully.
         */
        bool begin(uint8_t data_pin = 21, uint8_t clock_pin = 22, uint32_t frequency = 100000);

        /**
         * @brief Writes bytes directly to an I2C device.
         * @param address 7-bit device address.
         * @param data Bytes to write.
         * @param length Number of bytes to write.
         * @return true if the transfer succeeds and all bytes are written.
         */
        bool write(uint8_t address, uint8_t* data, size_t length);

        /**
         * @brief Reads bytes directly from an I2C device.
         * @param address 7-bit device address.
         * @param buffer Destination buffer.
         * @param length Number of bytes to read.
         * @return true if the requested bytes are received.
         */
        bool read(uint8_t address, uint8_t* buffer, size_t length);

        /**
         * @brief Writes one byte to an 8-bit device register.
         * @param address 7-bit device address.
         * @param reg Register address.
         * @param value Byte to write.
         * @return true if the transfer succeeds.
         */
        bool writeRegister(uint8_t address, uint8_t reg, uint8_t value);

        /**
         * @brief Writes a byte array to an 8-bit device register.
         * @param address 7-bit device address.
         * @param reg Register address.
         * @param value Bytes to write.
         * @param length Number of bytes to write.
         * @return true if the transfer succeeds and all bytes are written.
         */
        bool writeRegister(uint8_t address, uint8_t reg, uint8_t *value, size_t length);

        /**
         * @brief Writes a 16-bit value to a register, most-significant byte first.
         * @param address 7-bit device address.
         * @param reg Register address.
         * @param value 16-bit value to write.
         * @return true if the transfer succeeds.
         */
        bool writeRegister16(uint8_t address, uint8_t reg, uint16_t value);

        /**
         * @brief Reads bytes from an 8-bit register address.
         * @param address 7-bit device address.
         * @param reg Register address.
         * @param buffer Destination buffer.
         * @param length Number of bytes to read.
         * @return true if the requested bytes are received.
         */
        bool readRegister(uint8_t address, uint8_t reg, uint8_t* buffer, size_t length);

        /**
         * @brief Reads a 16-bit register value, most-significant byte first.
         * @param address 7-bit device address.
         * @param reg Register address.
         * @param buffer Destination for the value.
         * @return true if the register is read successfully.
         */
        bool readRegister(uint8_t address, uint8_t, uint16_t* buffer);

    private:
        TwoWire& _wire;
};