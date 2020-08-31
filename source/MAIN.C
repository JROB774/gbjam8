/*////////////////////////////////////////////////////////////////////////////*/

#include <gb/gb.h>

#define DEBUG_MODE 1

#include "UTILITY.C"
#include "MATH.C"
#include "COLLIDE.C"
#include "FADE.C"
#include "INPUT.C"
#include "TILESETS.C"
#include "TILEMAPS.C"
#include "ACTORS.C"
#include "MONSTERS.C"
#include "PLAYER.C"
#include "DISPLAY.C"
#include "GAME.C"
#include "TITLE.C"
#include "SPLASH.C"

void main ()
{
    BGP_REG = 0xFF; /* Set the current palette to black so we can fade in. */
    DISPLAY_ON;     /* Enable the Game Boy's display.                      */
    SPLASH();       /* Play through all the splash screens / credits.      */
    TITLE();        /* Display the title screen and wait for START.        */
    GAME();         /* Initialize and then run the main game loop.         */
}

/*////////////////////////////////////////////////////////////////////////////*/
