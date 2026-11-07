/**
 * @file        INA219.cpp
 * @brief       Implentation of hardware driver class for INA219 power monitor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 *
 */

#include "INA219.hpp"

INA219::INA219(uint8_t addr, I2CBus &i2c) : _addr(addr), _i2c(i2c) {}

bool INA219::begin()
{

    if (!_i2c.writeRegister16(_addr, 0x00, 0x8000))
        return false;
    delay(5);

    // config word
    // Bit breakdown (16-bit):
    // - RST (Bit 15): 0
    // - Res (Bit 14): 0
    // - BRNG (Bit 13): 0 -> 16V Bus Range
    // - PG   (Bits 12-11): 11 -> ±320mV Shunt Range (Gain /8)
    // - BADC (Bits 10-7):  0011 -> 12-bit / 1 sample Bus ADC
    // - SADC (Bits 6-3):   0011 -> 12-bit / 1 sample Shunt ADC
    // - MODE (Bits 2-0):   111  -> Continuous Shunt and Bus

    // 0001 1001 1001 1111 => 0x199F

    if (!_i2c.writeRegister16(_addr, 0x00, 0x199F))
        return false;

    // 3.4 A is an approximate peak current draw, 0.1 ohm shunt is typically used across INA219 breakout boards
    if (!setCalibration(3.4, 0.1))
        return false;

    return true;
}

bool INA219::setCalibration(float max_exp_amps, float shunt_ohms)
{
    if (max_exp_amps <= 0.0f || shunt_ohms <= 0.0f)
        return false;

    float current_lsb = max_exp_amps / 32768.0f;
    float calibration = 0.04096f / (current_lsb * shunt_ohms);
    if (calibration < 1.0f || calibration > 65535.0f)
        return false;

    uint16_t cal_value = static_cast<uint16_t>(calibration); // consult section 8.5.1 of datasheet for more info on calibration register
    if (!_i2c.writeRegister16(_addr, 0x05, cal_value))
        return false;

    _current_lsb = current_lsb;
    _power_lsb = _current_lsb * 20.0f;
    return true;
}

bool INA219::read()
{
    uint16_t raw;

    // read
    // validate
    // convert

    if (!_i2c.readRegister(_addr, 0x01, &raw))
        return false;
    float shunt_mV = static_cast<int16_t>(raw) * 0.01f;

    if (!_i2c.readRegister(_addr, 0x02, &raw))
        return false;
    float bus_V = (raw >> 3) * 0.004f;

    voltage_V = bus_V + (shunt_mV / 1000.0f);

    if (!_i2c.readRegister(_addr, 0x03, &raw))
        return false;
    power_mW = raw * _power_lsb * 1000.0f;

    if (!_i2c.readRegister(_addr, 0x04, &raw))
        return false;
    current_mA = static_cast<int16_t>(raw) * _current_lsb * 1000.0f;

    return true;
}
