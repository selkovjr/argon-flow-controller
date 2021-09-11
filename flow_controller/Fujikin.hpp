#pragma once

#include "Arduino.h"
#include "LibPrintf.h"

/*
** Default network address (we won't change it)
*/
#define FUJIKIN_MAC            0x21

/*
** Serial start of text
*/
#define STX                    0x02


/*
** Fujikin protocol identifiers
*/

//   1. Direction
#define READ_COMMAND           0x80
#define WRITE_COMMAND          0x81

//   2. Message class
#define IDENTITY_CLASS         0x01
#define NETWORK_CLASS          0x03
#define DEVICE_MANAGER_CLASS   0x64
#define EXCEPTION_CLASS        0x65
#define GAS_CAIBRATION_CLASS   0x66
#define FLOW_METER_CLASS       0x68
#define FLOW_CONTROLLER_CLASS  0x69
#define VALVE_DRIVER_CLASS     0x6a

//   3. Instance
#define INST0 0x00  // Only two commands are INST0; the rest are INST1
#define INST1 0x01

//   4. Attribute access
#define R  0x01
#define W  0x02
#define RW 0x03

//   5. Attribute storage
#define NA  0x00   // not applicable
#define V   0x01   // volatile
#define NV  0x02   // non-volatile

//   5. Attribute type
#define UINT8  0x01
#define UINT16 0x02
#define UINT32 0x04
#define REAL   0x08
#define TEXT   0x10
#define DATE   0x10

namespace Fujikin {
  // TEXT response payload
  extern char recvStringBuf[100];  // used in the caller

  // Max485 wiring
  const byte TX_ENABLE_PIN = 4;


  // Command definitions
  typedef struct {
    char *name;
    byte access;
    byte storage;
    byte cls;
    byte inst;
    byte attr;
    byte dt;
  } FujikinCommand;

#define NCOMMANDS 78
  const FujikinCommand comdata[NCOMMANDS] = {
    { "Vender ID",                              R, NA,  IDENTITY_CLASS,        INST1, 0x01, UINT16 },
    { "Product Type",                           R, NA,  IDENTITY_CLASS,        INST1, 0x02, UINT16 },
    { "Product Code",                           R, NA,  IDENTITY_CLASS,        INST1, 0x03, UINT16 },
    { "Revision",                               R, NA,  IDENTITY_CLASS,        INST1, 0x04, UINT16 },
    { "Product Name",                           R, NA,  IDENTITY_CLASS,        INST1, 0x07,   TEXT },
    { "Reset",                                  W, NA,  IDENTITY_CLASS,        INST1, 0xc7,  UINT8 },

    { "MAC ID",                                RW, NV,  NETWORK_CLASS,         INST1, 0x01,  UINT8 },
    { "Baud Rate",                             RW, NV,  NETWORK_CLASS,         INST1, 0x02,  UINT8 },

    { "Device Type",                            R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x01,   TEXT },
    { "Device Manufacturer Identity",           R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x03,   TEXT },
    { "Manufacturer Model Number",              R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x04,   TEXT },
    { "Firmware Revision",                      R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x05,   TEXT },
    { "Hardware Revision",                      R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x06,   TEXT },
    { "Serial Number",                          R, NA,  DEVICE_MANAGER_CLASS,  INST1, 0x07,   TEXT },

    { "Exception Status",                       R, NA,  EXCEPTION_CLASS,       INST1, 0xa0,  UINT8 },
    { "Occurred Alarm Details",                 R, NA,  EXCEPTION_CLASS,       INST1, 0xa1, UINT16 },
    { "Occurred Warning Details",               R, NA,  EXCEPTION_CLASS,       INST1, 0xa2, UINT16 },
    { "Flow Totalizer Alarm Enable/Disable",   RW, NV,  EXCEPTION_CLASS,       INST1, 0xb5,  UINT8 },
    { "Flow Totalizer Alarm Level",            RW, NV,  EXCEPTION_CLASS,       INST1, 0xb6, UINT32 },
    { "Flow Totalizer Warning Enable/Disable", RW, NV,  EXCEPTION_CLASS,       INST1, 0xb7,  UINT8 },
    { "Flow Totalizer Warning Level",          RW, NV,  EXCEPTION_CLASS,       INST1, 0xb8, UINT32 },

    { "Calibration Instance",                   R, NA,  GAS_CAIBRATION_CLASS,  INST0, 0x65,  UINT8 },
    { "nProcess Gases",                         R, NA,  GAS_CAIBRATION_CLASS,  INST0, 0xa0,  UINT8 },
    { "Gas Identifier",                         R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x01,   TEXT },
    { "Full Scale Range",                       R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x02, UINT16 },
    { "Flow Units",                             R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x03,   TEXT },
    { "Reference Temperature",                  R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x04, UINT16 },
    { "Reference Pressure",                     R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x05, UINT16 },
    { "Calibration Date",                       R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x09,   DATE },
    { "Gas STD No",                             R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x10, UINT16 },
    { "Gas CF",                                 R, NA,  GAS_CAIBRATION_CLASS,  INST1, 0x17,   REAL },

    { "FM Status",                              R, NA,  FLOW_METER_CLASS,      INST1, 0x07,  UINT8 },
    { "FM Alarm Enable/Disable",               RW, NV,  FLOW_METER_CLASS,      INST1, 0x08,  UINT8 },
    { "FM Warning Enable/Disable",             RW, NV,  FLOW_METER_CLASS,      INST1, 0x09,  UINT8 },
    { "FM Alarm Trip Point High",              RW, NV,  FLOW_METER_CLASS,      INST1, 0x11, UINT16 },
    { "FM Alarm Trip Point Low",               RW, NV,  FLOW_METER_CLASS,      INST1, 0x12, UINT16 },
    { "FM Alarm Trip Hysteresis",              RW, NV,  FLOW_METER_CLASS,      INST1, 0x13, UINT16 },
    { "FM Alarm Settling Time",                RW, NV,  FLOW_METER_CLASS,      INST1, 0x14, UINT16 },
    { "FM Warning Trip Point High",            RW, NV,  FLOW_METER_CLASS,      INST1, 0x15, UINT16 },
    { "FM Warning Trip Point Low",             RW, NV,  FLOW_METER_CLASS,      INST1, 0x16, UINT16 },
    { "FM Warning Trip Hysteresis",            RW, NV,  FLOW_METER_CLASS,      INST1, 0x17, UINT16 },
    { "FM Warning Settling Time",              RW, NV,  FLOW_METER_CLASS,      INST1, 0x18, UINT16 },
    { "Zero Enable/Disable",                   RW, NV,  FLOW_METER_CLASS,      INST1, 0xa5,  UINT8 },
    { "Flow Totalizer Enable/Disable",         RW, NV,  FLOW_METER_CLASS,      INST1, 0xb0,  UINT8 },
    { "Flow Totalizer Data",                    R, NA,  FLOW_METER_CLASS,      INST1, 0xb2, UINT32 },
    { "Flow Totalizer Time1",                   R, NA,  FLOW_METER_CLASS,      INST1, 0xb3, UINT32 },
    { "Flow Totalizer Time2",                   R, NA,  FLOW_METER_CLASS,      INST1, 0xb4, UINT32 },
    { "Requested Zero",                        RW, NA,  FLOW_METER_CLASS,      INST1, 0xba,  UINT8 },

    { "Control Mode Selection",                RW,  V,  FLOW_CONTROLLER_CLASS, INST1, 0x03,  UINT8 },
    { "Default Control Mode",                  RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x04,  UINT8 },
    { "Freeze Follow",                         RW,  V,  FLOW_CONTROLLER_CLASS, INST1, 0x05,  UINT8 },
    { "FC Status",                              R, NA,  FLOW_CONTROLLER_CLASS, INST1, 0x0a,  UINT8 },
    { "FC Alarm Enable/Disable",               RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x0b,  UINT8 },
    { "FC Warning Enable/Disable",             RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x0c,  UINT8 },
    { "FC Alarm Settling Time",                RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x0d, UINT16 },
    { "FC Alarm Error Band",                   RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x0e, UINT16 },
    { "FC Warning Settling Time",              RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x0f, UINT16 },
    { "FC Warning Error Band",                 RW, NV,  FLOW_CONTROLLER_CLASS, INST1, 0x10, UINT16 },
    { "Setpoint",                              RW,  V,  FLOW_CONTROLLER_CLASS, INST1, 0xa4, UINT16 },

    { "Valve Override",                        RW,  V,  VALVE_DRIVER_CLASS,    INST1, 0x01,  UINT8 },
    { "Valve Status",                           R, NA,  VALVE_DRIVER_CLASS,    INST1, 0x07,  UINT8 },
    { "Valve Alarm Enable/Disable",            RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x08,  UINT8 },
    { "Valve Warning Enable/Disable",          RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x09,  UINT8 },
    { "Valve Alarm Trip Point High",           RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x0f, UINT16 },
    { "Valve Alarm Trip Point Low",            RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x10, UINT16 },
    { "Valve Alarm Trip Hysteresis",           RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x11, UINT16 },
    { "Valve Warning Trip Point High",         RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x12, UINT16 },
    { "Valve Warning Trip Point Low",          RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x13, UINT16 },
    { "Valve Warning Trip Hysteresis",         RW, NV,  VALVE_DRIVER_CLASS,    INST1, 0x14, UINT16 },
    { "Valve Type",                             R, NA,  VALVE_DRIVER_CLASS,    INST1, 0xa0,  UINT8 },
    { "Valve Ramp Time",                       RW, NA,  VALVE_DRIVER_CLASS,    INST1, 0xa4, UINT32 },
    { "Filtered Setpoint",                      R, NA,  VALVE_DRIVER_CLASS,    INST1, 0xa6, UINT16 },
    { "Indicated Flow",                         R, NA,  VALVE_DRIVER_CLASS,    INST1, 0xa9, UINT16 },
    { "Valve Voltage",                          R, NA,  VALVE_DRIVER_CLASS,    INST1, 0xb6, UINT16 }
  };



  void setup();
  FujikinCommand comspec(char *name);
  void sendFujikinQuery(char *name);
  void sendFujikinCommand(char *name, byte *data, int length);
  byte decodeUint8Buffer(void);
  uint16_t decodeUint16Buffer(void);
  uint32_t decodeUint32Buffer(void);
  float decodeFloatBuffer(void);

  int receivedFujikinCommandAck(void);


  int receivedFujikinResponse(void);
}
