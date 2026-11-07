/**
 * @file        CCS811.cpp
 * @brief       Implementation of hardware driver class for CCSB11 VOC/CO2 sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 * 
 */

#include "CCS811.hpp"

CCS811::CCS811(I2CBus& i2c, uint8_t address) : _addr(address), _i2c(i2c) {}


bool CCS811::begin() {
    uint8_t hw_id = 0; 
    uint8_t status = 0;

    if (!_i2c.readRegister(_addr, 0x20, &hw_id, 1)) return false;
    if (hw_id != 0x81) return false;


    if (!_i2c.readRegister(_addr, 0x00, &status, 1)) return false;  
    if ((status & 0x10) == 0) return false; 
    
    uint8_t app_start = 0xF4;
    if (!_i2c.write(_addr, &app_start, 1)) return false;
    delay(5);
   

    if (!_i2c.writeRegister(_addr, 0x01, 0x10)) return false; 

    return true;
}

void CCS811::read() {
    uint8_t buffer[4] = {0}; 

    if (!_i2c.readRegister(_addr, 0x02, buffer, sizeof(buffer))) return;

    eco2 = static_cast<uint16_t>((buffer[0] << 8) | buffer[1]); 
    tvoc = static_cast<uint16_t>((buffer[2] << 8) | buffer[3]); 
}

bool CCS811::compensate(float humidity, float temp) {
    if (humidity < 0.0f || humidity > 100.0f || temp < -25.0f || temp > 102.998f)
        return false;

    uint16_t temp_conv = static_cast<uint16_t>((temp + 25.0f) * 512.0f + 0.5f);
    uint16_t hum_conv = static_cast<uint16_t>(humidity * 512.0f + 0.5f);

    uint8_t buffer[4] = {
        (uint8_t)(hum_conv >> 8),
        (uint8_t)(hum_conv & 0xFF),
        (uint8_t)(temp_conv >> 8),
        (uint8_t)(temp_conv & 0xFF)
    };

    return _i2c.writeRegister(_addr, 0x05, buffer, 4); 
}


bool CCS811::available() {
    uint8_t status = 0;
    if (!_i2c.readRegister(_addr, 0x00, &status, 1)) return false; 

    return ((status & 0x08) != 0); 
}
