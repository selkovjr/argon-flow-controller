#include "Fujikin.hpp"

namespace Fujikin {

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


  void setup() {
    pinMode(TX_ENABLE_PIN, OUTPUT);  // DE / RE Controling pin of RS-485
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
