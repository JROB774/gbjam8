/*////////////////////////////////////////////////////////////////////////////*/

#define DEBUG_NO_PROFILE 1
#define DEBUG_MODE       1

#include <gb/gb.h>
#include <rand.h>

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
#include "ROOMS.C"
#include "FLOOR.C"
#include "DISPLAY.C"
#include "GAME.C"
#include "TITLE.C"
#include "SPLASH.C"

void main ()
{
    #if 1
    while (TRUE)
    {
        initrand(sys_time);
        printf("\n");
        generate_floor();
        printf("\n");
        WAIT(10);
        waitpad(0xFF);
    }
    #else
    BKG_PAL0 = 0xFF; /* Set the current palette to black so we can fade in. */
    SPR_PAL0 = 0xE4; /* Set the first sprite palette to be default.         */
    SPR_PAL1 = 0x1B; /* Set the second sprite palette to be inverted.       */
    SPRITES_8x16;    /* We use 8x16 sprite mode to fit more data in OAM.    */
    DISPLAY_ON;      /* Enable the Game Boy's display.                      */
    SPLASH();        /* Play through all the splash screens / credits.      */
    TITLE();         /* Display the title screen and wait for START.        */
    GAME();          /* Initialize and then run the main game loop.         */
    #endif
}

/*////////////////////////////////////////////////////////////////////////////*/
