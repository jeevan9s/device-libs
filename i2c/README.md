# I2C Bus Hardware Abstraction
> Written for GEKO

A small Arduino C++ wrapper around `TwoWire` for common I2C transfers and register operations. It is shared by some ofthe sensor libraries in this repository.

## Features
- Start a `TwoWire` bus and configure its clock frequency
- Read and write raw byte sequences
- Read and write 8-bit-addressed device registers
- Read and write 16-bit register values in big-endian byte order

---

## Installation

#### PlatformIO
Add the repository to your `platformio.ini` file:

```ini
lib_deps =
    https://github.com/Queens-Rocket-Engineering-Team/av-prop.git#main
```

#### Manual Installation
1. Download this repository.
2. Copy the `i2c/` folder into your project's `lib/` directory.
3. Include the wrapper with `#include <i2c.hpp>`.

---

## Quick Start

Create an `I2CBus` using the Arduino `Wire` instance. Call `begin()` before performing transfers.

```cpp
#include <Wire.h>
#include <i2c.hpp>

I2CBus i2c(Wire);

void setup() {
    Serial.begin(115200);

    if (!i2c.begin()) {
        Serial.println("I2C initialization failed");
        while (1) delay(100);
    }

    uint8_t device_id = 0;
    if (i2c.readRegister(0x40, 0xFE, &device_id, 1)) {
        Serial.print("Device ID: 0x");
        Serial.println(device_id, HEX);
    }
}
```

The default `begin()` pins are SDA 21 and SCL 22, with a 100 kHz clock. Supply explicit pins and a frequency when required by the board:

```cpp
i2c.begin(SDA_PIN, SCL_PIN, 400000);
```

---

## API Reference

`I2CBus(TwoWire& wire)`
Creates a wrapper around an existing `TwoWire` instance, such as `Wire`.

---

`bool begin(uint8_t data_pin = 21, uint8_t clock_pin = 22, uint32_t frequency = 100000)`
Starts the bus and sets its clock speed. Returns `true` if bus initialization succeeds.

---

`bool write(uint8_t address, uint8_t* data, size_t length)` / `bool read(uint8_t address, uint8_t* buffer, size_t length)`
Writes bytes to or reads bytes from a device at the given 7-bit I2C address. Return `true` when the entire transfer succeeds.

---

`bool writeRegister(uint8_t address, uint8_t reg, uint8_t value)` / `bool writeRegister(uint8_t address, uint8_t reg, uint8_t* value, size_t length)`
Writes one byte or a byte sequence beginning at an 8-bit register address.

---

`bool writeRegister16(uint8_t address, uint8_t reg, uint16_t value)`
Writes a 16-bit value most-significant byte first.

---

`bool readRegister(uint8_t address, uint8_t reg, uint8_t* buffer, size_t length)` / `bool readRegister(uint8_t address, uint8_t reg, uint16_t* buffer)`
Reads a byte sequence or a big-endian 16-bit value from an 8-bit register address.

---

Jeevan Sanchez, 2026
