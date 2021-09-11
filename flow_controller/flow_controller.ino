#include "LibPrintf.h"
#include "Fujikin.hpp"


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial1.begin(38400, SERIAL_8N1);  // SERIAL_8N1 is the default

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Fujikin::setup();
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // LED off
  delay(5);
  digitalWrite(LED_BUILTIN, LOW); // LED off

  Fujikin::sendFujikinQuery("Product Name");
  if (Fujikin::receivedFujikinResponse()) {
    printf("product name: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendFujikinQuery("Manufacturer Model Number");
  if (Fujikin::receivedFujikinResponse()) {
    printf("model number: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendFujikinQuery("Gas Identifier");
  if (Fujikin::receivedFujikinResponse()) {
    printf("gas: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendFujikinQuery("nProcess Gases");
  if (Fujikin::receivedFujikinResponse()) {
    printf("gases known: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendFujikinQuery("Gas CF");
  if (Fujikin::receivedFujikinResponse()) {
    printf("gas conversion factor: %f\n", Fujikin::decodeFloatBuffer());
  }

  byte b[1] = {0x01};
  Fujikin::sendFujikinCommand("Default Control Mode", b, 1);
  if (Fujikin::receivedFujikinCommandAck()) {
    printf("default control is digital\n");
  }
  b[0] = {0x01};
  Fujikin::sendFujikinCommand("Freeze Follow", b, 1);
  if (Fujikin::receivedFujikinCommandAck()) {
    printf("freeze follow disabled\n");
  }

  Fujikin::sendFujikinQuery("Freeze Follow");
  if (Fujikin::receivedFujikinResponse()) {
    printf("freeze follow: %x\n", Fujikin::decodeUint8Buffer());
  }

//  byte w[2] = {0x00, 0x60};
//  Fujikin::sendFujikinCommand("Setpoint", w, 2);
//  if (Fujikin::receivedFujikinCommandAck()) {
//    printf("setpoint sent\n");
//  }

  Fujikin::sendFujikinQuery("FM Status");
  if (Fujikin::receivedFujikinResponse()) {
    printf("flowmeter status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendFujikinQuery("FC Status");
  if (Fujikin::receivedFujikinResponse()) {
    printf("controller status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendFujikinQuery("Valve Status");
  if (Fujikin::receivedFujikinResponse()) {
    printf("valve status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendFujikinQuery("Valve Ramp Time");
  if (Fujikin::receivedFujikinResponse()) {
    printf("valve ramp time: %d\n", Fujikin::decodeUint32Buffer());
  }
  Fujikin::sendFujikinQuery("Setpoint");
  if (Fujikin::receivedFujikinResponse()) {
    printf("setpoint: %x\n", Fujikin::decodeUint16Buffer());
  }
  Fujikin::sendFujikinQuery("Filtered Setpoint");
  if (Fujikin::receivedFujikinResponse()) {
    printf("filtered setpoint: %x\n", Fujikin::decodeUint16Buffer());
  }
  Fujikin::sendFujikinQuery("Indicated Flow");
  if (Fujikin::receivedFujikinResponse()) {
    printf("indicated flow: %x\n", Fujikin::decodeUint16Buffer());
  }

  printf("----\n");

  delay(1000);
}
