#include "Arduino.h"
#include "LibPrintf.h"
#include "UserInput.h"

namespace UserInput {

  namespace Rotary {

    void setup() {
      pinMode(ROTARY_PIN_A, INPUT);
      pinMode(ROTARY_PIN_B, INPUT);
      attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), activityA, FALLING);
    }

    void activityA() {
      if (digitalRead(ROTARY_PIN_B)) {
        printf("CCW\n");
      }
      else {
        printf("CW\n");
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
        printf("---- Push Switch Up   ----------\n");
      }
      else {
        printf("---- Push Switch Down ----------\n");
      }
    }
  }

  void setup() {
    PushSwitch::setup();
    Rotary::setup();
  }
}
