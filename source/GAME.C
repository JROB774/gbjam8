/*////////////////////////////////////////////////////////////////////////////*/

#define GAME_FADE_SPEED 10

INTERNAL void GAME ()
{
    while (TRUE) {
        U8 ix,iy, empty=0;

        SET_SPR_DATA(TILESET_SPRITES );
        SET_BKG_DATA(TILESET_EMPTY   );
        SET_BKG_DATA(TILESET_NUMBERS );
        SET_BKG_DATA(TILESET_ALPHABET);
        SET_BKG_DATA(TILESET_DISPLAY );
        SET_BKG_DATA(TILESET_ROOM    );

        for (iy=0; iy<SCREEN_TILES_HEIGHT; ++iy) {
            for (ix=0; ix<SCREEN_TILES_WIDTH; ++ix) {
                set_bkg_tiles(ix,iy, 1,1, &empty);
            }
        }

        SET_MAP_DATA(TILEMAP_ROOM);

        player_init();
        status_init();

        /* Use the system time to determine the random seed. */
        initrand(sys_time);

        actor_create(ATYPE_PLAYER, 0, 0);
        generate_floor();

        fade_from_black(GAME_FADE_SPEED);

        SHOW_SPRITES;

        reset_flag = FALSE;
        while (!reset_flag) {
            DEBUG_PROFILE_BEGIN(GAMELOOP);
            UPDATE_JOYPAD_STATE;
            actor_tick_all();
            room_tick();
            wait_vbl_done();
            DEBUG_PROFILE_END(GAMELOOP);
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
