#ifndef _TOUERIS2_BACKLIGHT_H_
#  define _TOUERIS2_BACKLIGHT_H_
/* ========================================================================== */

/* LCD_BACKLIGHT ============================================================ */
#  include <avrio/defs.h>
#  include <avr/io.h>

/* inline public functions ================================================== */
/*
 * Initialise la ressource matérielle (timer PWM de préférence) utilisée par
 * le module lcd (rétroéclairage).
 * A modifier en fonction du timer et de la sortie utilisée.
 */
INLINE void
vHmiBacklightInit (void) {

  DDRD |= _BV (6);  /* PD6 (OC0A) en sortie */
  /*
   * Mode PWM Phase correcte (1),
   * Clear OC on compare match
   * FCLK / 8
   * F = FCPU / (8 * 510) = 1.9 KHz pour 8 MHz
   */
  TCCR0A = 0b10000001;
  TCCR0B = 0b00000010;
}

/*
 * Modifie le niveau de rétroéclairage du LCD
 * @param ucValue niveau entre 0 et 63
 */
INLINE void
vHmiBacklightSet (uint8_t ucValue) {

  OCR0A = ucValue;
}

/* ========================================================================== */
#endif /* _TOUERIS2_BACKLIGHT_H_ */