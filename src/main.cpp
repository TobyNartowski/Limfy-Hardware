#include <Arduino.h>
#include <ArduinoJson.h>

#include <Config.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/CommunicationModule.h>

/* Device classes declarations */
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
CommunicationModule *communicationModule;

uint16_t totalSteps = 0;
uint8_t heartrate = 0, steps = 0, stepsBefore = 0;
uint16_t shakiness = 0;

String getParsedJsonData()
{
    String result;
    StaticJsonDocument<JSON_OBJECT_SIZE(3)> doc;
    doc["heartrate"] = heartrate;
    doc["steps"] = steps;
    doc["shakiness"] = shakiness;
    serializeJson(doc, result);
    return result;
}

void setup()
{
    Serial.begin(115200);
    pinMode(22, OUTPUT);
    digitalWrite(22, HIGH);

    communicationModule = new CommunicationModule();
    heartbeatSensor = new HeartbeatSensor();
    accelerometerSensor = new AccelerometerSensor();

    digitalWrite(22, LOW);
}

void loop()
{ 
    if (heartbeatSensor->fetchData()) {
        heartrate = heartbeatSensor->getHeartrate();

        totalSteps += steps;
        Serial.println(getParsedJsonData());
        heartrate = steps = shakiness = 0;
    }

    if (accelerometerSensor->fetchData()) {
        steps += accelerometerSensor->getSteps();
        shakiness += accelerometerSensor->getShakiness();
        
        accelerometerSensor->clearMeasurements();
    }

    delay(10);
}