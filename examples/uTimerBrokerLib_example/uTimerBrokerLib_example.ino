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


volatile bool calledA = false;
volatile bool calledB = false;
volatile bool calledC = false;
volatile bool calledD = false;
volatile bool calledE = false;
void callbackA() {
  calledA = true;
}
void callbackB() {
  calledB = true;
}
void callbackC() {
  calledC = true;
}
void callbackD() {
  calledD = true;
}
void callbackE() {
  calledE = true;
}

void setup() {
    delay (2000);
    Serial.begin(57600);
    uTimerBrokerLib TimerBrokerLib = uTimerBrokerLib::instance();
    TimerBrokerLib.add(callbackA, 1000);
    TimerBrokerLib.add(callbackB, 1500);
    TimerBrokerLib.add(callbackC, 2000);
    TimerBrokerLib.add(callbackD, 3000);
    TimerBrokerLib.add(callbackE, 5000);
}


void loop() {
  if (calledA) {
    calledA = false;
    Serial.println("A");
  }
  if (calledB) {
    calledB = false;
    Serial.println("B");
  }
  if (calledC) {
    calledC = false;
    Serial.println("C");
  }
  if (calledD) {
    calledD = false;
    Serial.println("D");
  }
  if (calledE) {
    calledE = false;
    Serial.println("E");
  }
}


