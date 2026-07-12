/**
 * @file        ADS131M04.hpp
 * @brief       Header file containing class definitions for ADS131M04 library. 
 * @author      Jeevan Sanchez
 * @date        2026-04-29
 *
 * device-libs
 */

#pragma once

#include <Arduino.h>
#include <SPI.h>
#include "registers.h"

#define SPEED_SCLK 8000000

class ADS131M04 {
public:
    
    ADS131M04(int8_t csPin, int8_t drdyPin, SPIClass* spi);

    void init();

    bool readChannels(int32_t *readingsBuffer = nullptr);
    void computeVoltages(const int32_t *raw, float *volts);

    int32_t getChannelData(uint8_t ch);

private:
    int8_t csPin;
    int8_t drdyPin;

    SPIClass *spi;
    bool initialized;

    int32_t channels[4];
    
    const float voltageRef = 1.2;
    const float resFactor = 8388608.0; // 2^23

    uint32_t spiTransfer(uint16_t cmd);
    void captureFrame(uint32_t *outputArr, uint16_t command = 0x0000);

    int32_t extendSign(uint32_t data);
};

