

/**
 * @file        LSM6DSM.cpp
 * @brief       LSM6DSM IMU library. 
 * @author      Jeevan Sanchez
 * @date        2026-07-08
 * 
 * Supports data capture for accelerometer, gyroscope, and temperature sensor
 * 
 * device-libs/LSM6DSM
 */

#include "LSM6DSM.hpp"

LSM6DSM::LSM6DSM(uint8_t addr, TwoWire* wire) : _addr(addr), _i2c(wire) {}

/// @brief initialize the sensor
/// @param addr I2C address of sensor (0x6A through LOW hardware)
/// @param port reference to I2C port
/// @return true on successful initialization, false otherwise
bool LSM6DSM::init(uint8_t addr, TwoWire &port);  {
    if (!_i2c) return false; 
    ///
}

/// @brief combine 8-bit data for utility
/// @param lsb 8-bit data from lower register
/// @param hsb 8-bit data from higher register
/// @return combined 16-bit data
int16_t LSM6DSM::combineBytes(uint8_t msb, uint8_t lsb) {
    // shift, add, cast
    return (int16_t)((msb << 8) | lsb); 
}

/// @brief convert raw accelerometer reading to G-Units
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToG(int16_t raw) {
    return (float)raw * ACC_SENS_4G / 1000.0
}

/// @brief convert raw gryoscope reading to degrees-per-second
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToDPS(int16_t raw) {
    return (float)raw * GY_SENS / 1000.0
}

/// @brief convert raw temperature reading to Celsius
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToC(int16_t raw) {
    return (float)raw  / TEMP_SENS;
}


 