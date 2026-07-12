
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

class LSM6DSM {
    public: 
        LSM6DSM() : _addr(0x6A), _i2c(&Wire) {}
        LSM6DSM(uint8_t i2c_addr, TwoWire* wire);

        bool init(); 
        bool init(uint8_t addr, TwoWire &port); 
        
        // data
        bool dataReady();

        void readAll(); 

        float accX(); 
        float accY(); 
        float accZ();
        
        float gyX(); 
        float gyY(); 
        float gyZ(); 

       float readTemp(); 

    private:
        uint8_t _addr; 
        TwoWire* _i2c; 

        bool readRegister(uint8_t reg, uint8_t* buffer, uint8_t len = 1); 
        bool writeRegister(uint8_t reg, uint8_t data); 

        uint16_t combineBytes(uint8_t lsb, uint8_t hsb);

        float rawToG(int16_t raw); 
        float rawToDPS(int16_t raw); 
        float rawToC(int16_t raw); 

        const float B16_SCALE = 32768.0f; 

        // formulae constants (sensitivity)
        const float TEMP_SENS = 256.0; // LSB/C
        const float ACC_SENS_4G = 0.122; // mg/LSB  
        const float ACC_SENS_8G = 0.244; // mg/LSB  
        const float GY_SENS = 17.50; // mdps/LSB  FS = ±500

       int16_t* _rawAcc[3]; 
       int16_t* _rawGy[3];
};



