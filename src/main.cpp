#include <Arduino.h>

#include <Config.h>
#include <data/DataProcessor.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/VibrationModule.h>
#include <device/TouchSensor.h>
#include <device/Display.h>

/* Device classes declarations */
Display *display;
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
VibrationModule *vibrationModule;
TouchSensor *touchSensor;

void setup()
{
    Serial.begin(115200);

    display = new Display();
    heartbeatSensor = new HeartbeatSensor(PIN_HEARTBEAT_SENSOR);
    accelerometerSensor = new AccelerometerSensor();
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);
    touchSensor = new TouchSensor(PIN_TOUCH_SENSOR);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop()
{
    display->readyToDraw();
    
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

    do {
        if (touchSensor->isTouched()) {
            display->drawCenterString("In development");
        }
    } while (display->draw());

    delay(10);
}