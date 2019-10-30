#include <Arduino.h>

#include <Config.h>
#include <data/DataProcessor.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>

/* Device classes declarations */
HeartbeatSensor heartbeatSensor(PIN_HEARTBEAT_SENSOR);
AccelerometerSensor *accelerometerSensor;

void setup()
{
    Serial.begin(115200);

    accelerometerSensor = new AccelerometerSensor();

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

    if (accelerometerSensor->fetchData()) {
        AccelerometerModel *data = accelerometerSensor->getAllMeasurements();

        accelerometerSensor->clearMeasurements();
    }

    delay(10);
}