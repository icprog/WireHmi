// WireHmi Led Test
// by epsilonrt <https://github.com/epsilonrt>

// Reads, switch on, switch off and toggle all leds then turn on each led,
// then turn off each led.

// Created 19 January 2018

// This example code is in the public domain.

#include <WireHmi.h>
#include <Toueris2Hmi.h>

//------------------------------------------------------------------------------
const unsigned pause = 1000;
const int ledPin = 13;

WireSlave slave (TOUERIS2_HMI_SLAVE_ADDR);
WireLeds Led (&slave, LED_REG, LED_NB);

void setup() {
  int loops = 0;

  Serial.begin (38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println ("WireLeds Class Test");

  // The LED is lit while waiting for the slave HMI
  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1);
  Wire.begin();
  while (!Led.begin()) {
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

void verify (int i) {
  if (i) {
    Serial.println (">Ok");
  }
  else {
    Serial.println (">Fail");
  }
}

void loop() {
  byte led, all;
  bool b1, b2;
  //return;

  Serial.print ("readAll>0x");
  all = Led.readAll();
  Serial.print (all, HEX);
  verify (all == 0);
  delay (pause);

  Serial.print ("writeAll>0x");
  b1 = Led.writeAll();
  all = Led.readAll();
  Serial.print (all, HEX);
  verify (b1 & (all == Led.all()));
  delay (pause);

  Serial.print ("toggleAll>0x");
  b1 = Led.toggleAll();
  all = Led.readAll();
  Serial.print (all, HEX);
  verify (b1 & (all == 0));
  delay (pause);

  Serial.print ("toggleAll>0x");
  b1 = Led.toggleAll();
  all = Led.readAll();
  Serial.print (all, HEX);
  verify (b1 & (all == Led.all()));
  delay (pause);

  Serial.print ("writeAll>0x");
  b1 = Led.writeAll (0);
  all = Led.readAll();
  Serial.print (all, HEX);
  verify (b1 & (all == 0));
  delay (pause);

  for (led = 0; led < LED_NB; led++) {

    Serial.write ('S');
    Serial.print (led);
    b1 = Led.set (led);
    b2 = Led.get (led);
    verify (b1 && b2);
    delay (pause);
  }

  for (led = 0; led < LED_NB; led++) {

    Serial.write ('C');
    Serial.print (led);
    b1 = Led.clear (led);
    b2 = Led.get (led);
    verify (b1 && !b2);
    delay (pause);
  }

  for (led = 0; led < LED_NB; led++) {

    Serial.write ('T');
    Serial.print (led);
    b1 = Led.toggle (led);
    b2 = Led.get (led);
    verify (b1 && b2);
    delay (pause);
  }

  for (led = 0; led < LED_NB; led++) {

    Serial.write ('T');
    Serial.print (led);
    b1 = Led.toggle (led);
    b2 = Led.get (led);
    verify (b1 && !b2);
    delay (pause);
  }

  delay (pause * 3);
}
//------------------------------------------------------------------------------
