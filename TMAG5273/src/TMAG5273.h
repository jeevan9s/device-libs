/**
 * @file        TMAG5273.hpp
 * @brief       Header file containing class definitions for TMAG5273 library.
 * @author      Jeevan Sanchez
 * @date        2026-05-03
 *
 * device-libs
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "registers.h"

class TMAG5273
{
public:
    TMAG5273() : _addr(0x35), _i2c(&Wire) {}
    TMAG5273(uint8_t addr, TwoWire *wire);

    bool init();

    /// @brief initialize the sensor
    /// @param addr I2C address of sensor (0x35 by default)
    /// @param port reference to I2C port
    /// @return true on successful initialization, false otherwise
    bool init(uint8_t addr, TwoWire &port);

    // data
    float getFluxX();
    float getFluxY();
    float getFluxZ();

    /// @brief obtain temperature values from sensor
    /// @return float temperature value in celsius
    float getTemp();

    /// @brief obtain flux values from sensor readings for all axes
    /// @param axes pointer to float array to store flux values in mT
    /// @return true on successful sensor read, false otherwise
    bool getAllFlux(float *axes);

    /// @brief set the averaging speed
    /// @param mode averaging mode speed; found on datasheet Table 8-3
    /// @return true if successful set, false otherwise
    bool setAveraging(uint8_t mode);

    /// @brief check device status for hardware erors
    /// @return the raw status byte; 0 means no errors.
    uint8_t getDeviceStatus();

private:
    uint8_t _addr;
    TwoWire *_i2c;
    float _range;

    // temperature constants from datasheets (section 5.6)
    const float TADC_T0 = 17508.0f;
    const float TSENSE_T0 = 25.0f;
    const float TADC_RES = 58.0f;

    const float B16_SCALE = 32768.0f; // 32,768 (2^15) is the 16-bit scaling value

    /// @brief reads one or more bytes from a specific register
    /// @param reg starting register address to read from
    /// @param buffer pointer to a byte array for stored data
    /// @param len number of bytes to read (defaults to 1)
    /// @return true if the I2C transaction was successful and requested number of bytes were received, false otherwise
    bool readRegister(uint8_t reg, uint8_t *buffer, uint8_t len = 1);

    /// @brief write a single byte of data into a register
    /// @param reg reigster address to write to
    /// @param data information to be written
    /// @return true if the write succeeds, false otherwise
    bool writeRegister(uint8_t reg, uint8_t data);

    /// @brief combine 8-bit data from msb and lsb registers
    /// @param msb data from msb register
    /// @param lsb data from lsb register
    /// @return combined 16-bit data
    int16_t combineBytes(uint8_t msb, uint8_t lsb);

    /// @brief convert raw 16-bit data to a milli-Tesla float value
    /// @param raw 16-bit data read from sensor
    /// @param range sensor range configured in init()
    /// @return milli-Tesla float value
    float rawTomT(int16_t raw, float range = 80.0f); // if range changes, change this to 40.0f
};
