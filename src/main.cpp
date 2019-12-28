#include <Arduino.h>
#include <driver/adc.h>

#include <Config.h>
#include <device/HeartbeatSensor.h>
#include <device/AccelerometerSensor.h>
#include <device/CommunicationModule.h>

/* Device classes declarations */
HeartbeatSensor *heartbeatSensor;
AccelerometerSensor *accelerometerSensor;
CommunicationModule *communicationModule;

int chargingInput = 0;
boolean chargingLedStatus = false;
unsigned long chargingTimestamp = millis();

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_BOARD_LED, OUTPUT);
    digitalWrite(PIN_BOARD_LED, HIGH);
    pinMode(PIN_CONNECT_LED, OUTPUT);
    digitalWrite(PIN_CONNECT_LED, LOW);
    adc2_config_channel_atten(PIN_CHARGING_INPUT, ADC_ATTEN_0db);

    heartbeatSensor = new HeartbeatSensor();
    accelerometerSensor = new AccelerometerSensor();
    communicationModule = new CommunicationModule();

    digitalWrite(PIN_BOARD_LED, HIGH);
}

void blinkChargingLed()
{
    if (millis() - chargingTimestamp > 1000) {
        chargingLedStatus = !chargingLedStatus;
        digitalWrite(PIN_BOARD_LED, chargingLedStatus);
        chargingTimestamp = millis();
    }
}

void loop()
{
    adc2_get_raw(PIN_CHARGING_INPUT, ADC_WIDTH_12Bit, &chargingInput);
    if (chargingInput <= CHARGING_THRESHOLD) {
        digitalWrite(PIN_BOARD_LED, LOW);

        if (heartbeatSensor->fetchData()) {
            communicationModule->setHeartbeat(heartbeatSensor->getHeartrate());
        }

        if (accelerometerSensor->fetchData()) {
            uint8_t steps = accelerometerSensor->getSteps();
            uint8_t shakiness = accelerometerSensor->getShakiness();

            if (shakiness < ACCELEROMETER_STEPS_SHAKE_THRESHOLD) {
                steps = 0;
            }

            communicationModule->fallDetected((uint8_t) accelerometerSensor->isFallDetected());
            communicationModule->setSteps(steps);
            communicationModule->setShakiness(shakiness);
            accelerometerSensor->clearMeasurements();
        }
    } else {
        blinkChargingLed();
    }

    delay(10);
}