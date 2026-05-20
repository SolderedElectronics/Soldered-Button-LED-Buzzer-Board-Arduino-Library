/**
 **************************************************
 * @file        attiny_firmware.ino
 * @brief       Button, LED & Buzzer Board firmware for ATtiny404
 *
 * IMPORTANT: Set clock to 10 MHz in megaTinyCore board settings.
 *            Run Tools -> Burn Bootloader after changing clock.
 *
 * I2C registers:
 *   0x00 (read)  - button states: bit0=BTN1, bit1=BTN2, bit2=BTN3 (1=pressed)
 *   0x01 (write) - LED colors: 9 bytes R1,G1,B1,R2,G2,B2,R3,G3,B3
 *   0x02 (write) - buzzer: 2 bytes uint16_t frequency in Hz, 0=off
 *
 * @authors     @ soldered.com
 ***************************************************/

#include <tinyNeoPixel_Static.h>
#include <Wire.h>

// IO port bank A (Dasduino/megaTinyCore pin numbers for ATtiny404)
#define PA0 11
#define PA1 8
#define PA2 9
#define PA3 10
#define PA4 0
#define PA5 1
#define PA6 2
#define PA7 3

// IO port bank B
#define PB0 7
#define PB1 6
#define PB2 5
#define PB3 4

#define ADDRESS_PIN1 5
#define ADDRESS_PIN2 4
#define ADDRESS_PIN3 3

#define DEFAULT_ADDRESS 0x30

void initDefault()
{
    pinMode(ADDRESS_PIN1, INPUT_PULLUP);
    pinMode(ADDRESS_PIN2, INPUT_PULLUP);
    pinMode(ADDRESS_PIN3, INPUT_PULLUP);
}

char getI2CAddress()
{
    char addrPin1 = !digitalRead(ADDRESS_PIN1);
    char addrPin2 = !digitalRead(ADDRESS_PIN2);
    char addrPin3 = !digitalRead(ADDRESS_PIN3);

    char address = DEFAULT_ADDRESS;
    address |= (addrPin1 << 0) | (addrPin2 << 1) | (addrPin3 << 2);

    return address;
}

#define PIN_LED   PA5
#define PIN_BTN1  PA3
#define PIN_BTN2  PA2
#define PIN_BTN3  PA1
#define PIN_BUZZ  PA6

#define NUM_LEDS  3

#define REG_BUTTONS 0x00
#define REG_LED     0x01
#define REG_BUZZER  0x02

int addr;

volatile uint8_t currentReg = REG_BUTTONS;
volatile uint8_t ledData[NUM_LEDS * 3] = {0};
volatile bool ledsNeedUpdate = false;
volatile bool buzzerNeedsUpdate = false;
volatile uint8_t buttonState = 0;
volatile uint16_t buzzerFreq = 0;

byte pixelBuf[NUM_LEDS * 3];
tinyNeoPixel leds = tinyNeoPixel(NUM_LEDS, PIN_LED, NEO_GRB, pixelBuf);

void setup()
{
    initDefault();
    addr = getI2CAddress();

    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_BTN2, INPUT_PULLUP);
    pinMode(PIN_BTN3, INPUT_PULLUP);

    pinMode(PIN_BUZZ, OUTPUT);
    digitalWrite(PIN_BUZZ, LOW);

    pinMode(PIN_LED, OUTPUT);
    leds.begin();
    leds.clear();
    leds.show();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
    uint8_t btn = 0;
    if (!digitalRead(PIN_BTN1)) btn |= 0x01;
    if (!digitalRead(PIN_BTN2)) btn |= 0x02;
    if (!digitalRead(PIN_BTN3)) btn |= 0x04;
    buttonState = btn;

    if (ledsNeedUpdate)
    {
        for (uint8_t i = 0; i < NUM_LEDS; i++)
        {
            leds.setPixelColor(i, ledData[i * 3], ledData[i * 3 + 1], ledData[i * 3 + 2]);
        }
        leds.show();
        ledsNeedUpdate = false;
    }

    if (buzzerNeedsUpdate)
    {
        if (buzzerFreq > 0)
            tone(PIN_BUZZ, buzzerFreq);
        else
            noTone(PIN_BUZZ);
        buzzerNeedsUpdate = false;
    }
}

void receiveEvent(int howMany)
{
    if (howMany < 1) return;

    currentReg = Wire.read();
    howMany--;

    if (currentReg == REG_LED)
    {
        for (uint8_t i = 0; i < (NUM_LEDS * 3) && howMany > 0; i++, howMany--)
        {
            ledData[i] = Wire.read();
        }
        ledsNeedUpdate = true;
    }
    else if (currentReg == REG_BUZZER && howMany >= 2)
    {
        buzzerFreq = ((uint16_t)Wire.read() << 8) | Wire.read();
        howMany -= 2;
        buzzerNeedsUpdate = true;
    }

    while (howMany-- > 0) Wire.read();
}

void requestEvent()
{
    switch (currentReg)
    {
    case REG_BUTTONS:
        Wire.write(buttonState);
        break;
    case REG_LED:
        Wire.write((const uint8_t *)ledData, NUM_LEDS * 3);
        break;
    case REG_BUZZER:
        Wire.write((uint8_t)(buzzerFreq >> 8));
        Wire.write((uint8_t)(buzzerFreq & 0xFF));
        break;
    default:
        Wire.write(0x00);
        break;
    }
}
