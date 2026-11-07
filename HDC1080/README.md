# HDC1080 Temperature and Humidity Sensor Library
> Written for GEKO

A C++/Arduino library for interfacing with the TI HDC1080 temperature and humidity sensor over I2C.

## Features
- Reads temperature in degrees Celsius
- Reads relative humidity in percent
- Verifies device identity and configures sequential conversions
- Uses the shared `I2CBus` hardware abstraction

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
2. Copy the `HDC1080/` and `i2c/` folders into your project's `lib/` directory.
3. Include the driver with `#include <HDC1080.hpp>`.

---

## Wiring Reference

| HDC1080 Pin | Function | Connection |
|-------------|----------|------------|
| VDD         | Power    | Per breakout board specifications |
| GND         | Ground   | GND |
| SDA         | I2C Data | MCU SDA pin |
| SCL         | I2C Clock | MCU SCL pin |

The default I2C address is `0x40`. Check the sensor or breakout board documentation for supply voltage and pull-up requirements.

---

## Quick Start

Create the I2C wrapper and sensor object, then initialize both before reading data.

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <i2c.hpp>
#include <HDC1080.hpp>

I2CBus i2c(Wire);
HDC1080 sensor(i2c);

void setup() {
    Serial.begin(115200);

    if (!i2c.begin()) {
        Serial.println("I2C initialization failed");
        while (1) delay(100);
    }

    if (!sensor.begin()) {
        Serial.println("HDC1080 initialization failed");
        while (1) delay(100);
    }
}

void loop() {
    sensor.read();

    Serial.print("Temperature: ");
    Serial.print(sensor.temp);
    Serial.print(" C | Humidity: ");
    Serial.print(sensor.humidity);
    Serial.println(" %");

    delay(250);
}
```

---

## API Reference

`HDC1080(I2CBus& i2c, uint8_t addr = 0x40)`
Creates a driver using the shared I2C bus and selected 7-bit address.

---

`bool begin()`
Checks the manufacturer and device IDs, resets the sensor, and configures sequential measurements. Returns `true` if all operations succeed.

---

`void read()`
Requests a temperature and humidity sample and updates the public fields when the I2C transfer succeeds.

---

`float tempConvert(uint16_t raw) const`
Converts a raw temperature reading to degrees Celsius.

---

`float humidityConvert(uint16_t raw) const`
Converts a raw humidity reading to relative humidity in percent.

---

`float temp`, `float humidity`
Public latest temperature (C) and relative humidity (%), updated by `read()`.

---

Jeevan Sanchez, 2026
