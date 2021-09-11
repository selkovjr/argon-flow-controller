#pragma once

#include "Arduino.h"
#include "LibPrintf.h"

namespace Fujikin {
  // TEXT response payload
  extern char recvStringBuf[100];  // used in the caller; wrap in a finction if feasible

  /*
  ** Interface
  */

  // Sets output mode on the Arduino pin controlling Transmit Enable on Max485.
  // Exposed to allow one-time setup in the main setup() function.
  void setUpMax485();


  void sendQuery(char *name);
  void sendCommand(char *name, byte *data, int length);
  int receivedCommandAck(void);
  int receivedResponse(void);

  byte decodeUint8Buffer(void);
  uint16_t decodeUint16Buffer(void);
  uint32_t decodeUint32Buffer(void);
  float decodeFloatBuffer(void);
}
