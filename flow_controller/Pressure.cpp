#include "Pressure.h"

namespace Pressure {
  float readPSI() {
    int p = analogRead(PRESSURE_SENSOR_PIN);
    return 60.0 * (p - P0_VOLTAGE) / (P60_VOLTAGE - P0_VOLTAGE);
  }

  float readKPa() {
    return 6.89476 * readPSI();
  }

  void setup() {
    analogReference(DEFAULT);
  }
}
