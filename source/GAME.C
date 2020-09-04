/*////////////////////////////////////////////////////////////////////////////*/

#define GAME_FADE_SPEED 0x03 /* (3) */

INTERNAL void GAME ()
{
    SET_SPR_DATA(TILESET_SPR_ISAAC   );
    SET_SPR_DATA(TILESET_SPR_MONSTERS);
    SET_SPR_DATA(TILESET_SPR_TEARS   );
    SET_SPR_DATA(TILESET_SPR_PICKUPS );
    SET_SPR_DATA(TILESET_SPR_ITEMS   );
    SET_SPR_DATA(TILESET_SPR_SPLATS  );
    SET_BKG_DATA(TILESET_DISPLAY     );
    SET_BKG_DATA(TILESET_ROOM        );
    SET_MAP_DATA(TILEMAP_ROOM        );

    status_init();

    /* @Temporary: Just make some debug actors for now. */
    actor_create(ATYPE_PLAYER, ASTATE_PLAYER_IDLE,  48,  48);
    /*
    actor_create(ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 32,  72);
    actor_create(ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 48,  72);
    actor_create(ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 64,  72);
    actor_create(ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 80,  72);
    actor_create(ATYPE_GAPER,  ASTATE_GAPER_MOVE_0, 96,  72);
    */

    fade_from_black(GAME_FADE_SPEED);

    SHOW_SPRITES;

    while (TRUE) {
        DEBUG_PROFILE_BEGIN(GAMELOOP);
        UPDATE_JOYPAD_STATE;
        actor_update_all();
        wait_vbl_done();
        DEBUG_PROFILE_END(GAMELOOP);
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
