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

namespace LSM6DSM_REG
{
    class Config
    {
    public:
        static constexpr uint8_t CTRL1_XL = 0x10;
        static constexpr uint8_t CTRL2_G = 0x11;
        static constexpr uint8_t CTRL3_C = 0x12;
        static constexpr uint8_t CTRL4_C = 0x13;
        static constexpr uint8_t CTRL5_C = 0x14;
        static constexpr uint8_t CTRL6_C = 0x15;
        static constexpr uint8_t CTRL7_G = 0x16;
        static constexpr uint8_t CTRL8_XL = 0x17;
        static constexpr uint8_t CTRL9_XL = 0x18;
        static constexpr uint8_t CTRL10_C = 0x19;
        static constexpr uint8_t WHO_AM_I = 0X0F;
        static constexpr uint8_t STATUS_REG = 0X1E;
    };

    class Data
    {
    public:
        static constexpr uint8_t OUT_TEMP_L = 0x20;
        static constexpr uint8_t OUT_TEMP_H = 0x21;
        static constexpr uint8_t OUTX_L_G = 0x22;
        static constexpr uint8_t OUTX_H_G = 0x23;
        static constexpr uint8_t OUTY_L_G = 0X24;
        static constexpr uint8_t OUTY_H_G = 0X25;
        static constexpr uint8_t OUTZ_L_G = 0x26;
        static constexpr uint8_t OUTZ_H_G = 0x27;
        static constexpr uint8_t OUTX_L_XL = 0x28;
        static constexpr uint8_t OUTX_H_XL = 0x29;
        static constexpr uint8_t OUTY_L_XL = 0X2A;
        static constexpr uint8_t OUTY_H_XL = 0X2B;
        static constexpr uint8_t OUTZ_L_XL = 0x2C;
        static constexpr uint8_t OUTZ_H_XL = 0x2D;
    };
};