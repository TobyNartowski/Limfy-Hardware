#include "VibrationModule.h"

VibrationModule::VibrationModule(int modulePin)
{
    pinMode(modulePin, OUTPUT);
    this->modulePin = modulePin;
    timestamp = millis();
}

void VibrationModule::vibrate(uint8_t strength, unsigned long ms)
{
    analogWrite(modulePin, strength);
    delay(ms);
    analogWrite(modulePin, 0);
}
