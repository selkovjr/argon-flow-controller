#pragma once
#include "Arduino.h"

#define PRESSURE_SENSOR_PIN A0
#define P0_VOLTAGE 96
#define P60_VOLTAGE 555

namespace Pressure {
  extern float readKPa();
  extern float readPSI();
  extern void setup();
}
