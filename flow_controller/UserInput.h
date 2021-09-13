#pragma once

#define ROTARY_PIN_A 2
#define ROTARY_PIN_B 3
#define PUSH_SW_PIN 21

namespace UserInput {
  namespace Rotary {
    void setup();
    void activityA();
    void activityB();
  }
  namespace PushSwitch {
    void setup();
    void pushSwitchActivity();
  }
  void setup();
}
