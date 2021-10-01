#pragma once
#include "flow_controller_menu.h"

#define TRIGGER_PIN 20

#define TRIGGER_OFF   0  // no activity

#define TRIGGER_T2_P  1  // pressed
#define TRIGGER_T2_R  2  // released; to be reset by timer to simulate ramp-down

#define TRIGGER_T4_P1 1  // first push
#define TRIGGER_T4_R1 2  // first release
#define TRIGGER_T4_P2 3  // second push
#define TRIGGER_T4_R2 0  // second release (same as off)

// these transitions can be modeled by (sate % 4) but we'll use these macros
// for clarity:
//
static uint8_t next_t4_state[] = {
  TRIGGER_T4_P1,  // TRIGGER_OFF -> TRIGGER_T4_P1
  TRIGGER_T4_R1,  // TRIGGER_T4_P1 -> TRIGGER_T4_R1
  TRIGGER_T4_P2,  // TRIGGER_T4_R1 -> TRIGGER_T4_P2
  TRIGGER_T4_R2   // TRIGGER_T4_P2 -> TRIGGER_T4_R2
};

namespace Trigger {
  extern char mode[3];
  extern uint8_t state;
  void setup();
  void setMode(int);
  void onTriggerActivity();
}
