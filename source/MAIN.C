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

void main ()
{
    splash();

    SET_SPR_DATA(TILESET_SPRITES );
    SET_BKG_DATA(TILESET_EMPTY   );
    SET_BKG_DATA(TILESET_NUMBERS );
    SET_BKG_DATA(TILESET_ALPHABET);
    SET_BKG_DATA(TILESET_DISPLAY );
    SET_BKG_DATA(TILESET_ROOM    );

    SET_MAP_DATA(TILEMAP_ROOM);

    display_draw_status();

    actor_create(0, ATYPE_PLAYER, ASTATE_PLAYER_IDLE,  48, 48);
    actor_create(4, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 80, 40);
    actor_create(8, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 64, 72);

    SET_DISPLAY_FLAGS;

    fade_from_black(3);

    while (TRUE)
    {
        UPDATE_JOYPAD_STATE;
        SET_DISPLAY_FLAGS;

        actor_update_all();
        wait_vbl_done();
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
