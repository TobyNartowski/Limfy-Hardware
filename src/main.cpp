#include <Arduino.h>
#include <U8g2lib.h>

#include <Config.h>
#include <data/DataProcessor.h>
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
DataProcessor *dataProcessor;
CommunicationModule *communicationModule;

uint8_t heartrate = 0, steps = 0;
uint16_t shakiness = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    display = new Display();
    display->drawString("Booting up...");

    heartbeatSensor = new HeartbeatSensor(PIN_HEARTBEAT_SENSOR);
    accelerometerSensor = new AccelerometerSensor();
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);
    touchSensor = new TouchSensor(PIN_TOUCH_SENSOR);
    communicationModule = new CommunicationModule();
    
    display->drawString("Connecting...");

    while (!communicationModule->checkConnection()) {
        delay(1000);
    }
    communicationModule->initNetwork();

    digitalWrite(13, HIGH);

    display->drawString("Data...");
}

void loop()
{    
    if (heartbeatSensor->fetchData()) {
        heartrate = dataProcessor->getHeartrateData(heartbeatSensor->getAllMeasurements());        
        heartbeatSensor->clearMeasurements();

        display->drawHeartrate(heartrate);
        display->drawAccelerometerData(steps, shakiness);

        heartrate = steps = shakiness = 0;
    }

    if (accelerometerSensor->fetchData()) {
        steps += dataProcessor->getAccelerometerSteps(accelerometerSensor->getAllMeasurements());
        shakiness += dataProcessor->getAccelerometerShakiness(accelerometerSensor->getAllMeasurements());
        accelerometerSensor->clearMeasurements();
    }

    if (touchSensor->isTouched()) {
        vibrationModule->vibrate(30);
    }

    delay(10);
}