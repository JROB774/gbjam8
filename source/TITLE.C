/*////////////////////////////////////////////////////////////////////////////*/

#define TITLE_FADE_SPEED  0x03 /* (3) */

INTERNAL void TITLE ()
{
    SET_BKG_DATA(TILESET_EMPTY   );
    SET_BKG_DATA(TILESET_NUMBERS );
    SET_BKG_DATA(TILESET_ALPHABET);
    SET_BKG_DATA(TILESET_TITLE   );
    SET_MAP_DATA(TILEMAP_TITLE   );

    fade_from_black(TITLE_FADE_SPEED);
    JOYPAD_WAIT_START;
    fade_to_black(TITLE_FADE_SPEED);
}

/*////////////////////////////////////////////////////////////////////////////*/
