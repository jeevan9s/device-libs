/**
 * @file        INA219.hpp
 * @brief       Definition of hardware driver class for INA219 power monitor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 */

#pragma once

#include <Arduino.h>
#include "i2c.hpp"

/**
 * @brief Driver for the INA219 voltage, current, and power monitor.
 */
class INA219 {
    public:
        /**
         * @brief Creates an INA219 driver.
         * @param addr 7-bit I2C address.
         * @param i2c Shared I2C bus wrapper.
         */
        INA219(uint8_t addr, I2CBus& i2c);

        /**
         * @brief Resets and configures the monitor with default ADC settings
         *        and a 3.4 A / 0.1 ohm calibration.
         * @return true if configuration and calibration succeed.
         */
        bool begin();

        /**
         * @brief Sets the current and power scaling for the connected shunt.
         * @param max_exp_amps Expected maximum current in amperes.
         * @param shunt_ohms Shunt resistance in ohms.
         * @return true if the values are valid and the calibration write succeeds.
         */
        bool setCalibration(float max_exp_amps, float shunt_ohms);

        /**
         * @brief Reads and converts bus voltage, shunt current, and power.
         * @return true if all register reads succeed; false otherwise.
         */
        bool read();

        /** Bus voltage, including shunt voltage, in volts. Updated by @ref read. */
        float voltage_V;

        /** Current in milliamperes. Updated by @ref read. */
        float current_mA;

        /** Power in milliwatts. Updated by @ref read. */
        float power_mW;

    private:

        uint8_t _addr;
        I2CBus& _i2c;
        float _current_lsb = 0.0f;
        float _power_lsb = 0.0f;
};