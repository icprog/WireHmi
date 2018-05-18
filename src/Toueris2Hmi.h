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
#include <WireHmi.h>

#define LED1  0
#define LED2  1
#define LED3  2
#define LED4  3
#define LED5  4

#define LED_RED     LED1
#define LED_GREEN1  LED2
#define LED_GREEN2  LED3
#define LED_YELLOW1 LED4
#define LED_YELLOW2 LED5

#define KUP       1
#define KDOWN     2
#define KLEFT     3
#define KRIGHT    4
#define KCENTER   5

#define TOUERIS2_HMI_SLAVE_ADDR 0b0111111

// Toueris II Hmi
class Toueris2Hmi : public  WireSlave {
  public:
    Toueris2Hmi (int hirqPin = -1, byte slaveAddress = TOUERIS2_HMI_SLAVE_ADDR);
    bool begin();
    WireLeds led;
    WireKeyboard keyb;
    WireBackLight backlight;
};

/* ========================================================================== */
#endif /* __TOUERIS2_HMI_PUBLIC_H__ */
