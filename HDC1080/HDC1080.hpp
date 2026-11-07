/**
 * @file        HDC1080.hpp
 * @brief       Definition of hardware driver class for HDC1080 temperature and humidity sensor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 * 
*/

#pragma once 

#include <Arduino.h>
#include "i2c.hpp"

class HDC1080 {
    public:
        HDC1080(I2CBus& i2c, uint8_t addr = 0x40); 

        bool begin();

        void read();
        
        float tempConvert(uint16_t raw) const;
        float humidityConvert(uint16_t raw) const;

        float temp; 
        float humidity;

    private:
        uint8_t _addr;
        I2CBus& _i2c;
};