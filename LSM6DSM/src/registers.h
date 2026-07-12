/**
 * @file        registers.hpp
 * @brief       LSM6DSM register mappings.
 * @author      Jeevan Sanchez
 * @date        2026-07-08
 * 
 * Consult the datasheet (Table 20) for register contents: https://www.st.com/resource/en/datasheet/lsm6dsm.pdf
 * 
 * device-libs/LSM6DSM
 */

#pragma once
#include <Arduino.h>

namespace LSM6DSM_REG {
    class Config {
        constexpr uint8_t CTRL1_XL = 0x10; 
        constexpr uint8_t CTRL2_G = 0x11; 
        constexpr uint8_t CTRL3_C = 0x12; 
        constexpr uint8_t CTRL4_C = 0x13; 
        constexpr uint8_t CTRL5_C = 0x14; 
        constexpr uint8_t CTRL6_C = 0x15; 
        constexpr uint8_t CTRL7_G = 0x16; 
        constexpr uint8_t CTRL8_XL = 0x17; 
        constexpr uint8_t CTRL9_XL = 0x18; 
        constexpr uint8_t CTRL10_C = 0x19; 
        constexpr uint8_t WHO_AM_I = 0X0F; 
        constexpr uint8_t STATUS_REG = 0X1E;
};

    class Data {
        constexpr uint8_t OUT_TEMP_L = 0x20; 
        constexpr uint8_t OUT_TEMP_H = 0x21; 
        constexpr uint8_t OUTX_L_G = 0x22; 
        constexpr uint8_t OUTX_H_G = 0x23; 
        constexpr uint8_t OUTY_L_G = 0X24; 
        constexpr uint8_t OUTY_H_G = 0X25; 
        constexpr uint8_t OUTZ_L_G = 0x26; 
        constexpr uint8_t OUTZ_H_G = 0x27; 
        constexpr uint8_t OUTX_L_XL = 0x28; 
        constexpr uint8_t OUTX_H_XL = 0x29; 
        constexpr uint8_t OUTY_L_XL = 0X2A; 
        constexpr uint8_t OUTY_H_XL = 0X2B; 
        constexpr uint8_t OUTZ_L_XL = 0x2C; 
        constexpr uint8_t OUTZ_H_G = 0x2D; 
    };
};