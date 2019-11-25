#include <Arduino.h>

#include <Config.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/CommunicationModule.h>

/* Device classes declarations */
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
CommunicationModule *communicationModule;

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_BOARD_LED, OUTPUT);
    digitalWrite(PIN_BOARD_LED, HIGH);    

    heartbeatSensor = new HeartbeatSensor();
    accelerometerSensor = new AccelerometerSensor();
    communicationModule = new CommunicationModule();

    pinMode(PIN_CHARGING_LED, OUTPUT);
    digitalWrite(PIN_CHARGING_LED, HIGH);
    digitalWrite(PIN_BOARD_LED, LOW);
}

void loop()
{
    if (heartbeatSensor->fetchData()) {
        communicationModule->setHeartbeat(heartbeatSensor->getHeartrate());
    }

    if (accelerometerSensor->fetchData()) {
        uint8_t steps = accelerometerSensor->getSteps();
        uint8_t shakiness = accelerometerSensor->getShakiness();

        if (shakiness < ACCELEROMETER_STEPS_SHAKE_THRESHOLD) {
            steps = 0;
        }

        communicationModule->setSteps(steps);
        communicationModule->setShakiness(shakiness);
        accelerometerSensor->clearMeasurements();
    }

    delay(10);
}