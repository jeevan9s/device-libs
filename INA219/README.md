# INA219 Power Monitor Library
> Written for GEKO

A C++/Arduino library for interfacing with the TI INA219 voltage, current, and power monitor over I2C.

## Features
- Measures bus voltage, shunt current, and power
- Converts register readings to volts, milliamperes, and milliwatts
- Configurable current scaling for the selected shunt resistor
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
2. Copy the `INA219/` and `i2c/` folders into your project's `lib/` directory.
3. Include the driver with `#include <INA219.hpp>`.

---

## Wiring Reference

| INA219 Pin | Function | Connection |
|------------|----------|------------|
| VCC        | Power    | Per breakout board specifications |
| GND        | Ground   | GND |
| SDA        | I2C Data | MCU SDA pin |
| SCL        | I2C Clock | MCU SCL pin |
| VIN+ / VIN-| Current path | Connect in series with the load |

Use the I2C address selected by the breakout board's address pins. Ensure the current path and shunt resistor are appropriate for the load.

---

## Quick Start

The default calibration in `begin()` is for a 3.4 A expected maximum and a 0.1 ohm shunt. Use `setCalibration()` after initialization if your hardware uses different values.

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <i2c.hpp>
#include <INA219.hpp>

I2CBus i2c(Wire);
INA219 monitor(0x40, i2c);

void setup() {
    Serial.begin(115200);

    if (!i2c.begin()) {
        Serial.println("I2C initialization failed");
        while (1) delay(100);
    }

    if (!monitor.begin()) {
        Serial.println("INA219 initialization failed");
        while (1) delay(100);
    }
}

void loop() {
    if (monitor.read()) {
        Serial.print("Voltage: ");
        Serial.print(monitor.voltage_V);
        Serial.print(" V | Current: ");
        Serial.print(monitor.current_mA);
        Serial.print(" mA | Power: ");
        Serial.print(monitor.power_mW);
        Serial.println(" mW");
    }

    delay(250);
}
```

---

## API Reference

`INA219(uint8_t addr, I2CBus& i2c)`
Creates a driver for the selected 7-bit I2C address.

---

`bool begin()`
Resets and configures the device for a 16 V bus range and continuous bus/shunt conversion, then applies the default 3.4 A / 0.1 ohm calibration. Returns `true` on success.

---

`bool setCalibration(float max_exp_amps, float shunt_ohms)`
Sets the expected maximum current (A) and shunt resistance (ohms), and writes the calibration register. Returns `false` if either value is non-positive, the derived calibration is out of range, or the write fails.

---

`bool read()`
Reads and converts the measurements. Returns `true` if all register reads succeed.

---

`float voltage_V`, `float current_mA`, `float power_mW`
Public latest bus voltage (V), current (mA), and power (mW), updated by a successful `read()`.

---

Jeevan Sanchez, 2026
