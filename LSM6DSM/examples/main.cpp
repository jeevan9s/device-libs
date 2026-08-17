#include <Arduino.h>
#include <LSM6DSM.h>

LSM6DSM imu;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    if (!imu.init(0x35, Wire))
    {
        Serial.println("LSM6DSM init failed");
        while (1)
            delay(100);
    }

    Serial.println("LSM6DSM online");
}

void loop()
{

    if (imu.dataReady())
    {
        imu.readAll();

        Serial.print(" acc X: ");
        Serial.print(imu.accX(), 2);

        Serial.print(" | acc Y: ");
        Serial.print(imu.accY(), 2);

        Serial.print(" | acc Z: ");
        Serial.print(imu.accY(), 2);

        Serial.println(" G");

        Serial.print(" gy X: ");
        Serial.print(imu.accX(), 2);

        Serial.print(" | gy Y: ");
        Serial.print(imu.accY(), 2);

        Serial.print(" | gy Z: ");
        Serial.print(imu.accY(), 2);

        Serial.println(" dps");
    }

    float temp = imu.readTemp();
    if (!isnan(temp))
    {
        Serial.print(" | Temp: ");
        Serial.print(temp, 2);
        Serial.println(" C");
    }

    delay(250);
}