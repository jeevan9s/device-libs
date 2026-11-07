/**
 * @file        i2c.cpp
 * @brief       I2C Bus Hardware Abstraction Implementation
 * @author      Jeevan
 * @date        2026-11-05
 * 
 */

#include "i2c.hpp"

I2CBus::I2CBus(TwoWire& wire) : _wire(wire) {}

bool I2CBus::begin(uint8_t data_pin, uint8_t clock_pin, uint32_t frequency) {
    if (!_wire.begin(data_pin, clock_pin)) return false; 
    _wire.setClock(frequency);
    return true;
}

bool I2CBus::write(uint8_t address, uint8_t* data, size_t length) {
    if (data == nullptr && length > 0) return false;
    _wire.beginTransmission(address); 
    size_t written = _wire.write(data, length); 
    
    return (_wire.endTransmission() == 0 && written == length);
}

bool I2CBus::read(uint8_t address, uint8_t* buffer, size_t length) {
    if (buffer == nullptr && length > 0) return false;
    size_t received = _wire.requestFrom(address, length); 
    if (received != length) return false; 

    for (size_t i = 0; i < length; i++) {
        if (!_wire.available()) return false;
        buffer[i] = _wire.read();
    }

    return true;
}

bool I2CBus::writeRegister(uint8_t address, uint8_t reg, uint8_t value) {
    _wire.beginTransmission(address); 
    size_t register_written = _wire.write(reg); 
    size_t value_written = _wire.write(value);

    return (_wire.endTransmission() == 0 && register_written == 1 && value_written == 1); 
}

bool I2CBus::writeRegister(uint8_t address, uint8_t reg, uint8_t* value, size_t length) {
    if (value == nullptr && length > 0) return false;
    _wire.beginTransmission(address); 
    size_t register_written = _wire.write(reg); 
    size_t written = _wire.write(value, length);

    return (_wire.endTransmission() == 0 && register_written == 1 && written == length); 
}

bool I2CBus::writeRegister16(uint8_t address, uint8_t reg, uint16_t value) {
    uint8_t data[2] = {
        static_cast<uint8_t>(value >> 8),
        static_cast<uint8_t>(value & 0xFF)
    };
    return writeRegister(address, reg, data, sizeof(data));
}


bool I2CBus::readRegister(uint8_t address, uint8_t reg, uint8_t* buffer, size_t length) {
    if (buffer == nullptr && length > 0) return false;
    _wire.beginTransmission(address); 
    if (_wire.write(reg) != 1) {
        _wire.endTransmission();
        return false;
    }

    if (_wire.endTransmission(false) != 0) return false; 

    size_t received = _wire.requestFrom(address, length); 
    if (received != length) return false; 

    for (size_t i = 0; i < length; i++) {
        if (!_wire.available()) return false;
        buffer[i] = _wire.read();
    }

    return true;
}

bool I2CBus::readRegister(uint8_t address, uint8_t reg, uint16_t* buffer) {
    if (buffer == nullptr) return false;
    uint8_t data[2];

    if (!readRegister(address, reg, data, 2)) return false;

    *buffer = (static_cast<uint16_t>(data[0]) << 8) | data[1];

    return true;
}