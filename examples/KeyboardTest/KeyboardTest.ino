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
  int loops = 0;

  Serial.begin (38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("WireKeyboard Class Test");
  
  // The LED is lit while waiting for the slave HMI
  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1);
  Wire.begin();
  while (!Keyb.begin()) {
    loops++; // One waiting loop per second
  }
  digitalWrite (ledPin, 0);
  
  // The led flashes to inform the number of waiting loops
  for (byte j = 0; j < loops; j++) {

    digitalWrite (ledPin, 1);
    delay (200);
    digitalWrite (ledPin, 0);
    delay (200);
  }
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
