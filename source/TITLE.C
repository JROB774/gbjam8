/*////////////////////////////////////////////////////////////////////////////*/

#define TITLE_FADE_SPEED     3
#define TITLE_WAIT_DURATION 20

INTERNAL void TITLE ()
{
    SET_BKG_DATA(TILESET_EMPTY   );
    SET_BKG_DATA(TILESET_NUMBERS );
    SET_BKG_DATA(TILESET_ALPHABET);
    SET_BKG_DATA(TILESET_TITLE   );
    SET_MAP_DATA(TILEMAP_TITLE   );

    #if !DEBUG_MODE
    fade_from_black(TITLE_FADE_SPEED);
    JOYPAD_WAIT_START;
    fade_to_black(TITLE_FADE_SPEED);
    WAIT(TITLE_WAIT_DURATION);
    #endif
}

/*////////////////////////////////////////////////////////////////////////////*/
