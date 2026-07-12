

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

LSM6DSM::LSM6DSM(uint8_t addr, TwoWire *wire) : _addr(addr), _i2c(wire) {}

bool LSM6DSM::init()
{
    if (!_i2c)
        return false;
    return init(_addr, *_i2c);
}

/// @brief initialize the sensor
/// @param addr I2C address of sensor (0x6A through LOW hardware)
/// @param port reference to I2C port
/// @return true on successful initialization, false otherwise
bool LSM6DSM::init(uint8_t addr, TwoWire &port)
{
    if (!_i2c)
        return false;
    _i2c = &port;
    _addr = addr;

    // handshake | id is 6Ah
    uint8_t id;
    if (!readRegister(LSM6DSM_REG::Config::WHO_AM_I, &id))
        return false;
    if (id != 0x6A)
        return false;

    // trigger hardware reset
    if (!writeRegister(LSM6DSM_REG::Config::CTRL3_C, 0x01))
        return false;
    delay(10);

    // config

    // configure accel control reg (CTRL1_XL)
    // bits 3-0: ODR & Power Mode Selection -- 416 Hz -> 0110
    // bits 1-0: FS Selection -- 4g -> 10
    // combined: 0110 1000 = 68
    if (!writeRegister(LSM6DSM_REG::Config::CTRL1_XL, 0x68))
        return false;

    // configure gyro control reg (CTRL2_G)
    // bits 3-0: ODR & Power Mode Selection -- 416 Hz -> 0110
    // bits 1-0: FS Selection -- 500dps -> 01
    // FS @ 125 dps -- disable -> 0
    // combined: 0110 0100 = 64
    if (!writeRegister(LSM6DSM_REG::Config::CTRL2_G, 0x64))
        return false;

    // configure control reg (CTRL3_C)
    // enable BDU -> 1
    // enable multi-byte bursts -> 1
    // software reset -> 1
    if (!writeRegister(LSM6DSM_REG::Config::CTRL3_C, 0x44))
        return false;

    // configure control reg 2 (CTRL4_C)
    // enable I2C -> 0
    // mask both drdy signals -> 1
    if (!writeRegister(LSM6DSM_REG::Config::CTRL4_C, 0x08))
        return false;

    // configure control reg (CTRL7_G)
    // bit 7: G_HM_MODE (0 = high-performance mode ENABLED)
    // bit 6: HP_EN_G (0 = high-pass filter DISABLED to allow LPF2 operation)
    // combined: 0000 0000 = 0x00
    if (!writeRegister(LSM6DSM_REG::Config::CTRL7_G, 0x00))
        return false;

    // configure control reg (CTRL8_XL)
    // enable LPF2 for accel -> 1
    // set cutoff to ODR/9 -> 10
    // combined: 1100 0000
    if (!writeRegister(LSM6DSM_REG::Config::CTRL8_XL, 0xC0))
        return false;

    return true;
}

/// @brief IMU data ready check
/// @return true if gyroscope and accelerometer are ready to send data
bool LSM6DSM::dataReady()
{
    uint8_t status;
    if (!readRegister(LSM6DSM_REG::Config::STATUS_REG, &status))
    {
        return false;
    }

    return (status & 0x03) == 0x03;
}

/// @brief update data class members for processing
void LSM6DSM::readAll()
{
    uint8_t buffer[12];

    if (readRegister(LSM6DSM_REG::Data::OUTX_L_G, buffer, 12))
    {
        _rawGyro[0] = combineBytes(buffer[1], buffer[0]);
        _rawGyro[1] = combineBytes(buffer[3], buffer[2]);
        _rawGyro[2] = combineBytes(buffer[5], buffer[4]);

        _rawAcc[0] = combineBytes(buffer[7], buffer[6]);
        _rawAcc[1] = combineBytes(buffer[9], buffer[8]);
        _rawAcc[2] = combineBytes(buffer[11], buffer[10]);
    }
}

float LSM6DSM::accX()
{
    return rawToG(_rawAcc[0]);
}

float LSM6DSM::accY()
{
    return rawToG(_rawAcc[1]);
}

float LSM6DSM::accZ()
{
    return rawToG(_rawAcc[2]);
}

float LSM6DSM::gyX()
{
    return rawToDPS(_rawGyro[0]);
}

float LSM6DSM::gyY()
{
    return rawToDPS(_rawGyro[1]);
}

float LSM6DSM::gyZ()
{
    return rawToDPS(_rawGyro[2]);
}

/// @brief read data from the chip's onboard temperature sensor
/// @return temperature reading in Celsius on a successful read, 0 on read failure
float LSM6DSM::readTemp()
{
    uint8_t tempBuffer[2];

    if (readRegister(LSM6DSM::Data::OUT_TEMP_L, tempBuffer, 2))
    {
        int16_t tempRaw = combineBytes(tempBuffer[1], tempBuffer[0]);
        return rawToC(tempRaw);
    }

    return 0.0f; // fail
}

/// @brief reads one or more bytes from a specific register
/// @param reg starting register address to read from
/// @param buffer pointer to a byte array for stored data
/// @param len number of bytes to read (defaults to 1)
/// @return true if the I2C transaction was successful and requested number of bytes were received, false otherwise
bool LSM6DSM::readRegister(uint8_t reg, uint8_t *buffer, uint8_t len)
{
    if (!_i2c || len <= 0)
        return false;

    _i2c->beginTransmission(_addr);
    _i2c->write(reg);
    if (_i2c->endTransmission(false) != 0)
        return false;

    if (_i2c->requestFrom(_addr, len) == len)
    {
        for (uint8_t i = 0; i < len; i++)
        {
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
bool LSM6DSM::writeRegister(uint8_t reg, uint8_t data)
{
    if (!_i2c)
        return false;

    _i2c->beginTransmission(_addr);
    _i2c->write(reg);
    _i2c->write(data);

    return (_i2c->endTransmission() == 0);
}

/// @brief combine 8-bit data for utility
/// @param lsb 8-bit data from lower register
/// @param hsb 8-bit data from higher register
/// @return combined 16-bit data
uint16_t LSM6DSM::combineBytes(uint8_t msb, uint8_t lsb)
{
    // shift, add, cast
    return (int16_t)((msb << 8) | lsb);
}

/// @brief convert raw accelerometer reading to G-Units
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToG(int16_t raw) {
    return (float)raw * ACC_SENS_4G / 1000.0;
}

/// @brief convert raw gryoscope reading to degrees-per-second
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToDPS(int16_t raw) {
    return (float)raw * GY_SENS / 1000.0;
}

/// @brief convert raw temperature reading to Celsius
/// @param raw direct measurement
/// @return converted reading as a float
float LSM6DSM::rawToC(int16_t raw)
{
    return (float)raw / TEMP_SENS;
}
