/*////////////////////////////////////////////////////////////////////////////*/

#include <gb/gb.h>

#include "DEFINE.C"
#include "COLLIDE.C"
#include "FADE.C"
#include "INPUT.C"

#include "TILESETS.C"
#include "TILEMAPS.C"

void main ()
{
    set_sprite_data(TILESET_SPRITES_OFFSET,TILESET_SPRITES_LENGTH,TILESET_SPRITES);

    set_bkg_data(TILESET_FONT_OFFSET,TILESET_FONT_LENGTH,TILESET_FONT);
    set_bkg_data(TILESET_ROOM_OFFSET,TILESET_ROOM_LENGTH,TILESET_ROOM);

    set_bkg_tiles(0,0, TILEMAP_ROOM_WIDTH,TILEMAP_ROOM_HEIGHT,TILEMAP_ROOM);

    DISPLAY_ON;
    SHOW_BKG;

    while (TRUE)
    {
        wait_vbl_done();
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
