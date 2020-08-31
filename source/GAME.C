/*////////////////////////////////////////////////////////////////////////////*/

#define GAME_FADE_SPEED  0x03 /* (3) */

INTERNAL void game ()
{
    SET_SPR_DATA(TILESET_SPRITES);
    SET_BKG_DATA(TILESET_DISPLAY);
    SET_BKG_DATA(TILESET_ROOM   );
    SET_MAP_DATA(TILEMAP_ROOM   );

    display_draw_status();

    /* @Temporary: Just make some debug actors for now. */
    actor_create(0, ATYPE_PLAYER, ASTATE_PLAYER_IDLE,  48, 48);
    actor_create(4, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 80, 40);
    actor_create(8, ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 64, 72);

    fade_from_black(GAME_FADE_SPEED);

    SHOW_SPRITES;

    while (TRUE)
    {
        UPDATE_JOYPAD_STATE;
        actor_update_all();
        wait_vbl_done();
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
