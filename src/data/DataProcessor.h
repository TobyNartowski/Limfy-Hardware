#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

#include <Config.h>

class DataProcessor {
private:
    // static void addHeartbeatMeasurement(bool *array);
public:
    static uint8_t getHeartrate(uint8_t data[]);
    
    // StaticJsonDocument<JSON_ARRAY_SIZE(3)> document;
    // JsonArray array = document.to<JsonArray>();
    
    // array.add(true);
    // array.add(false);
    // array.add(true);

    // serializeJson(document, destination);

};