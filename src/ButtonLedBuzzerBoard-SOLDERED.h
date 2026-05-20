/**
 **************************************************
 *
 * @file        ButtonLedBuzzerBoard-SOLDERED.h
 * @brief       Library for Soldered Button, LED & Buzzer Board (ATtiny404)
 *
 * I2C registers:
 *   0x00 (read)  - button states: bit0=BTN1, bit1=BTN2, bit2=BTN3
 *   0x01 (write) - LED colors: 9 bytes R1,G1,B1,R2,G2,B2,R3,G3,B3
 *   0x02 (write) - buzzer: 2 bytes uint16_t frequency in Hz, 0=off
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#ifndef __BUTTONLEDBUZZERBOARD_SOLDERED__
#define __BUTTONLEDBUZZERBOARD_SOLDERED__

#include "Arduino.h"
#include "Wire.h"

#define BLB_DEFAULT_ADDRESS 0x30

#define BLB_REG_BUTTONS 0x00
#define BLB_REG_LED     0x01
#define BLB_REG_BUZZER  0x02

#define BLB_NUM_LEDS 3

class ButtonLedBuzzerBoard_Soldered
{
  public:
    ButtonLedBuzzerBoard_Soldered(uint8_t address = BLB_DEFAULT_ADDRESS);
    void begin();

    void setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
    void setAllLEDs(uint8_t r, uint8_t g, uint8_t b);
    void setLEDs(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3,
                 uint8_t b3);

    void setBuzzer(uint16_t freq);

    uint8_t readButtons();
    bool isButton1Pressed();
    bool isButton2Pressed();
    bool isButton3Pressed();

  private:
    uint8_t _address;
    uint8_t _ledBuf[BLB_NUM_LEDS * 3];
    void _writeLEDs();
};

#endif
