#include <Arduino.h>
#include <U8g2lib.h>
#include <ArduinoJson.h>

#include <Config.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/VibrationModule.h>
#include <device/TouchSensor.h>
#include <device/Display.h>
#include <device/CommunicationModule.h>

/* Device classes declarations */
Display *display;
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
VibrationModule *vibrationModule;
TouchSensor *touchSensor;
CommunicationModule *communicationModule;

uint16_t totalSteps = 0;
uint8_t heartrate = 0, steps = 0, stepsBefore = 0;
uint16_t shakiness = 0;
unsigned long connectionMillis = 0;

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
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    display = new Display();
    display->drawCenter("Limfy.");

    communicationModule = new CommunicationModule();
    communicationModule->check();

    heartbeatSensor = new HeartbeatSensor();
    delay(1000);
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);
    delay(1000);

    touchSensor = new TouchSensor(PIN_TOUCH_SENSOR);
    delay(1000);
    
    accelerometerSensor = new AccelerometerSensor();
    delay(1000);

    delay(500);

    digitalWrite(13, HIGH);
    display->drawCenter("Witaj!");
    delay(1500);
    
    display->drawHeartrate(heartrate);
    display->drawSteps(totalSteps);
    connectionMillis = millis();
}

void loop()
{
    if (millis() - connectionMillis > 60000) {
        communicationModule->check();
        connectionMillis = millis();
    }
 
    if (heartbeatSensor->fetchData()) {
        heartrate = heartbeatSensor->getHeartrate();

        vibrationModule->vibrate(30, 60);
        delay(1000);
        communicationModule->sendData(getParsedJsonData());
        vibrationModule->vibrate(50, 60);

        totalSteps += steps;

        display->drawSteps(totalSteps);
        display->drawHeartrate(heartrate);
        heartrate = steps = shakiness = 0;
    }

    if (accelerometerSensor->fetchData()) {
        steps += accelerometerSensor->getSteps();
        shakiness += accelerometerSensor->getShakiness();
        
        accelerometerSensor->clearMeasurements();
        delay(200);
    }

    if (touchSensor->isTouched()) {
        vibrationModule->vibrate(255, 60);
    }

    delay(10);
}