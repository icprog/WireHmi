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
#ifndef __TOUERIS2_HMI_PUBLIC_H__
#define __TOUERIS2_HMI_PUBLIC_H__

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
    bool begin();
    WireLeds led;
    WireKeyboard keyb;
    WireBackLight backlight;
};
// -----------------------------------------------------------------------------
#endif // defined(__cplusplus)
/* ========================================================================== */
#endif /* __TOUERIS2_HMI_PUBLIC_H__ */
