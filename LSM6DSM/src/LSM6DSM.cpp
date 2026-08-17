#include <Arduino.h>
#include <Wire.h>
#include <LSM6DSM.h>

LSM6DSM imu;

void setup() {
    Serial.begin(115200);
    Wire.begin();

    if (!imu.init(0x6A, Wire)) {
        Serial.println("LSM6DSM init failed");
        while (1) delay(100);
    }

    Serial.println("LSM6DSM online");
}

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