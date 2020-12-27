#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
   
}

void setup() {
    
    Serial.begin(9600);
   
    Serial.println("Adafruit MLX90614 test");  

 
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

  mlx.begin();  
}

void loop() {

  pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
 
        tsLastReport = millis();

        Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
        Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
        Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
        Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    
        Serial.println();
    
        
    }


 /*   Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
    Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

    Serial.println();
    delay(500);*/
    
    
 
  
}
