# CCS811 Air Quality Sensor Library
> Written for GEKO

A C++/Arduino library for interfacing with the ams CCS811 indoor air quality sensor over I2C.

## Features
- Reads equivalent CO2 (eCO2) in ppm and total volatile organic compounds (TVOC) in ppb
- Checks for data-ready samples
- Supports temperature and humidity environmental compensation
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
2. Copy the `CCS811/` and `i2c/` folders into your project's `lib/` directory.
3. Include the driver with `#include <CCS811.hpp>`.

---

## Wiring Reference

| CCS811 Pin | Function | Connection |
|------------|----------|------------|
| VDD        | Power    | Per breakout board specifications |
| GND        | Ground   | GND |
| SDA        | I2C Data | MCU SDA pin |
| SCL        | I2C Clock | MCU SCL pin |

Default I2C address is `0x5A`; the alternate address is commonly `0x5B` when the breakout's address-select input is asserted. Check the breakout board's voltage and pin requirements.

---

## Quick Start

Create the shared I2C bus and sensor object, then initialize the bus and sensor. The CCS811 driver defaults to address `0x5A`.

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <i2c.hpp>
#include <CCS811.hpp>

I2CBus i2c(Wire);
CCS811 sensor(i2c);

void setup() {
    Serial.begin(115200);

    if (!i2c.begin()) {
        Serial.println("I2C initialization failed");
        while (1) delay(100);
    }

    if (!sensor.begin()) {
        Serial.println("CCS811 initialization failed");
        while (1) delay(100);
    }
}

void loop() {
    if (sensor.available()) {
        sensor.read();
        Serial.print("eCO2: ");
        Serial.print(sensor.eco2);
        Serial.print(" ppm | TVOC: ");
        Serial.print(sensor.tvoc);
        Serial.println(" ppb");
    }

    delay(250);
}
```

Optionally call `sensor.compensate(humidity, temperature)` with measured relative humidity in percent and temperature in degrees Celsius.

---

## API Reference

`CCS811(I2CBus& i2c, uint8_t address = 0x5A)`
Creates a driver using the shared I2C bus and selected 7-bit address.

---

`bool begin()`
Verifies the hardware ID and application status, starts the application, and configures the driver's measurement mode. Returns `true` if initialization succeeds.

---

`bool available()`
Checks the sensor's DATA_READY status bit. Returns `true` when a sample is ready; a failed I2C read also returns `false`.

---

`bool compensate(float humidity, float temp)`
Writes environmental compensation values. Humidity is in percent (0-100), temperature is in Celsius (-25 to 102.998). Returns `false` for out-of-range values or an unsuccessful write.

---

`void read()`
Reads the algorithm result and updates the public measurement fields if the I2C read succeeds.

---

`uint16_t eco2` / `uint16_t tvoc`
Public latest measurements: equivalent CO2 concentration in ppm and total VOC concentration in ppb.

---

Jeevan Sanchez, 2026
