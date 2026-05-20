/**
 **************************************************
 *
 * @file        FullDemo.ino
 * @brief       Full demo for Soldered Button, LED & Buzzer Board
 *              Host: ESP32 WROVER-E
 *
 * - Prints button states to Serial (115200 baud)
 * - Cycles all LEDs through colors every 2 seconds
 * - Short beep on each color change
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered board;

const uint8_t colors[][3] = {
    {255,   0,   0},  // red
    {  0, 255,   0},  // green
    {  0,   0, 255},  // blue
    {255, 255,   0},  // yellow
    {  0, 255, 255},  // cyan
    {255,   0, 255},  // magenta
    {255, 255, 255},  // white
    {  0,   0,   0},  // off
};
const uint8_t numColors = sizeof(colors) / sizeof(colors[0]);
uint8_t colorIdx = 0;

unsigned long lastColorChange = 0;

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // if not using Qwiic, specify I2C pins: Wire.begin(21, 22)
    board.begin();
    delay(2000);

    Serial.println("Button, LED & Buzzer Board - Full Demo");
    board.setAllLEDs(0, 0, 0);
}

void loop()
{
    Serial.print("BTN1:");
    Serial.print(board.isButton1Pressed() ? "ON " : "off");
    Serial.print(" BTN2:");
    Serial.print(board.isButton2Pressed() ? "ON " : "off");
    Serial.print(" BTN3:");
    Serial.println(board.isButton3Pressed() ? "ON " : "off");

    if (millis() - lastColorChange > 2000)
    {
        uint8_t r = colors[colorIdx][0];
        uint8_t g = colors[colorIdx][1];
        uint8_t b = colors[colorIdx][2];
        board.setAllLEDs(r, g, b);

        board.setBuzzer(2000);
        delay(100);
        board.setBuzzer(0);

        colorIdx = (colorIdx + 1) % numColors;
        lastColorChange = millis();
    }

    delay(100);
}
