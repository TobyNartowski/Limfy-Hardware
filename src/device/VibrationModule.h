#pragma once

class VibrationModule {
    int modulePin;
    unsigned long timestamp;
    bool isVibrating = false;
public:
    VibrationModule(int modulePin);
    void vibrate(unsigned long ms);
    void vibrateNotification();
};