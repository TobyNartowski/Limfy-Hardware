#include <Arduino.h>

#include <Config.h>
#include <data/DataProcessor.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/VibrationModule.h>

/* Device classes declarations */
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
VibrationModule *vibrationModule;

void setup()
{
    Serial.begin(115200);

    heartbeatSensor = new HeartbeatSensor(PIN_HEARTBEAT_SENSOR);
    accelerometerSensor = new AccelerometerSensor();
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop()
{
    if (heartbeatSensor->fetchData()) {
        vibrationModule->vibrateNotification();
        uint8_t heartrate = DataProcessor::getHeartrate(heartbeatSensor->getAllMeasurements());
        Serial.println(heartrate);
        
        heartbeatSensor->clearMeasurements();
    }

    if (accelerometerSensor->fetchData()) {
        AccelerometerModel *data = accelerometerSensor->getAllMeasurements();

        accelerometerSensor->clearMeasurements();
    }

    delay(10);
}