#include "Arduino.h"
#include "LibPrintf.h"
#include "Trigger.h"

namespace Trigger {
  void triggerAction() {
    if (digitalRead(TRIGGER_PIN)) {
      printf("----------down----------\n");
      digitalWrite(13, HIGH);
    }
    else {
      printf("----------up----------\n");
      digitalWrite(13, HIGH);
    }
  }

  void setup() {
    pinMode(13, OUTPUT);  // On-board LED
    pinMode(TRIGGER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), triggerAction, CHANGE);
  }

}

