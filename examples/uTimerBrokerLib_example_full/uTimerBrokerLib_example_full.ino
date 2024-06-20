/**
 * \class uTimerBrokerLib
 * \brief Broker library for uTimerLib
 *
 * Adds multiple timed functions support to uTimerLib
 *
 * Decreases resolution to miliseconds
 *
 * Library depends on uTimerLib library, https://github.com/Naguissa/uTimerLib
 *
 * @see <a href="https://github.com/Naguissa/uTimerBrokerLib">https://github.com/Naguissa/uTimerBrokerLib</a>
 * @see <a href="https://github.com/Naguissa/uTimerLib">https://github.com/Naguissa/uTimerLib</a> - Needed dependecy
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 */
#include "Arduino.h"
#include "uTimerBrokerLib.h"

// Define it if not exists to avoid breaking the compiler.
// Set it correctly it if needed
#ifndef LED_BUILTIN
    #define LED_BUILTIN 1
#endif


// We use 3 attached functions:
// 1 - Blink led each second
// 2 - Write "SMS " via serial, one letter each 500ms. 3 times and then deactivates itself (5,5s run time)
// 3 - Attach 2nd callback (SMS) each 10s



volatile bool led_status = false;
volatile uint8_t sms_status = 0;
volatile uint8_t sms_counter = 0;
uTimerBrokerLib TimerBrokerLib = uTimerBrokerLib::instance();

void callbackBlink() {
  led_status = !led_status;
  digitalWrite(LED_BUILTIN, led_status);
}

void callbackSMS() {
  char outChar;
  switch (sms_status) {
    case 0:
        outChar = 'S';
        sms_status++;
        break;
    case 1:
        outChar = 'M';
        sms_status++;
        break;
    case 2:
        outChar = 'S';
        sms_status++;
        break;
    default:
        outChar = ' ';
        sms_status = 0;
        sms_counter++;
        break;
    }
    // We should not use Serial or millis insede interrupts, but this is a example
    // We could set a volatile variable and use Serial on loop.
    if (sms_counter > 2) { // Skips last space
        sms_counter = 0;
        TimerBrokerLib.clear(callbackSMS);
        Serial.println();
    } else {
        Serial.print(outChar);
    }
    
    
}

void callbackAttachSMS() {
    TimerBrokerLib.add(callbackSMS, 500);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    delay (2000);
    Serial.begin(57600);
    
    callbackAttachSMS();
    TimerBrokerLib.add(callbackBlink, 1000);
    TimerBrokerLib.add(callbackAttachSMS, 10000);
}


void loop() {
}


