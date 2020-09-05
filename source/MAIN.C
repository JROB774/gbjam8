/*////////////////////////////////////////////////////////////////////////////*/

#define DEBUG_NO_PROFILE 0
#define DEBUG_MODE       1

#include <gb/gb.h>

#include "UTILITY.C"
#include "DECLARE.C"
#include "TILESETS.C"
#include "TILEMAPS.C"
#include "MATH.C"
#include "INPUT.C"
#include "FADE.C"
#include "ACTORS.C"
#include "MONSTERS.C"
#include "PLAYER.C"
#include "DISPLAY.C"
#include "GAME.C"
#include "TITLE.C"
#include "SPLASH.C"

void main ()
{
    BKG_PAL0 = 0xFF; /* Set the current palette to black so we can fade in. */
    SPRITES_8x16;    /* We use 8x16 sprite mode to fit more data in OAM.    */
    DISPLAY_ON;      /* Enable the Game Boy's display.                      */
    SPLASH();        /* Play through all the splash screens / credits.      */
    TITLE();         /* Display the title screen and wait for START.        */
    GAME();          /* Initialize and then run the main game loop.         */
}

/*////////////////////////////////////////////////////////////////////////////*/
