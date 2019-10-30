#include "TouchSensor.h"

#include <Arduino.h>

TouchSensor::TouchSensor(int sensorPin)
{
    this->sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);
}

bool TouchSensor::isTouched()
{
    return digitalRead(sensorPin) == HIGH;
}