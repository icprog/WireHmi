/*
 * This file is part of AvrIO.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * <http://www.cecill.info>. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#ifndef _AVRIO_BOARD_BUTTON_H_
#  define _AVRIO_BOARD_BUTTON_H_
/* ========================================================================== */

/* BUTTON==================================================================== */
#  include <avrio/defs.h>
#  include <avr/io.h>
#  include <avr/interrupt.h>

/* constants ================================================================ */
#  define BUTTON_QUANTITY  6
// PC0-PC2
#  define BUTTON_BUTTON1 _BV(0)
#  define BUTTON_BUTTON2 _BV(1)
#  define BUTTON_BUTTON3 _BV(2)
#  define BUTTONC_ALL_BUTTONS   (BUTTON_BUTTON1|BUTTON_BUTTON2|BUTTON_BUTTON3)

// PB1-PB3
#  define BUTTON_BUTTON4 _BV(3)
#  define BUTTON_BUTTON5 _BV(4)
#  define BUTTON_BUTTON6 _BV(5)
#  define BUTTONB_ALL_BUTTONS   ((BUTTON_BUTTON4|BUTTON_BUTTON5|BUTTON_BUTTON6)>>2)

#  define BUTTON_ALL_BUTTONS (BUTTON_BUTTON1|BUTTON_BUTTON2|BUTTON_BUTTON3|BUTTON_BUTTON4|BUTTON_BUTTON5|BUTTON_BUTTON6)
#  define BUTTON_NO_BUTTON (0)

// PCINT
#  define BUTTONB_vect PCINT0_vect
#  define BUTTONB_PCIE PCIE0
#  define BUTTONB_PCMSK  PCMSK0
#  define BUTTONC_vect PCINT1_vect
#  define BUTTONC_PCIE PCIE1
#  define BUTTONC_PCMSK  PCMSK1
#  define BUTTON_BUTTON1_PCINT  PCINT8
#  define BUTTON_BUTTON2_PCINT  PCINT9
#  define BUTTON_BUTTON3_PCINT  PCINT10
#  define BUTTON_BUTTON4_PCINT  PCINT1
#  define BUTTON_BUTTON5_PCINT  PCINT2
#  define BUTTON_BUTTON6_PCINT  PCINT3

#  if !defined(PCICR) && defined(GIMSK)
#   define PCICR GIMSK
#  endif
/* types ==================================================================== */
typedef uint8_t xButMask;

/* inline public functions ================================================== */
// ------------------------------------------------------------------------------
static inline void
vButHardwareInit (void) {

  PORTB |= BUTTONB_ALL_BUTTONS;
  DDRB &= ~BUTTONB_ALL_BUTTONS;
  PORTC |= BUTTONC_ALL_BUTTONS;
  DDRC &= ~BUTTONC_ALL_BUTTONS;
}

// ------------------------------------------------------------------------------
static inline xButMask
xButHardwareGet (xButMask xMask) {

  return (((PINC ^ BUTTONC_ALL_BUTTONS) & BUTTONC_ALL_BUTTONS) | (((PINB ^ BUTTONB_ALL_BUTTONS)<<2) & (BUTTONB_ALL_BUTTONS<<2))) & xMask;
}

/* public variables ========================================================= */
#  if defined(BUTTON_MASK_ARRAY_ENABLE)
#    define DECLARE_BUTTON_MASK_ARRAY  \
  const xButMask \
    xButMaskArray [BUTTON_QUANTITY] = { \
      BUTTON_BUTTON1,BUTTON_BUTTON2,BUTTON_BUTTON3,BUTTON_BUTTON4,BUTTON_BUTTON5,BUTTON_BUTTON6 \
    }
#  else
#    define DECLARE_BUTTON_MASK_ARRAY
#  endif

/* ========================================================================== */
#endif /* _AVRIO_BOARD_BUTTON_H_ */
