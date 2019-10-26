#include <Arduino.h>

#include <data/DataProcessor.h>
#include <device/HeartbeatSensor.h>

/* Default configuration */
#define PIN_HEARTBEAT_SENSOR A0

/* Device classes declarations */
HeartbeatSensor heartbeatSensor(PIN_HEARTBEAT_SENSOR);

void setup()
{
    Serial.begin(115200);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop()
{
    if (heartbeatSensor.fetchData()) {
        uint8_t heartrate = DataProcessor::getHeartrate(heartbeatSensor.getAllMeasurements());
        Serial.println(heartrate);
        
        heartbeatSensor.clearMeasurements();
    }

    delay(10);
}