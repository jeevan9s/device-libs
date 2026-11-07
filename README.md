# device-libs

> A collection of reusable embedded C++ libraries I've written for interfacing with sensors and peripheral devices, primarily for ESP32- and PlatformIO-based projects.

## Supported Devices

- **LSM6DSM** — 6-axis IMU (accelerometer + gyroscope)
- **ADS131M04** — 4-channel, 24-bit precision ADC
- **TMAG5273** — 3-axis Hall-effect magnetic sensor
- **CCS811** — indoor air quality sensor (eCO2 and TVOC)
- **HDC1080** — temperature and humidity sensor
- **INA219** — voltage, current, and power monitor
- **i2c** — shared I2C bus hardware abstraction

## Goals

These libraries are designed to provide:
- Clean, hardware-focused APIs
- Minimal dependencies
- Easy integration into PlatformIO projects
- Reusable drivers for robotics, avionics, and embedded systems

## Comments
- Libraries I've written in the past few months (fall 2026), use a shared I2C HAL. These were all developed together for GEKO, a rover I worked on for a school design project.