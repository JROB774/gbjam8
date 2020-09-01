/*////////////////////////////////////////////////////////////////////////////*/

GLOBAL const U8 TILE_HEART_FULL[] = { 0x0B }; /* (11) */
GLOBAL const U8 TILE_HEART_NONE[] = { 0x0C }; /* (12) */

INTERNAL void display_draw_status ()
{
    set_bkg_tiles(1,0, 1,1, TILE_HEART_FULL);
    set_bkg_tiles(2,0, 1,1, TILE_HEART_FULL);
    set_bkg_tiles(3,0, 1,1, TILE_HEART_FULL);
}

INTERNAL void display_draw_map ()
{
    HIDE_SPRITES;
    SET_MAP_DATA(TILEMAP_MAP);
    JOYPAD_WAIT_SELECT;
    SET_MAP_DATA(TILEMAP_ROOM);
    SHOW_SPRITES;
}

/*////////////////////////////////////////////////////////////////////////////*/
