/**
 * @file        i2c.h
 * @brief       I2C Bus Hardware Abstraction Definitions
 * @author      Jeevan Sanchez
 * @date        2026-11-05
 * 
 */

#pragma once

#include <Wire.h>

class I2CBus {
    public:
        I2CBus(TwoWire& _wire);

        bool begin(uint8_t data_pin = 21, uint8_t clock_pin = 22, uint32_t frequency = 100000); 
        bool write(uint8_t address, uint8_t* data, size_t length); 
        bool read(uint8_t address, uint8_t* buffer, size_t length); 

        bool writeRegister(uint8_t address, uint8_t reg, uint8_t value);
        bool writeRegister(uint8_t address, uint8_t reg, uint8_t *value, size_t length); 
        bool writeRegister16(uint8_t address, uint8_t reg, uint16_t value);
        bool readRegister(uint8_t address, uint8_t reg, uint8_t* buffer, size_t length); 
        bool readRegister(uint8_t address, uint8_t, uint16_t* buffer);

    private:
        TwoWire& _wire; 
};