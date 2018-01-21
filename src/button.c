/**
 * @file button.c
 * @brief Interface Homme-Machine Projet Toueris 2 - Partie bouton poussoir
 */
#include "hmi.h"
#include "button.h"
#include "hmi-hirq.h"
#include "config.h" // toujours en dernier

/* constants ================================================================ */

/* private variables ======================================================== */
static xButMask xPrevButtons;

/* public variables ========================================================= */
xButMask xButtons;

/* private functions ======================================================== */

// -----------------------------------------------------------------------------
static void
vButtonCheck (xButMask xBitMask, uint8_t ucButtonIndex) {

  if (xBitMask & xPrevButtons) {

    /* Ce bit a changé d'état */
    if ( (xBitMask & xButtons) == 0) {

      /* Le bit est à 0, le bouton a été relaché */
      ucButtonIndex |= BUT_RELEASE;
    }
    ATOMIC_BLOCK (ATOMIC_RESTORESTATE) {
    }
    //vTwiUsiSlaveWrite (ucButtonIndex); // bloque si buffer TX plein
  }
}


/* internal public functions ================================================ */
// -----------------------------------------------------------------------------
void
vHmiButtonInit (void) {

  xPrevButtons = BUTTON_NO_BUTTON;
  vButInit();
}

// -----------------------------------------------------------------------------
void
vHmiButtonTask (void) {

  xButtons = xButGet (BUTTON_ALL_BUTTONS); // xButGet gère l'anti-rebond

  if (xButtons != xPrevButtons) {

    // Un bit à 1 dans xPrevButtons indique un changemet d'état de celui-ci
    xPrevButtons ^= xButtons;

    // 1 ou plusieurs bouton ont changés d'état
    vButtonCheck (BUTTON_BUTTON1, 1);
    vButtonCheck (BUTTON_BUTTON2, 2);
    vButtonCheck (BUTTON_BUTTON3, 3);
    vButtonCheck (BUTTON_BUTTON4, 4);
    vButtonCheck (BUTTON_BUTTON5, 5);
    xPrevButtons = xButtons;
  }
  if (bTwiSlaveTxBufferEmpty()) {

    // Désactive HIRQ si le buffer de transmission est vide
    vHmiHirqClear();
  }
  else {

    // Active HIRQ si le buffer de transmission contient des données
    vHmiHirqSet();
  }
}

/* ========================================================================== */
