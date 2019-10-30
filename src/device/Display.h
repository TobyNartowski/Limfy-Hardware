#pragma once

#include <U8glib.h>

class Display {
private:
    U8GLIB_SH1106_128X64 display;
public:
    Display();
    void readyToDraw();
    uint8_t draw();

    void drawCenterString(String text);
};