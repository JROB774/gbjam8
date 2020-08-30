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

#define SET_DISPLAY_FLAGS \
do                        \
{                         \
SHOW_SPRITES;             \
SHOW_BKG;                 \
DISPLAY_ON;               \
}                         \
while (0)

void main ()
{
    BGP_REG = 0xFF; /* Set the current palette to black so we can fade in. */

    set_sprite_data(TILESET_SPRITES_OFFSET,TILESET_SPRITES_LENGTH,TILESET_SPRITES);

    set_bkg_data(TILESET_EMPTY_OFFSET,    TILESET_EMPTY_LENGTH,    TILESET_EMPTY   );
    set_bkg_data(TILESET_NUMBERS_OFFSET,  TILESET_NUMBERS_LENGTH,  TILESET_NUMBERS );
    set_bkg_data(TILESET_ALPHABET_OFFSET, TILESET_ALPHABET_LENGTH, TILESET_ALPHABET);
    set_bkg_data(TILESET_ROOM_OFFSET,     TILESET_ROOM_LENGTH,     TILESET_ROOM    );

    set_bkg_tiles(0,0, TILEMAP_ROOM_WIDTH,TILEMAP_ROOM_HEIGHT,TILEMAP_ROOM);

    display_update();

    SET_DISPLAY_FLAGS;

    actor_create(0, ATYPE_PLAYER, ASTATE_PLAYER_IDLE,  48, 48);
    actor_create(4, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 80, 40);
    actor_create(8, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 64, 72);

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
