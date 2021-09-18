#include "flow_controller_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>

#include <TaskManagerIO.h>

#include "Display.h"
#include "FlowMeterRenderer.h"

void setup() {
  Display::setup();
  setupMenu();
  renderer.setCustomDrawingHandler(&flowMeterRenderer);
  renderer.takeOverDisplay();
  switches.changeEncoderPrecision(30, 8);
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
  switches.changeEncoderPrecision(30, 8);
  Display::drawBackground();
}



