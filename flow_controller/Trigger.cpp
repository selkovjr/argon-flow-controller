#include "Arduino.h"
#include "Trigger.h"

namespace Trigger {
  uint8_t state = TRIGGER_OFF;
  char mode[3] = "T2";

  void onTriggerActivity() {
    if (!digitalRead(TRIGGER_PIN)) {
      Serial.print(mode);
      Serial.print("down ");
      digitalWrite(13, HIGH);
      if (strcmp(mode, "T2") == 0) {
        Serial.println("T2");
        state = TRIGGER_T2_P;
      }
      if (strcmp(mode, "T4") == 0) {
        Serial.println("T4");
        state = next_t4_state[state];
      }
    }
    else {
      Serial.println("up ");
      if (strcmp(mode, "T2") == 0) {
        Serial.println("T2");
        state = TRIGGER_T2_R;
        // Let the menu return to TRIGGER_OFF after a couple cycles
      }
      if (strcmp(mode, "T4") == 0) {
        Serial.println("T4");
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
    Serial.println("setting mode");
    Serial.println(menuTriggerMode.getCurrentValue());
    menuTriggerMode.copyEnumStrToBuffer(mode, 3, menuTriggerMode.getCurrentValue());
  }
}
