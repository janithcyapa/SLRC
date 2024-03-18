#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void OLEDBegin()
{
    // Serial.print(F("Connecting Display\n"));
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.print(F("SSD1306 allocation failed\n"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    // Serial.print(F("Display Connected\n"));
    // Clear the buffer
    display.clearDisplay();
    display.display();
}
void print(String txt)
{
    display.clearDisplay();
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(txt);
    display.display();
    Serial.println(txt + "\n");
}