/**
 **************************************************
 *
 * @file        ButtonInteraction.ino
 * @brief       Button interaction example for Soldered Button, LED & Buzzer Board
 *              Host: ESP32 WROVER-E
 *
 * Press a button to light its LED and sound the buzzer:
 *   BTN1 -> LED1 red,   1000 Hz
 *   BTN2 -> LED2 green, 2000 Hz
 *   BTN3 -> LED3 blue,  3000 Hz
 *
 * Multiple buttons can be pressed simultaneously.
 * Buzzer plays the highest pressed button's frequency.
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered board;

void setup()
{
    Wire.begin(); // if not using Qwiic, specify I2C pins: Wire.begin(21, 22)
    board.begin();
    delay(2000);

    board.setAllLEDs(0, 0, 0);
    board.setBuzzer(0);
}

void loop()
{
    uint8_t buttons = board.readButtons();

    bool btn1 = buttons & 0x01;
    bool btn2 = buttons & 0x02;
    bool btn3 = buttons & 0x04;

    board.setLED(0, btn3 ? 255 : 0, 0, 0);
    board.setLED(1, 0, btn2 ? 255 : 0, 0);
    board.setLED(2, 0, 0, btn1 ? 255 : 0);

    if (btn3)      board.setBuzzer(3000);
    else if (btn2) board.setBuzzer(2000);
    else if (btn1) board.setBuzzer(1000);
    else           board.setBuzzer(0);

    // remove delay for smooth tone
    delay(20);
}
