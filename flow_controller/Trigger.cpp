#include "Arduino.h"
#include "Trigger.h"

namespace Trigger {
  uint8_t state = TRIGGER_OFF;
  char mode[3];

  void onTriggerActivity() {
    if (digitalRead(TRIGGER_PIN)) {
      Serial.println("down");
      if (strcmp(mode, "T4") == 0) {
        digitalWrite(13, HIGH);
        state = next_t4_state[state];
      }
    }
    else {
      Serial.println("up");
      if (strcmp(mode, "T4") == 0) {
        digitalWrite(13, LOW);
        state = next_t4_state[state];
      }
    }
  }

  void setup() {
    pinMode(13, OUTPUT);  // On-board LED
    pinMode(TRIGGER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), onTriggerActivity, CHANGE);
  }

  // Sets mode from the menu
  void setMode(int id) {
    menuTriggerMode.copyEnumStrToBuffer(mode, 3, menuTriggerMode.getCurrentValue());
  }
}

