// PCF8583 RAM Test
// by epsilonrt <https://github.com/epsilonrt>

// write and read test in the RAM memory of a PCF8583 (I2C)

// Created 19 January 2018

// This example code is in the public domain.

#include <WireHmi.h>

//------------------------------------------------------------------------------
// IHM Toueris II 
#define IHM_ID 0b0111111

#define LED_REG 0
#define LED_NB  3
#define LED1  (1<<0)
#define LED2  (1<<1)
#define LED3  (1<<2)

#define PWM_REG 1

#define BUT_REG 2
#define BUT_NB  5
#define BUT_RELEASE (1<<7)
#define BUT_UP      1
#define BUT_DOWN    2
#define BUT_LEFT    3
#define BUT_RIGHT   4
#define BUT_CENTER  5

//------------------------------------------------------------------------------
#define STRLEN      8
#define RAMSIZE     256

WireSlave ram (0xA0 >> 1);

void setup() {

  Serial.begin (500000);
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop() {
  byte len;
  static byte dataAddress;
  static char txBuf[STRLEN + 1];
  static char rxBuf[STRLEN + 1];
  static char c = 'A';
  //return;

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
