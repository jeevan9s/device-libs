

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

bool LSM6DSM::init() {
    if (!_i2c) return false;
    return init(_addr, *_i2c);
}

/// @brief initialize the sensor
/// @param addr I2C address of sensor (0x6A through LOW hardware)
/// @param port reference to I2C port
/// @return true on successful initialization, false otherwise
bool LSM6DSM::init(uint8_t addr, TwoWire &port);  {
    if (!_i2c) return false; 
    _i2c = &port; 
    _addr = addr; 
    
}


/// @brief reads one or more bytes from a specific register
/// @param reg starting register address to read from
/// @param buffer pointer to a byte array for stored data
/// @param len number of bytes to read (defaults to 1)
/// @return true if the I2C transaction was successful and requested number of bytes were received, false otherwise
bool LSM6DSM::readRegister(uint8_t reg, uint8_t* buffer, uint8_t len) {
    if (!_i2c || len <= 0) return false; 

    _i2c->beginTransmission(_addr); 
    _i2c->write(reg); 
    if (_i2c->endTransmission(false) != 0) return false; 


    if (_i2c->requestFrom(_addr, len) == len) {
        for (uint8_t i = 0; i < len; i++) {
                buffer[i] = _i2c->read();
            }
        
        return true;
    }

    return false;
}

/// @brief write a single byte of data into a register
/// @param reg reigster address to write to 
/// @param data information to be written
/// @return true if the write succeeds, false otherwise
bool LSM6DSM::writeRegister(uint8_t reg, uint8_t data) {
    if (!_i2c) return false; 

    _i2c->beginTransmission(_addr); 
    _i2c->write(reg); 
    _i2c->write(data); 

    return (_i2c->endTransmission() == 0);
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


 