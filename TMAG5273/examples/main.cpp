#include <Arduino.h>
#include <TMAG5273.h>

TMAG5273 sensor; 

const int SCL_PIN = 0; 
const int SDA_PIN = 0; 

void setup() {
    Serial.begin(9600);

    Wire.begin();  

    if (!sensor.init(0x35, Wire)) {
        Serial.println("TMAG5273 init failed"); 
        while (1) delay(100); 
    }

    Serial.println("TMAG5273 online");
}

void loop() {
    float axes[3]; 
    
    if (sensor.getAllFlux(axes)) {
        Serial.print("X: "); 
        Serial.print(axes[0], 2); 
        
        Serial.print(" | Y: "); 
        Serial.print(axes[1], 2); 

        Serial.print(" | Z: "); 
        Serial.print(axes[2], 2); 
        
        Serial.println(" mT"); 
    }

    float temp = sensor.getTemp(); 
    if (!isnan(temp)) {
        Serial.print(" | Temp: "); 
        Serial.print(temp, 2); 
        Serial.println(" C");
    }

    delay(250); 
}