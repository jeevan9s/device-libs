/**
 * @file        CCS811.hpp
 * @brief       Driver for the CCS811 indoor air quality sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 *
 */

#pragma once

#include <Arduino.h>
#include "i2c.hpp"

/**
 * @brief Reads equivalent CO2 and total volatile organic compound values
 *        from a CCS811 sensor over I2C.
 */
class CCS811
{
public:
    /**
     * @brief Creates a CCS811 driver.
     * @param i2c Shared I2C bus wrapper.
     * @param address 7-bit I2C address (default 0x5A).
     */
    CCS811(I2CBus& i2c, uint8_t address = 0x5A);

    /**
     * @brief Checks the hardware ID and application status, starts the
     *        application, and selects the driver's measurement mode.
     * @return true if all initialization transactions succeed.
     */
    bool begin();

    /**
     * @brief Checks the STATUS register's DATA_READY bit.
     * @return true if a new sample is ready; false if not ready or the read fails.
     */
    bool available();

    /**
     * @brief Writes environmental compensation values to the sensor.
     * @param humidity Relative humidity in percent (0-100).
     * @param temp Temperature in degrees Celsius (-25 to 102.998).
     * @return true if the values are in range and the write succeeds.
     */
    bool compensate(float humidity, float temp);

    /**
     * @brief Reads the algorithm result and updates @ref eco2 and @ref tvoc.
     *
     * If the I2C read fails, the previously stored values are unchanged.
     */
    void read();

    /** Equivalent CO2 concentration in parts per million (ppm). */
    uint16_t eco2 = 0;

    /** Total volatile organic compounds in parts per billion (ppb). */
    uint16_t tvoc = 0;

private:
    uint8_t _addr;
    I2CBus& _i2c;
};
