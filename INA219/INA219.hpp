/**
 * @file        INA219.hpp
 * @brief       Definition of hardware driver class for INA219 power monitor
 * @author      Jeevan Sanchez
 * @date        2026-11-06
 * 
 */

#pragma once

#include <Arduino.h>
#include "i2c.hpp"

class INA219 {
    public:
        INA219(uint8_t addr, I2CBus& i2c); 
        bool begin();
        bool setCalibration(float max_exp_amps, float shunt_ohms); 
        bool read();

        float voltage_V;
        float current_mA;
        float power_mW;

    private:

        uint8_t _addr;
        I2CBus& _i2c;
        float _current_lsb = 0.0f;
        float _power_lsb = 0.0f;
};