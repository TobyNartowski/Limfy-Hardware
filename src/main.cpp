#include <Arduino.h>
#include <U8g2lib.h>

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

uint8_t heartrate = 255;

void setup()
{
    Serial.begin(115200);

    display = new Display();
    heartbeatSensor = new HeartbeatSensor(PIN_HEARTBEAT_SENSOR);
    accelerometerSensor = new AccelerometerSensor();
    vibrationModule = new VibrationModule(PIN_VIBRATION_MODULE);
    touchSensor = new TouchSensor(PIN_TOUCH_SENSOR);
    
    // display.begin();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop()
{    
    if (heartbeatSensor->fetchData()) {
        heartrate = DataProcessor::getHeartrate(heartbeatSensor->getAllMeasurements());        
        heartbeatSensor->clearMeasurements();
    }

    if (accelerometerSensor->fetchData()) {
        AccelerometerModel *data = accelerometerSensor->getAllMeasurements();

        accelerometerSensor->clearMeasurements();
    }

    if (touchSensor->isTouched()) {
        vibrationModule->vibrate(30);
    }

    display->drawHeartrate(heartrate);

    delay(10);
}