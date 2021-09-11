#include "Fujikin.hpp"

/*
** Default network address (we won't change it)
*/
#define FUJIKIN_MAC            0x21

/*
** Start of text (serial protocol)
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

//   6. Attribute type
#define UINT8  0x01
#define UINT16 0x02
#define UINT32 0x04
#define REAL   0x08
#define TEXT   0x10
#define DATE   0x10


namespace Fujikin {
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


  // transmit buffer
  byte outBuf [20] = {0};

  // response buffer
  byte recvBuf [100] = {0};

  // TEXT response payload
  char recvStringBuf [100] = {0};

  // UINT8 response payload
  byte recvUint8;

  // UINT32 response payload
  union uint32_u {
    byte b[4];
    uint32_t val;
  } recvUint32;

  // REAL response payload
  union float_u {
    byte b[4];
    float val;
  } recvFloat;


  void setUpMax485() {
    pinMode(TX_ENABLE_PIN, OUTPUT);  // DE / RE Controling pin of RS-485
  }

  // Looks up command data by name. Provides a crude human-readable intreface
  // to Fujikin protocol buffers. The definitions are stored in comdata[] above.
  FujikinCommand comspec(char *name) {
    for (int i = 0; i < NCOMMANDS; i++) {
      if (strcmp(comdata[i].name, name) == 0) {
        return comdata[i];
      }
    }
    printf("can't find attribute named '%s'\n", name);
    return {"unknown", 0, 0, 0, 0, 0, 0};
  }

  void sendFujikinQuery(char *name) {
    FujikinCommand spec = comspec(name);

    if (spec.access == W) {
      printf("sendFujikinQuery: '%s' is a write-only command\n", spec.name);
      return;
    }

    byte bufSize = 0;
    outBuf[0] = FUJIKIN_MAC;   ++bufSize;
    outBuf[1] = STX;           ++bufSize;
    outBuf[2] = READ_COMMAND;  ++bufSize;
    outBuf[3] = 0x03;          ++bufSize;  // packet length
    outBuf[4] = spec.cls;      ++bufSize;
    outBuf[5] = spec.inst;     ++bufSize;
    outBuf[6] = spec.attr;     ++bufSize;

    byte checksum = 0;
    for (int i = 1; i < bufSize; i++) checksum += outBuf[i];

    outBuf[7] = 0x00;          ++bufSize;  // padding (end of data)
    outBuf[8] = checksum;      ++bufSize;

    digitalWrite (TX_ENABLE_PIN, HIGH);  // enable sending
    Serial1.write(outBuf, bufSize);
    Serial1.flush ();  // Waits for the transmission of outgoing serial data to complete
    digitalWrite (TX_ENABLE_PIN, LOW);  // start receiving

    while (!Serial1.available()) {}  // block until Fujikin responds
  }


  int receivedFujikinCommandAck(void) {
    if (Serial1.available()) {
      byte b = Serial1.read();
      if (b == 0x06) {
        delay (2);
        if (Serial1.available()) {
          byte b = Serial1.read();
          if (b == 0x06) {
            return 1;
          }
        }
        else if (b == 0x16) {
          printf ("Write NACK\n");
          delay(5000);
          return 0;
        }
        else {
          printf ("  unexpected write result code: %d\n", b);
          delay(5000);
          return 0;
        }
      }
      else if (b == 0x16) {
        printf ("NACK\n");
        delay(5000);
        return 0;
      }
      else {
        printf ("  unexpected handshake code: %d\n", b);
        delay(5000);
        return 0;
      }
    }

    else {
      printf ("No response after 2ms\n");
      delay(5000);
      return 0;
    }
  }


  void sendFujikinCommand(char *name, byte *data, int length) {
    FujikinCommand spec = comspec(name);

    if (spec.access == R) {
      printf("sendFujikinCommand: '%s' is a write-only command\n", spec.name);
      return;
    }

    byte bufSize = 0;
    outBuf[bufSize++] = FUJIKIN_MAC;
    outBuf[bufSize++] = STX;
    outBuf[bufSize++] = WRITE_COMMAND;
    outBuf[bufSize++] = length + 3;    // packet length: data + class, instance, and attribute
    outBuf[bufSize++] = spec.cls;
    outBuf[bufSize++] = spec.inst;
    outBuf[bufSize++] = spec.attr;

    for (int i = 0; i < length; i++) {
      outBuf[bufSize++] = data[i];
    }
    outBuf[bufSize++] = 0x00;         // padding (end of data)

    byte checksum = 0;
    for (int i = 1; i < bufSize; i++) checksum += outBuf[i];
    outBuf[bufSize++] = checksum;

    digitalWrite (TX_ENABLE_PIN, HIGH);  // enable sending
    Serial1.write(outBuf, bufSize);
    Serial1.flush ();  // Waits for the transmission of outgoing serial data to complete
    digitalWrite (TX_ENABLE_PIN, LOW);  // start receiving

    while (!Serial1.available()) {}  // block until Fujikin responds
  }


  int receivedFujikinResponse(void) {
    byte* p = recvBuf;
    int i;

    memset(recvBuf, 0, sizeof(recvBuf));

    if (Serial1.available()) {
      byte b = Serial1.read();
      if (b == 0x06) {
        delay (2);
        while (Serial1.available()) {
          byte b = Serial1.read();
          *p++ = b;
          delayMicroseconds(500);
          // printf ("  byte: %x %c\n", b, b);
        }

        // Parse the receive buffer
        if (recvBuf[0] != 0x00) {
          printf("this message is not for me: %s\n", recvBuf);
          return 0;
        }
        if (recvBuf[1] != 0x02) {
          printf("recieve buffer corrupt; no STX at [1]: %s\n", recvBuf[1]);
          return 0;
        }
        if (recvBuf[2] != 0x80) {
          printf("recieve buffer corrupt; not responding to a read command at [2]: %s\n", recvBuf[1]);
          return 0;
        }

        int length = (int)(byte)recvBuf[3];
        // printf("packet length: %d\n", length);

        // recvBuf[4], recvBuf[5], recvBuf[6]: class, instance, attribute

        for (p = recvBuf + 7, i = 0; i <= length - 3; p++, i++) {
          recvStringBuf[i] = *p;
        }
        recvStringBuf[i] = 0;
        return 1;
      }

      else if (b == 0x16) {
        printf ("NACK\n");
        delay(5000);
        return 0;
      }

      else {
        printf ("  unexpected handshake code: %d\n", b);
        delay(5000);
        return 0;
      }
    }
    else {
      printf ("No response after 2ms\n");
      delay(5000);
      return 0;
    }
  }


  byte decodeUint8Buffer(void) {
    return recvBuf[7];
  }

  uint16_t decodeUint16Buffer(void) {
    return (uint16_t)recvBuf[7] + 256 * (uint16_t)recvBuf[8];
  }

  uint32_t decodeUint32Buffer(void) {
    for (int i = 0; i < 4; i++) {
      recvUint32.b[i] = recvBuf[7 + i];
    }
    return recvUint32.val;
  }

  float decodeFloatBuffer(void) {
    for (int i = 0; i < 4; i++) {
      recvFloat.b[i] = recvBuf[7 + i];
    }
    return recvFloat.val;
  }

}
