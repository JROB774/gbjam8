/*////////////////////////////////////////////////////////////////////////////*/

#include <gb/gb.h>

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

#include "SPLASH.C"
#include "TITLE.C"
#include "GAME.C"

void main ()
{
    BGP_REG = 0xFF; /* Set the current palette to black so we can fade in. */

    HIDE_SPRITES;
    HIDE_WIN;
    SHOW_BKG;

    DISPLAY_ON;

    splash();
    title();
    game();
}

/*////////////////////////////////////////////////////////////////////////////*/
