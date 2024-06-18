/**
 * Really tiny library to basic 7 segments displays
 *
 * Functionality example
 *
 * @see <a href="https://github.com/Naguissa/uSevenSegmentLib">https://github.com/Naguissa/uSevenSegmentLib</a>
 * @see <a href="https://github.com/Naguissa/uTimerLib">https://github.com/Naguissa/uTimerLib</a> - Needed dependecy
 * @see <a href="https://www.foroelectro.net/librerias-arduino-ide-f29/usevensegmentlib-libreria-arduino-para-controlar-d-t193.html">https://www.foroelectro.net/librerias-arduino-ide-f29/usevensegmentlib-libreria-arduino-para-controlar-d-t193.html</a>
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


