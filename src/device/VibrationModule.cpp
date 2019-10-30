#include "VibrationModule.h"

#include <Arduino.h>

VibrationModule::VibrationModule(int modulePin)
{
    pinMode(modulePin, OUTPUT);
    this->modulePin = modulePin;
    timestamp = millis();
}

void VibrationModule::vibrate(unsigned long ms)
{
    analogWrite(modulePin, 255);
    delay(ms);
    analogWrite(modulePin, 0);
}

void VibrationModule::vibrateNotification()
{
    vibrate(50);
    delay(50);
    vibrate(100);
}
