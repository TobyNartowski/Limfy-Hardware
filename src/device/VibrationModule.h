#pragma once

#include <Arduino.h>

class VibrationModule {
    int modulePin;
    unsigned long timestamp;
    bool isVibrating = false;
public:
    VibrationModule(int modulePin);
    void vibrate(uint8_t strength, unsigned long ms);
};