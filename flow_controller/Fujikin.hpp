#pragma once

#include "Arduino.h"
#include "LibPrintf.h"

/*
** Fujikin.hpp
**

** This module interacts with a Fujikin mass flow controller, FCS-1000, and
** with the Max485 signal converter that relays serial communication between
** the flow controller and one of Arduino's UARTs. The hardware interface used
** to dirve the FCS-1000 in this application is a two-wire RS485 serial link.
** It can also be driven via an analog interface, with reduced functionality.
**
** The Max485 board has only two states: transmit and receive, controlled by
** a single wire. These states need to be co-ordinated with the flow controller's
** query-response cycle, so it didn't make much sense to create a separate
** Max485 module just to control a binary switch.
**
** This module has only been tested with FCS-T1000, but from a number of
** device descriptors it returns in response to ID queries, it appears that
** there are multiple Fujikin devices sharing the same protocol. If your
** device is different, contact customer support. They are very helpful.
**
** For the details of the protocol, see this this document in the doc folder:
**
**     tdf-ma-cu-m-002-9e_fcs_t1000_rs485_command_reference.pdf
**
** Note: the Fujikin protocol does not implement any error correction. The
** device requires and returns checksums with all commands and responses,
** allowing for data to be re-transmitted in the case of error.
**
** Re-transmission is currently not implemented in this module.
*/


/*
** Max485 wiring: Transmit Enable to D4
*/
#define TX_ENABLE_PIN 4


namespace Fujikin {

  // TEXT response payload
  extern char recvStringBuf[100];  // used in the caller; wrap access in a finction if feasible


  // Sets output mode on the Arduino pin controlling Transmit Enable on Max485.
  // Exposed in the interface to allow one-time initialization in the main setup()
  // function.
  void setUpMax485();


  // Sends a named write/state-change command to Fujikin and exits
  // immediately. This function is non-blocking; however, a subsequent
  // wait loop is necessary for catching ACK or NAK from Fujikin, which
  // arrives within 1ms.
  //
  // The wait loop runs inside receivedCommandAck().
  //
  // Example:
  //   byte b[1] = {0x01};
  //   Fujikin::sendCommand("Freeze Follow", b, 1);
  //   if (Fujikin::receivedCommandAck()) {
  //     printf("freeze follow disabled\n");
  //   }
  //
  void sendCommand(char *name, byte *data, int length);


  // If the receiver is not immediately available, this function waits for 2ms
  // before reading a single-byte response.
  //
  // Return: 1 for ACK, 0 for all other responses.
  int receivedCommandAck(void);


  // Sends a named read command to Fujikin and exits immediately. A subsequent
  // call to receivedResponse() will check for ACK and consume the response
  // from the UART, deopsiting it into a private receive buffer. That buffer
  // is then parsed by one of a set of accessor methods, appropriate for the
  // data type of the response.
  //
  // Example:
  //   Fujikin::sendQuery("Gas CF");
  //   if (Fujikin::receivedResponse()) {
  //     printf("gas conversion factor: %f\n", Fujikin::decodeFloatBuffer());
  //   }
  //
  void sendQuery(char *name);


  // Waits for the ACK + response sequence and stores the response as a raw buffer
  // and as a string. The string buffer recvStringBuf is available for immediate
  // consumption by the caller as soon as receivedResponse() returns 1. It is
  // exposed as a global namespace member, scoped as Fujikin::recvStringBuf.
  //
  // If the expected response is not a string, it needs to be parsed out of
  // the internal receive buffer with one of the decode methods listed below.
  //
  // Return: 1 when the query succeeds, 0 when it fails.
  int receivedResponse(void);


  // Extract a single byte from the receive buffer
  byte decodeUint8Buffer(void);


  // Parse a 16-bit word from the receive buffer
  uint16_t decodeUint16Buffer(void);


  // Parse a 32-bit word from the receive buffer
  uint32_t decodeUint32Buffer(void);


  // Parse a floating-point number from the receive buffer
  float decodeFloatBuffer(void);
}
