#include <Arduino.h>
#include <U8g2lib.h>

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

uint8_t heartrate = 0, steps = 0;
uint16_t shakiness = 0;

void setup()
{
    uint8_t bootCounter = 0;

    Serial.begin(9600);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    touchSensor = new TouchSensor(PIN_TOUCH_SENSOR);
    Serial.println("touch");
    delay(5000);
    Serial.println("touchafter");
    
    accelerometerSensor = new AccelerometerSensor();
    Serial.println("accelerometer");
    delay(5000);
    Serial.println("accelerometerafter");

    delay(500);

    Serial.println("init");
    communicationModule = new CommunicationModule();
     while (!communicationModule->checkConnection()) {
        delay(5000);
        bootCounter++;
        if (bootCounter > 4) {
            communicationModule->reset();
            bootCounter = 0;
        }
    }

    Serial.println("afterinit");
    delay(2000);
    Serial.println("network");
    communicationModule->initNetwork();
    Serial.println("afternetwork");
    delay(5000);
    Serial.println("afternetworkdelay");

    heartbeatSensor = new HeartbeatSensor();
    Serial.println("heartbeat");
    delay(5000);
    Serial.println("heartbeatafter");
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);
    Serial.println("vibration");
    delay(5000);
    Serial.println("vibrationafter");



    display = new Display();
    display->drawCenter("Limfy.");
    delay(1000);

    digitalWrite(13, HIGH);
    display->drawCenter("Hi!");
    Serial.println("on");
}

void loop()
{    
    if (heartbeatSensor->fetchData()) {
        heartrate = heartbeatSensor->getHeartrate();
        display->drawHeartrate(heartrate);
        display->drawAccelerometerData(steps, shakiness);
        
        heartrate = steps = shakiness = 0;
    }

    if (accelerometerSensor->fetchData()) {
        steps += accelerometerSensor->getSteps();
        shakiness += accelerometerSensor->getShakiness();
        accelerometerSensor->clearMeasurements();
        delay(200);
    }

    if (touchSensor->isTouched()) {
        Serial.println("beforesend");
        vibrationModule->vibrate(60);
        communicationModule->sendData();
        Serial.println("aftersend");
        delay(20000);
    }

    delay(10);
}