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
 * @brief Description de l'interface homme-machine du projet Toueris II
 */
#ifndef __TOUERIS2_HMI_H__
#define __TOUERIS2_HMI_H__

#define TOUERIS2_HMI_SLAVE_ADDR 0b0111111

#define LED_REG 0
#define LED_NB  3
#define LED1  (1<<0)
#define LED2  (1<<1)
#define LED3  (1<<2)

#define BACKLIGHT_REG 1

#define BUT_REG 2
#define BUT_NB  5
#define BUT_RELEASE (1<<7)
#define BUT_UP      1
#define BUT_DOWN    2
#define BUT_LEFT    3
#define BUT_RIGHT   4
#define BUT_CENTER  5

#if defined(__cplusplus)
// -----------------------------------------------------------------------------
#include <WireHmi.h>

// Toueris II Hmi
class Toueris2Hmi : public  WireSlave {
  public:
    Toueris2Hmi (int hirqPin = -1, byte slaveAddress = TOUERIS2_HMI_SLAVE_ADDR);
    void begin();
    WireLeds led;
    WireKeyboard keyb;
    WireBackLight backlight;
};
// -----------------------------------------------------------------------------
#endif // defined(__cplusplus)
/* ========================================================================== */
#endif /* __TOUERIS2_HMI_H__ */
