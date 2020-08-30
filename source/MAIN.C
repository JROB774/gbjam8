/*////////////////////////////////////////////////////////////////////////////*/

#include <gb/gb.h>
#include <stdio.h>

#include "UTILITY.C"
#include "COLLIDE.C"
#include "FADE.C"
#include "INPUT.C"

#include "TILESETS.C"
#include "TILEMAPS.C"

#include "ACTORS.C"
#include "MONSTERS.C"
#include "PLAYER.C"

void main ()
{
    set_sprite_data(TILESET_SPRITES_OFFSET,TILESET_SPRITES_LENGTH,TILESET_SPRITES);

    set_bkg_data(TILESET_FONT_OFFSET,TILESET_FONT_LENGTH,TILESET_FONT);
    set_bkg_data(TILESET_ROOM_OFFSET,TILESET_ROOM_LENGTH,TILESET_ROOM);

    set_bkg_tiles(0,0, TILEMAP_ROOM_WIDTH,TILEMAP_ROOM_HEIGHT,TILEMAP_ROOM);

    DISPLAY_ON;

    SHOW_BKG;
    SHOW_SPRITES;

    actor_create(0, ATYPE_PLAYER, ASTATE_PLAYER_IDLE,  48, 48);
    actor_create(4, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 80, 40);
    actor_create(8, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 64, 72);

    while (TRUE)
    {
        UPDATE_JOYPAD_STATE;

        actor_update_all();
        wait_vbl_done();
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
