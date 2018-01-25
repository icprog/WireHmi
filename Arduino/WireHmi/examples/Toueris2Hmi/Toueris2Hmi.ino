// Toueris2Hmi Demo
// by epsilonrt <https://github.com/epsilonrt>

// Control and display of the HMI keys.

// Created 23 January 2018

// This example code is in the public domain.

#include <Toueris2Hmi.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <avr/wdt.h>

//------------------------------------------------------------------------------
const unsigned pause = 1000;
const int hirqPin = 2;
const int ledPin = 13;

Toueris2Hmi Hmi (hirqPin);
char buffer[16];
byte index = 0;

void setup() {
  int loops = 0;

  MCUSR = 0;
  wdt_disable();

  Serial.begin (500000);
  Serial.println ("Toueris2Hmi Class Demo");
  Serial.println ("Available commands:");
  Serial.println (" bXXX:\t to set backlight to XXX (0-255)");
  Serial.println (" sX:\t to turn on led X (0-2)");
  Serial.println (" cX:\t to turn off led X (0-2)");
  Serial.println (" tX:\t to toggle led X (0-2)");
  Serial.println (" gX:\t to get led X (0-2)");
  Serial.println (" WX:\t write all leds (0-7)");
  Serial.println (" TX:\t toggle all leds (0-7)");
  Serial.println (" R:\t read all leds");
  Serial.println (" K:\t RESET by watchdog");

  // The LED is lit while waiting for the slave HMI
  pinMode (ledPin, OUTPUT);
  digitalWrite (ledPin, 1);
  Wire.begin();
  while (!Hmi.begin()) {
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
    Serial.println ("\n>Ok");
  }
  else {
    Serial.println ("\n>Fail");
  }
}

bool test (int i) {
  if (!i) {
    Serial.println ("\n>Fail");
    return false;
  }
  return true;
}


bool str2byte (const char * str, byte * value) {
  char *endptr;
  long val;

  errno = 0;    /* Pour distinguer la réussite/échec après l'appel */
  val = strtol (str, &endptr, 0);

  if ( (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
       || (errno != 0 && val == 0)) {

    return false;
  }

  if ( (endptr == str) || (val > 255) || (val < 0)) {

    return false;
  }
  *value = (byte) val;
  return true;
}

void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    char c = Serial.read();
    if ( ( (c != '\n') && (c != '\r')) && (index < (sizeof (buffer) - 1))) {
      buffer[index++] = c;
    }
    else {
      byte value, read_value;
      bool success;

      buffer[index] = 0;
      switch (buffer[0]) {
        case 'K':
        case 'k':
          buffer[0] = 0;
          index = 0;
          wdt_enable (WDTO_15MS);
          for (;;);
          break;
        case 'b':
          if (str2byte (&buffer[1], &value)) {
            success = Hmi.backlight.write (value);
            read_value = Hmi.backlight.read();
            verify (success & (read_value == value));
          }
          else {
            verify (false);
          }
          break;
        case 's':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <= 2))) {

              success = Hmi.led.set (value);
              read_value = Hmi.led.get (value);
              verify (success & (read_value == true));
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        case 'c':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <= 2))) {

              success = Hmi.led.clear (value);
              read_value = Hmi.led.get (value);
              verify (success & (read_value == false));
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        case 't':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <= 2))) {

              success = Hmi.led.toggle (value);
              verify (success);
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        case 'T':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <=  Hmi.led.all()))) {

              success = Hmi.led.toggleAll (value);
              verify (success);
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        case 'W':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <= Hmi.led.all()))) {

              success = Hmi.led.writeAll (value);
              read_value = Hmi.led.readAll ();
              verify (success & (read_value == value));
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        case 'R':
          read_value = Hmi.led.readAll ();
          Serial.print ("\n>");
          Serial.println (read_value, HEX);
          break;
        case 'g':
          if (str2byte (&buffer[1], &value)) {

            if (test ( (value >= 0) && (value <= 2))) {

              read_value = Hmi.led.get (value);
              if (read_value) {
                Serial.println ("\n>1");
              }
              else {
                Serial.println ("\n>0");
              }
            }
            else {
              verify (false);
            }
          }
          else {
            verify (false);
          }
          break;
        default:
          Serial.println ("\n>Invalid command !");
          break;
      }
      buffer[0] = 0;
      index = 0;
    }
  }

  if (Hmi.keyb.available()) {
    byte key = Hmi.keyb.key();

    if (Hmi.keyb.released()) {
      Serial.write ('R');
    }
    else {

      Serial.write ('P');
    }
    Serial.println (key);
  }
}
//------------------------------------------------------------------------------
