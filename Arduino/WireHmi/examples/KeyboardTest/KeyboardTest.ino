// WireHmi Keyb Test
// by epsilonrt <https://github.com/epsilonrt>

// Prints the keys pressed (Px) and released (Rx) on the serial port.

// Created 23 January 2018

// This example code is in the public domain.

#include <WireHmi.h>
#include <Toueris2Hmi.h>

//------------------------------------------------------------------------------
const unsigned pause = 1000;
const int hirqPin = 2;
const int ledPin = 13;

WireSlave slave (TOUERIS2_HMI_SLAVE_ADDR);
WireKeyboard Keyb (&slave, BUT_REG, hirqPin);

void setup() {

  Serial.begin (500000);
  Serial.println("WireKeyboard Class Test");
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
  Keyb.begin();
  digitalWrite (ledPin, 0);
}

void loop() {

  if (Keyb.available()) {
    byte key = Keyb.key();
    
    if (Keyb.released()) {
      Serial.write('R');
    }
    else {
      
      Serial.write('P');
    }
    Serial.println(key);
  }
}
//------------------------------------------------------------------------------
