// Toueris II IHM Led Test
// by epsilonrt <https://github.com/epsilonrt>

// Turn on each led, then turn off each led.

// Created 19 January 2018

// This example code is in the public domain.

#include <WireHmi.h>
#include <Toueris2Hmi.h>

WireSlave slave (IHM_ID);
WireLeds Led (&slave, LED_REG, LED_NB);
const unsigned pause = 1000;

void setup() {

  Serial.begin (500000);
  Wire.begin(); // join i2c bus (address optional for master)
  Led.begin();
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
  b1 = Led.writeAll(0);
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

  delay (pause*3);
}
//------------------------------------------------------------------------------
