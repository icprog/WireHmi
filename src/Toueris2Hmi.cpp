/* Copyright © 2018 Pascal JEAN, All rights reserved.
 * This file is part of the WireHmi Library.
 *
 * The WireHmi Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * The WireHmi Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the WireHmi Library; if not, see <http://www.gnu.org/licenses/>.
 */
#include "Toueris2Hmi.h"

// -----------------------------------------------------------------------------
//
//                            Toueris2Hmi class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
Toueris2Hmi::Toueris2Hmi (int hirqPin, byte slaveAddress) :
  WireSlave (slaveAddress),
  led (this, LED_REG, LED_NB),
  keyb (this, BUT_REG, hirqPin),
  backlight (this, BACKLIGHT_REG) {
}

// -----------------------------------------------------------------------------
bool Toueris2Hmi::begin() {
  
  return this->led.begin() && this->keyb.begin() && this->backlight.begin();
}

/* ========================================================================== */
