#include "flow_controller_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>

#include <TaskManagerIO.h>

#include "Display.h"
#include "FlowMeterRenderer.h"

void setup() {
  Serial.begin(115200);
  Display::setup();
  setupMenu();
  renderer.setCustomDrawingHandler(&flowMeterRenderer);
  renderer.takeOverDisplay();
  switches.changeEncoderPrecision(80, 0);
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

void CALLBACK_FUNCTION onTalkConditionChange(int id) {
  // TODO - your menu change code
}

void CALLBACK_FUNCTION onTalkIntervalChange(int id) {
  // TODO - your menu change code
}

void CALLBACK_FUNCTION onTriggerModeChange(int id) {
  // TODO - your menu change code
}

void CALLBACK_FUNCTION onBackToWork(int id) {
  renderer.takeOverDisplay();
  switches.changeEncoderPrecision(80, 0);
  Display::drawBackground();
}



