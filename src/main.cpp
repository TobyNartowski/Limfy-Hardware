#include <Arduino.h>

#include <Config.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/CommunicationModule.h>

/* Device classes declarations */
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
CommunicationModule *communicationModule;

uint8_t heartbeat = 0, steps = 0;
uint16_t shakiness = 0;

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
        heartbeat = heartbeatSensor->getHeartrate();

        if (shakiness < ACCELEROMETER_STEPS_SHAKE_THRESHOLD) {
            steps = 0;
        }

        communicationModule->setHeartbeat(heartbeat);
        heartbeat = steps = shakiness = 0;
    }

    if (accelerometerSensor->fetchData()) {
        steps += accelerometerSensor->getSteps();
        shakiness += accelerometerSensor->getShakiness();
        
        communicationModule->setSteps(steps);
        communicationModule->setShakiness(shakiness);
        accelerometerSensor->clearMeasurements();
    }

    delay(10);
}