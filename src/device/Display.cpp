#include "Display.h"

Display::Display() {
    display = U8GLIB_SH1106_128X64(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);
    display.setColorIndex(1);
    display.setFont(u8g_font_unifont);
    display.begin();
}

uint8_t Display::draw()
{
    return display.nextPage();
}

void Display::readyToDraw()
{
    display.firstPage();
}

void Display::drawCenterString(String text)
{
    display.drawStr((64 - ((text.length() * 8) / 2)), 36, text.c_str());
}