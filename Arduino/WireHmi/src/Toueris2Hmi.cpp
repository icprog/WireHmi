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
 * @brief Interface homme-machine du projet Toueris II
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
