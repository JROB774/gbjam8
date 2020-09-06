/*////////////////////////////////////////////////////////////////////////////*/

#define GAME_FADE_SPEED 0x03 /* (3) */

INTERNAL void GAME ()
{
    SET_SPR_DATA(TILESET_SPRITES );
    SET_BKG_DATA(TILESET_EMPTY   );
    SET_BKG_DATA(TILESET_NUMBERS );
    SET_BKG_DATA(TILESET_ALPHABET);
    SET_BKG_DATA(TILESET_DISPLAY );
    SET_BKG_DATA(TILESET_ROOM    );
    SET_MAP_DATA(TILEMAP_EMPTY   );
    SET_MAP_DATA(TILEMAP_ROOM    );

    player_init();
    status_init();

    /* Use the system time to determine the random seed. */
    initrand(sys_time);

    generate_floor();

    /* @Temporary: Just make some debug actors for now. ***********************/
    actor_create(ATYPE_PLAYER, 24, 72);
    /*actor_create(ATYPE_GAPER,  72, 56);*/
    /*actor_create(ATYPE_GAPER,  56, 72);*/
    /*actor_create(ATYPE_GAPER,  72, 72);*/
    /*actor_create(ATYPE_GAPER,  88, 72);*/
    /*actor_create(ATYPE_GAPER,  72, 88);*/
    /**************************************************************************/

    fade_from_black(GAME_FADE_SPEED);

    SHOW_SPRITES;

    while (TRUE) {
        DEBUG_PROFILE_BEGIN(GAMELOOP);
        UPDATE_JOYPAD_STATE;
        actor_tick_all();
        room_tick();
        wait_vbl_done();
        DEBUG_PROFILE_END(GAMELOOP);
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
