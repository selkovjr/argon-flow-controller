#include "Arduino.h"
#include "LibPrintf.h"
#include "UserInput.h"

namespace UserInput {

  namespace Rotary {

    void setup() {
      pinMode(ROTARY_PIN_A, INPUT);
      pinMode(ROTARY_PIN_B, INPUT);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), activityA, CHANGE);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), activityB, CHANGE);
    }

    void activityA() {
      if (digitalRead(ROTARY_PIN_B)) {
        printf("---------- pin B 1 ----------\n");
        digitalWrite(13, HIGH);
      }
      else {
        printf("---------- pin B 0 ----------\n");
        digitalWrite(13, LOW);
      }
    }

    void activityB() {
      if (digitalRead(ROTARY_PIN_A)) {
        printf("---------- pin A 1 ----------\n");
        digitalWrite(13, HIGH);
      }
      else {
        printf("---------- pin A 0 ----------\n");
        digitalWrite(13, LOW);
      }
    }
  }

  namespace PushSwitch {
    void setup() {
      pinMode(PUSH_SW_PIN, INPUT);
      attachInterrupt(digitalPinToInterrupt(PUSH_SW_PIN), pushSwitchActivity, CHANGE);
    }

    void pushSwitchActivity() {
      if (digitalRead(PUSH_SW_PIN)) {
        printf("---------- Push Switch 1 ----------\n");
        digitalWrite(13, HIGH);
      }
      else {
        printf("---------- Push Switch 0 ----------\n");
        digitalWrite(13, LOW);
      }
    }
  }

  void setup() {
    pinMode(13, OUTPUT);  // On-board LED
    PushSwitch::setup();
    Rotary::setup();
  }
}
