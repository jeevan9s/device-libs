#include <Arduino.h>
#include <ADS131M04.h>

#define ADC_CS_PIN 0
#define ADC_DRDY_PIN 0

ADS131M04 adc(ADC_CS_PIN, ADC_DRDY_PIN, &SPI);

void setup() {
    Serial.begin(9600);
    delay(1000); 

    SPI.begin();

    adc.init();

    Serial.println("ADS131M04 initialized");
}

void loop() {

    // reading buffers
    int32_t raw[4];
    float volts[4]; 

    if (adc.readChannels(raw)) {
        
        adc.computeVoltages(raw, volts); 

        for (int i = 0; i < 4; i++) {

            Serial.print("CH");
            Serial.print(i);

            Serial.print(": ");

            Serial.print(raw[i]);
            Serial.print(" raw");

            Serial.print(" | ");

            Serial.print(volts[i], 6);
            Serial.println(" V");
        }

        Serial.println();
    }

    else {
        Serial.println("ADC read timeout");
    }
    
    delay(250);

    }