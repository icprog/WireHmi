// WireHmi Backlight Test
// by epsilonrt <https://github.com/epsilonrt>

// Increases the LCD light every second still and always.

// Created 23 January 2018

// This example code is in the public domain.

#include <WireHmi.h>
#include <Toueris2Hmi.h>

//------------------------------------------------------------------------------
const unsigned pause = 1000;
const int ledPin = 13;

WireSlave slave (TOUERIS2_HMI_SLAVE_ADDR);
WireBackLight Backlight (&slave, BACKLIGHT_REG);

void setup() {
  int loops = 0;

  Serial.begin (500000);
  Serial.println("WireBackLight Class Test");
  
  // The LED is lit while waiting for the slave HMI
  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1);
  Wire.begin();
  while (!Backlight.begin()) {
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
  static byte backlight_write;
  byte backlight_read;
  bool success;

  Serial.print ("write>0x");
  success = Backlight.write(backlight_write);
  backlight_read = Backlight.read();
  Serial.print (backlight_read, HEX);
  if (success & (backlight_read == backlight_write)) {
    Serial.println (">Ok");
  }
  else {
    Serial.println (">Fail");
  }
  delay (pause);

  backlight_write += 8;
}
//------------------------------------------------------------------------------
