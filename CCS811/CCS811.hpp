/**
 * @file        CCS811.hpp
 * @brief       Definition of hardware driver class for I2C CCSB11 VOC/CO2 sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 *
 */

#pragma once

#include <Arduino.h>
#include "i2c.hpp"

class CCS811
{
public:
    CCS811(I2CBus& i2c, uint8_t address = 0x5A);

    /// @brief  confirm hardware ID, check if app fw is loaded, put app into start, set measuring mode to constant power mode
    /// @return true on successful initialization
    bool begin();

    /// @brief probe the STATUS register (0x00) for the DATA_READY bit
    /// @return true if a new data sample is ready
    bool available();

    /// @brief set compensation parameters with humidity and temp
    /// @param humidity percentage describing humidity
    /// @param temp measured in C
    bool compensate(float humidity, float temp);

    /// @brief burst read and combine bytes from MSB/LSB for each data field in ALG_RESULT_DATA reg
    void read();

    uint16_t eco2 = 0; // ppm
    uint16_t tvoc = 0; // ppb

private:
    uint8_t _addr;
    I2CBus& _i2c;
};
