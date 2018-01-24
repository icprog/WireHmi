// PCF8583 RAM Test
// by epsilonrt <https://github.com/epsilonrt>

// write and read test in the RAM memory of a PCF8583 (I2C)

// Created 19 January 2018

// This example code is in the public domain.

#include <WireHmi.h>
#include <Toueris2Hmi.h>

#define STRLEN      8
#define RAMSIZE     256

//------------------------------------------------------------------------------
const int ledPin = 13;

WireSlave ram (0xA0 >> 1);

void setup() {

  Serial.begin (500000);
  Serial.println("WireSlave Class Test");
  pinMode (ledPin, OUTPUT);
  for (byte j = 0; j < 3; j++) {

    digitalWrite (ledPin, 1);
    delay (200);
    digitalWrite (ledPin, 0);
    delay (200);
  }
  digitalWrite (ledPin, 1);
  delay (2000);
  Wire.begin();
  digitalWrite (ledPin, 0);
}

void loop() {
  byte len;
  static byte dataAddress;
  static char txBuf[STRLEN + 1];
  static char rxBuf[STRLEN + 1];
  static char c = 'A';

  if (dataAddress >= RAMSIZE) {
    dataAddress = 0;
  }

  // filling transmit buffer
  for (int i = 0; i < STRLEN; i++) {
    if (c > 'Z') {
      c = 'A';
    }
    txBuf[i] = c++;
  }

  Serial.write ('S');
  Serial.print (dataAddress, HEX);
  Serial.write ('>');
  Serial.print (txBuf);

  if (ram.write (dataAddress, (const byte *) txBuf, STRLEN)) {
    Serial.println (">Ok");
  }
  else {
    Serial.println (">Fail");
  }

  len = ram.read (dataAddress, (byte *) rxBuf, STRLEN);
  rxBuf[len] = 0;

  Serial.write ('R');
  Serial.print (dataAddress, HEX);
  Serial.write ('>');
  Serial.print (rxBuf);
  if (strcmp (rxBuf, txBuf) == 0) {
    Serial.println (">Ok");
  }
  else {
    Serial.println (">Fail");
  }

  dataAddress += STRLEN;

  delay (1000);
}
//------------------------------------------------------------------------------
