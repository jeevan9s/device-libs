
/**
 * @file        LSM6DSM.hpp
 * @brief       Header containing class defs for LSM6DSM IMU library.
 * @author      Jeevan Sanchez
 * @date        2026-07-08
 *
 *
 * device-libs/LSM6DSM
 */

#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "registers.h"

class LSM6DSM
{
public:
    LSM6DSM() : _addr(0x6A), _i2c(&Wire) {}
    LSM6DSM(uint8_t i2c_addr, TwoWire *wire);

    bool init();

    /// @brief initialize the sensor
    /// @param addr I2C address of sensor (0x6A through LOW hardware)
    /// @param port reference to I2C port
    /// @return true on successful initialization, false otherwise
    bool init(uint8_t addr, TwoWire &port);

    /// @brief IMU data ready check
    /// @return true if gyroscope and accelerometer are ready to send data
    bool dataReady();

    /// @brief update data class members for processing
    void readAll();

    /// @brief accelerometer data getters (per axis)
    /// @return floating point acceleration data in G
    float accX();
    float accY();
    float accZ();

    /// @brief gyroscope data getters (per axis)
    /// @return floating point angular rate in dps
    float gyX();
    float gyY();
    float gyZ();

    /// @brief read data from the chip's onboard temperature sensor
    /// @return temperature reading in Celsius on a successful read, 0 on read failure
    float readTemp();

    /// @brief calibrate the gyroscope to remove bias
    /// @param samples number of samples to average for calibration
    void calibrateGyro(int samples);

private:
    uint8_t _addr;
    TwoWire *_i2c;

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

    /// @brief combine 8-bit data for utility
    /// @param lsb 8-bit data from lower register
    /// @param hsb 8-bit data from higher register
    /// @return combined 16-bit data
    uint16_t combineBytes(uint8_t lsb, uint8_t hsb);

    /// @brief convert raw accelerometer reading to G-Units
    /// @param raw direct measurement
    /// @return converted reading as a float
    float rawToG(int16_t raw);

    /// @brief convert raw gryoscope reading to degrees-per-second
    /// @param raw direct measurement
    /// @return converted reading as a float
    float rawToDPS(int16_t raw);

    /// @brief convert raw temperature reading to Celsius
    /// @param raw direct measurement
    /// @return converted reading as a float
    float rawToC(int16_t raw);

    static constexpr float B16_SCALE = 32768.0f;
    static constexpr float TEMP_SENS = 256.0f;
    static constexpr float ACC_SENS_4G = 0.122f;
    static constexpr float ACC_SENS_8G = 0.244f;
    static constexpr float GY_SENS = 17.50f;

    float _gyBias[3] = {0.0f, 0.0f, 0.0f};
    int16_t _rawAcc[3] = {0, 0, 0};
    int16_t _rawGy[3] = {0, 0, 0};
};