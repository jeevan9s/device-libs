/**
 * @file        HDC1080.hpp
 * @brief       Definition of hardware driver class for HDC1080 temperature and humidity sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 */

#pragma once

#include <Arduino.h>
#include "i2c.hpp"

/**
 * @brief Driver for the HDC1080 temperature and humidity sensor.
 */
class HDC1080 {
    public:
        /**
         * @brief Creates an HDC1080 driver.
         * @param i2c Shared I2C bus wrapper.
         * @param addr 7-bit I2C address (default 0x40).
         */
        HDC1080(I2CBus& i2c, uint8_t addr = 0x40);

        /**
         * @brief Verifies the device IDs and configures sequential measurements.
         * @return true if identification and configuration succeed.
         */
        bool begin();

        /**
         * @brief Reads a temperature and humidity sample into the public fields.
         *
         * The fields are unchanged if the I2C transfer fails.
         */
        void read();

        /**
         * @brief Converts a raw temperature register value to degrees Celsius.
         * @param raw 16-bit temperature reading.
         * @return Temperature in degrees Celsius.
         */
        float tempConvert(uint16_t raw) const;

        /**
         * @brief Converts a raw humidity register value to relative humidity.
         * @param raw 16-bit humidity reading.
         * @return Relative humidity in percent.
         */
        float humidityConvert(uint16_t raw) const;

        /** Temperature in degrees Celsius. Updated by @ref read. */
        float temp;

        /** Relative humidity in percent. Updated by @ref read. */
        float humidity;

    private:
        uint8_t _addr;
        I2CBus& _i2c;
};