#pragma once

class VibrationModule {
    int modulePin;
    unsigned long timestamp;
    bool isVibrating = false;
    void vibrate(unsigned long ms);
public:
    VibrationModule(int modulePin);
    void vibrateNotification();
};