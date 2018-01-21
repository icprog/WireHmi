/**
 * Copyright © 2018 epsilonRT. All rights reserved.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * <http://www.cecill.info>.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 * @file
 * @brief
 */
#include "WireHmi.h"

// -----------------------------------------------------------------------------
//
//                            WireSlave class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
WireSlave::WireSlave (byte slaveAddress) : _address (slaveAddress)  {
}

// -----------------------------------------------------------------------------
byte WireSlave::read (byte dataAddress, byte *values, byte len) {
  byte readBytes = 0;
  Wire.beginTransmission (_address); // transmit to device
  Wire.write (dataAddress);       // sends one byte
  Wire.endTransmission (false);   // repeat start transmitting
  readBytes += Wire.requestFrom (_address, len);   // request bytes from slave device
  while (Wire.available()) { // slave may send less than requested
    *values++ = Wire.read();    // receive a byte as character
  }
  return readBytes;
}

// -----------------------------------------------------------------------------
byte WireSlave::read (byte dataAddress) {
  byte data = 0xFF;
  this->read (dataAddress, &data, 1);
  return data;
}

// -----------------------------------------------------------------------------
byte WireSlave::read (byte *values, byte len) {
  byte readBytes = 0;
  Wire.beginTransmission (_address); // transmit to device
  readBytes += Wire.requestFrom (_address, len);   // request bytes from slave device
  while (Wire.available()) { // slave may send less than requested
    *values++ = Wire.read();    // receive a byte as character
  }
  return readBytes;
}

// -----------------------------------------------------------------------------
byte WireSlave::read () {
  byte data = 0xFF;
  this->read (&data, 1);
  return data;
}

// -----------------------------------------------------------------------------
bool WireSlave::write (byte dataAddress, const byte *values, byte len) {
  Wire.beginTransmission (_address); // transmit to device
  Wire.write (dataAddress);       // sends one byte
  Wire.write (values, len);  // sends data bytes
  return (Wire.endTransmission() == 0);    // stop transmitting
}

// -----------------------------------------------------------------------------
bool WireSlave::write (byte dataAddress, byte value) {
  return this->write (dataAddress, &value, 1);
}

// -----------------------------------------------------------------------------
bool WireSlave::write (const byte *values, byte len) {
  Wire.beginTransmission (_address); // transmit to device
  Wire.write (values, len);  // sends data bytes
  return (Wire.endTransmission() == 0);    // stop transmitting
}

// -----------------------------------------------------------------------------
bool WireSlave::write (byte value) {
  return this->write (&value, 1);
}

// -----------------------------------------------------------------------------
//
//                         WireRegister class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
WireRegister::WireRegister (WireSlave * slave, byte regAddress) :
  _slave (slave), _reg (regAddress) {

}

// -----------------------------------------------------------------------------
byte WireRegister::read() {
  return _slave->read (_reg);
}

// -----------------------------------------------------------------------------
bool WireRegister::write (byte value) {
  return _slave->write (_reg, value);
}

// -----------------------------------------------------------------------------
//
//                            WireLeds class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
WireLeds::WireLeds (WireSlave * slave, byte regAddress, byte size) :
  WireRegister (slave, regAddress), _size (size), _mask ( (1 << size) - 1), _leds (0) {
}

// -----------------------------------------------------------------------------
bool WireLeds::begin() {

  return this->write (_leds);
}

// -----------------------------------------------------------------------------
byte WireLeds::readAll() {

  _leds = this->read();
  return _leds;
}

// -----------------------------------------------------------------------------
bool WireLeds::writeAll (byte all) {

  _leds = all & _mask;
  return this->write (_leds);
}

// -----------------------------------------------------------------------------
bool WireLeds::toggleAll (byte all) {

  _leds ^= all & _mask;
  return this->write (_leds);
}

// -----------------------------------------------------------------------------
bool WireLeds::set (byte led) {
  byte b = (1 << led) & _mask;
  if (b) {
    _leds |= b;
    return this->write (_leds);
  }
  return false;
}

// -----------------------------------------------------------------------------
bool WireLeds::clear (byte led) {
  byte b = (1 << led) & _mask;
  if (b) {
    _leds &= ~b;
    return this->write (_leds);
  }
  return false;
}

// -----------------------------------------------------------------------------
bool WireLeds::toggle (byte led) {
  byte b = (1 << led) & _mask;
  if (b) {
    _leds ^= b;
    return this->write (_leds);
  }
  return false;
}

// -----------------------------------------------------------------------------
bool WireLeds::get (byte led) {
  byte b = (1 << led) & _mask;
  if (b) {
    _leds = this->read();
    return (_leds & b) != 0;
  }
  return false;
}

// -----------------------------------------------------------------------------
//
//                            WireKeyboard class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
WireKeyboard::WireKeyboard (WireSlave * slave, byte regAddress, int hirqPin)  :
  WireRegister (slave, regAddress), _hirq (hirqPin), _key (0) {

}

// -----------------------------------------------------------------------------
bool WireKeyboard::begin() {
  if (_hirq > 0) {
    pinMode (_hirq, INPUT);
  }
  return true;
}

// -----------------------------------------------------------------------------
bool WireKeyboard::available() {
  if (_hirq > 0) {
    if (digitalRead (_hirq)) {
      return false;
    }
  }
  _key = WireRegister::read();
  return _key != 0;
}

// -----------------------------------------------------------------------------
//
//                            WireBackLight class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
WireBackLight::WireBackLight (WireSlave * slave, byte regAddress)  :
  WireRegister (slave, regAddress) {

}

// -----------------------------------------------------------------------------
bool WireBackLight::begin() {

  return true;
}

/* ========================================================================== */
