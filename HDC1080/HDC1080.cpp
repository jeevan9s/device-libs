/**
 * @file        HDC1080.cpp
 * @brief       Implentation of hardware driver class for HDC1080 temperature and humidity sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 * 
 */

#include "HDC1080.hpp"

HDC1080::HDC1080(I2CBus& i2c, uint8_t addr) : _addr(addr), _i2c(i2c) {}

bool HDC1080::begin() {
    uint16_t m_id; 
    uint16_t d_id; 

    if (!_i2c.readRegister(_addr, 0xFE, &m_id)) return false; 
    if (m_id != 0x5449) return false; 

    if (!_i2c.readRegister(_addr, 0xFF, &d_id)) return false;
    if (d_id != 0x1050) return false; 

    // bit 15 is SW reset -> 2^15 = 0x8000
    if (!_i2c.writeRegister16(_addr, 0x02, 0x8000)) return false; 
    delay(5);

    // config
    // sequential mode 0x1000
    // 14-bit TRES 0x0400 
    // 14-bit HRES 0x0100
    
    uint16_t config = 0x1000; 

    if (!_i2c.writeRegister16(_addr, 0x02, config)) return false;

    return true;
}

void HDC1080::read() {
    uint8_t reg = 0x00;
    if (!_i2c.write(_addr, &reg, 1)) return;
    delay(15); 

    uint8_t raw[4] = {0}; 

    if (_i2c.read(_addr, raw, sizeof(raw))) {

        uint16_t rawTemp = (raw[0] << 8) | raw[1];
        uint16_t rawHumidity = (raw[2] << 8) | raw[3];

        temp = tempConvert(rawTemp);
        humidity = humidityConvert(rawHumidity);
    }
}

float HDC1080::tempConvert(uint16_t raw) const {
    return ((float)raw / 65536.0f) * 165.0f - 40.0f;
}

float HDC1080::humidityConvert(uint16_t raw) const {
    return ((float)raw / 65536.0f) * 100.0f; 
}
