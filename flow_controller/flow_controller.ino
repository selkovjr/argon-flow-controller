#include "LibPrintf.h"
#include "Fujikin.hpp"


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial1.begin(38400, SERIAL_8N1);  // SERIAL_8N1 is the default

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // DE / RE Controling pin of RS-485
  pinMode(TX_ENABLE_PIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // LED off
  delay(5);
  digitalWrite(LED_BUILTIN, LOW); // LED off

  sendFujikinQuery("Product Name");
  if (receivedFujikinResponse()) {
    printf("product name: %s\n", recvStringBuf);
  }
  sendFujikinQuery("Manufacturer Model Number");
  if (receivedFujikinResponse()) {
    printf("model number: %s\n", recvStringBuf);
  }
  sendFujikinQuery("Gas Identifier");
  if (receivedFujikinResponse()) {
    printf("gas: %s\n", recvStringBuf);
  }
  sendFujikinQuery("nProcess Gases");
  if (receivedFujikinResponse()) {
    printf("gases known: %d\n", decodeUint8Buffer());
  }
  sendFujikinQuery("Gas CF");
  if (receivedFujikinResponse()) {
    printf("gas conversion factor: %f\n", decodeFloatBuffer());
  }

  byte b[1] = {0x01};
  sendFujikinCommand("Default Control Mode", b, 1);
  if (receivedFujikinCommandAck()) {
    printf("default control is digital\n");
  }
  b[0] = {0x01};
  sendFujikinCommand("Freeze Follow", b, 1);
  if (receivedFujikinCommandAck()) {
    printf("freeze follow disabled\n");
  }

  sendFujikinQuery("Freeze Follow");
  if (receivedFujikinResponse()) {
    printf("freeze follow: %x\n", decodeUint8Buffer());
  }

//  byte w[2] = {0x00, 0x60};
//  sendFujikinCommand("Setpoint", w, 2);
//  if (receivedFujikinCommandAck()) {
//    printf("setpoint sent\n");
//  }

  sendFujikinQuery("FM Status");
  if (receivedFujikinResponse()) {
    printf("flowmeter status: %d\n", decodeUint8Buffer());
  }
  sendFujikinQuery("FC Status");
  if (receivedFujikinResponse()) {
    printf("controller status: %d\n", decodeUint8Buffer());
  }
  sendFujikinQuery("Valve Status");
  if (receivedFujikinResponse()) {
    printf("valve status: %d\n", decodeUint8Buffer());
  }
  sendFujikinQuery("Valve Ramp Time");
  if (receivedFujikinResponse()) {
    printf("valve ramp time: %d\n", decodeUint32Buffer());
  }
  sendFujikinQuery("Setpoint");
  if (receivedFujikinResponse()) {
    printf("setpoint: %x\n", decodeUint16Buffer());
  }
  sendFujikinQuery("Filtered Setpoint");
  if (receivedFujikinResponse()) {
    printf("filtered setpoint: %x\n", decodeUint16Buffer());
  }
  sendFujikinQuery("Indicated Flow");
  if (receivedFujikinResponse()) {
    printf("indicated flow: %x\n", decodeUint16Buffer());
  }

  printf("----\n");

  delay(1000);
}
