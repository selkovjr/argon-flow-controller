#include "LibPrintf.h"
#include "Fujikin.hpp"


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial1.begin(38400, SERIAL_8N1);  // SERIAL_8N1 is the default. It works with Fujikin.

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Fujikin::setUpMax485();
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // LED off
  delay(5);
  digitalWrite(LED_BUILTIN, LOW); // LED off

  Fujikin::sendQuery("Product Name");
  if (Fujikin::receivedResponse()) {
    printf("product name: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendQuery("Manufacturer Model Number");
  if (Fujikin::receivedResponse()) {
    printf("model number: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendQuery("Gas Identifier");
  if (Fujikin::receivedResponse()) {
    printf("gas: %s\n", Fujikin::recvStringBuf);
  }
  Fujikin::sendQuery("nProcess Gases");
  if (Fujikin::receivedResponse()) {
    printf("gases known: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendQuery("Gas CF");
  if (Fujikin::receivedResponse()) {
    printf("gas conversion factor: %f\n", Fujikin::decodeFloatBuffer());
  }

  byte b[1] = {0x01};
  Fujikin::sendCommand("Default Control Mode", b, 1);
  if (Fujikin::receivedCommandAck()) {
    printf("default control is digital\n");
  }
  b[0] = {0x01};
  Fujikin::sendCommand("Freeze Follow", b, 1);
  if (Fujikin::receivedCommandAck()) {
    printf("freeze follow disabled\n");
  }

  Fujikin::sendQuery("Freeze Follow");
  if (Fujikin::receivedResponse()) {
    printf("freeze follow: %x\n", Fujikin::decodeUint8Buffer());
  }

//  byte w[2] = {0x00, 0x60};
//  Fujikin::sendCommand("Setpoint", w, 2);
//  if (Fujikin::receivedCommandAck()) {
//    printf("setpoint sent\n");
//  }

  Fujikin::sendQuery("FM Status");
  if (Fujikin::receivedResponse()) {
    printf("flowmeter status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendQuery("FC Status");
  if (Fujikin::receivedResponse()) {
    printf("controller status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendQuery("Valve Status");
  if (Fujikin::receivedResponse()) {
    printf("valve status: %d\n", Fujikin::decodeUint8Buffer());
  }
  Fujikin::sendQuery("Valve Ramp Time");
  if (Fujikin::receivedResponse()) {
    printf("valve ramp time: %d\n", Fujikin::decodeUint32Buffer());
  }
  Fujikin::sendQuery("Setpoint");
  if (Fujikin::receivedResponse()) {
    printf("setpoint: %x\n", Fujikin::decodeUint16Buffer());
  }
  Fujikin::sendQuery("Filtered Setpoint");
  if (Fujikin::receivedResponse()) {
    printf("filtered setpoint: %x\n", Fujikin::decodeUint16Buffer());
  }
  Fujikin::sendQuery("Indicated Flow");
  if (Fujikin::receivedResponse()) {
    printf("indicated flow: %x\n", Fujikin::decodeUint16Buffer());
  }

  printf("----\n");

  delay(1000);
}
