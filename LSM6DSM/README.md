# LSM6DSM IMU Library
> Written for [Penguin](https://github.com/jeevan9s/penguin-bot)

A C++/Arduino library for interfacing with the STMicroelectronics LSM6DSM 6-axis IMU.

## Features
- 3-axis accelerometer data
- 3-axis gyroscope data
- On-chip temperature sensor
- I2C initialization and communication
- Built-in raw-to-engineering-unit conversion helpers
- Optional gyro bias calibration

---

## Installation

#### PlatformIO
Add the library to your `platformio.ini` file:

```ini
lib_deps =
    https://github.com/Queens-Rocket-Engineering-Team/av-prop.git#main
```

If you are using this repo directly in a local project, place the `LSM6DSM/` directory into your project's `lib/` folder.

#### Manual Installation
1. Download this repository.
2. Copy the `LSM6DSM/` folder into your project `lib/` directory.
3. Include the library with `#include <LSM6DSM.h>`.

---

## Wiring Reference

| LSM6DSM Pin | Function | Connection |
|------------|----------|------------|
| VDD        | Power    | 3.3V       |
| GND        | Ground   | GND        |
| SDA        | I2C Data | MCU SDA pin |
| SCL        | I2C Clock | MCU SCL pin |
| SA0        | Address select | Optional hardware strap |

Typical I2C usage:
- Default address: `0x6A` for SA0 = 0
- Alternate address: `0x6B` for SA0 = 1

---

## Quick Start

Start by including the library and creating an IMU object. The sensor uses the I2C bus, so you also need `Wire`.

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <LSM6DSM.h>

LSM6DSM imu;
```

In `setup()`, initialize serial output and the I2C bus. Then call `imu.init(0x6A, Wire)` to verify the sensor is present and configure the accelerometer and gyroscope.

```cpp
void setup() {
    Serial.begin(115200);
    Wire.begin();

    if (!imu.init(0x6A, Wire)) {
        Serial.println("LSM6DSM init failed");
        while (1) delay(100);
    }

    Serial.println("LSM6DSM online");
}
```

Once the sensor is initialized, check `dataReady()` before reading data. `readAll()` updates the internally cached accelerometer and gyroscope values, and the getters return the readings in engineering units.

```cpp
void loop() {
    if (imu.dataReady()) {
        imu.readAll();

        Serial.print("acc X: ");
        Serial.print(imu.accX(), 2);
        Serial.print(" | acc Y: ");
        Serial.print(imu.accY(), 2);
        Serial.print(" | acc Z: ");
        Serial.print(imu.accZ(), 2);
        Serial.println(" G");

        Serial.print("gyr X: ");
        Serial.print(imu.gyX(), 2);
        Serial.print(" | gyr Y: ");
        Serial.print(imu.gyY(), 2);
        Serial.print(" | gyr Z: ");
        Serial.print(imu.gyZ(), 2);
        Serial.println(" dps");
    }

    float temp = imu.readTemp();
    if (!isnan(temp)) {
        Serial.print("Temp: ");
        Serial.print(temp, 2);
        Serial.println(" C");
    }

    delay(250);
}
```

---

## API Reference

`LSM6DSM()`
Constructs an LSM6DSM object using the default address `0x6A` and the global `Wire` bus.

---

`LSM6DSM(uint8_t i2c_addr, TwoWire *wire)`
Constructs an LSM6DSM object using a custom I2C address and bus instance.

---

`bool init()`
Initializes the sensor using the object defaults.
- Verifies the device identity
- Performs a hardware reset
- Configures accelerometer and gyroscope settings
- Returns `true` on success, `false` otherwise

---

`bool init(uint8_t addr, TwoWire &port)`
Initializes the sensor on a specific I2C bus and address.
- `addr`: I2C device address
- `port`: Reference to a `TwoWire` instance such as `Wire`
- Returns `true` on successful initialization

---

`bool dataReady()`
Checks whether new accelerometer and gyroscope data is available.

---

`void readAll()`
Reads the latest raw accelerometer, gyroscope, and temperature data into the internal class buffers.

---

`float accX()`
`float accY()`
`float accZ()`
Returns the current acceleration in G for each axis.

---

`float gyX()`
`float gyY()`
`float gyZ()`
Returns the current angular rate in degrees per second for each axis.

---

`float readTemp()`
Returns the current internal temperature reading in Celsius.

---

`void calibrateGyro(int samples)`
Averages a number of gyroscope samples to estimate and remove bias from the gyro outputs.

---

Jeevan Sanchez, 2026