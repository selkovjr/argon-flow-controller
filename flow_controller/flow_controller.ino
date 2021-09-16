#include "flow_controller_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>

#include <TaskManagerIO.h>

#include "Display.h"

#define SCREEN_WIDTH 128 //pixel width
#define SCREEN_HEIGHT 128 //pixel height

void setup() {
  // display.setFont(&FreeSansOblique12pt7b);
  display.begin();
  display.setRotation(2);
  display.fillScreen(BLACK);

  setupMenu();
}

void loop() {
  taskManager.runLoop();
}


void CALLBACK_FUNCTION onModeChange(int id) {
    // TODO - your menu change code
}

void CALLBACK_FUNCTION onWarningLevelChange(int id) {
    // TODO - your menu change code
}

void CALLBACK_FUNCTION onCutOffLevelChange(int id) {
    // TODO - your menu change code
}

void CALLBACK_FUNCTION onTalkEnableChange(int id) {
    // TODO - your menu change code
}

void CALLBACK_FUNCTION onTalkIntervalChange(int id) {
    // TODO - your menu change code
}



void CALLBACK_FUNCTION onTriggerModeChange(int id) {
    // TODO - your menu change code
}
