#pragma once

#include "Arduino.h"
#include "LibPrintf.h"

namespace Fujikin {
  // TEXT response payload
  extern char recvStringBuf[100];  // used in the caller; wrap in a finction if feasible

  // Max485 wiring
  const byte TX_ENABLE_PIN = 4;  // D4

  /*
  ** Interface
  */

  void setUpMax485();


  void sendFujikinQuery(char *name);
  void sendFujikinCommand(char *name, byte *data, int length);
  byte decodeUint8Buffer(void);
  uint16_t decodeUint16Buffer(void);
  uint32_t decodeUint32Buffer(void);
  float decodeFloatBuffer(void);

  int receivedFujikinCommandAck(void);


  int receivedFujikinResponse(void);
}
