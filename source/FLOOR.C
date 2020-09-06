/*////////////////////////////////////////////////////////////////////////////*/

/* FLOOR GENERATION */

#define MAX_FLOOR_WIDTH  0x06
#define MAX_FLOOR_HEIGHT 0x06

#define MIN_FLOOR_ROOMS  0x06 /* ( 6) */
#define MAX_FLOOR_ROOMS  0x0B /* (11) */

#define ROOM_TYPE_NONE   0x00
#define ROOM_TYPE_START  0x01
#define ROOM_TYPE_NORMAL 0x02
#define ROOM_TYPE_BOSS   0x03

#define ROOM_DOOR_U      0x01
#define ROOM_DOOR_R      0x02
#define ROOM_DOOR_D      0x04
#define ROOM_DOOR_L      0x08

typedef struct _MROOM_
{
    U8   type;   /* Identifier stating what type of room it is.      */
    U8   doors;  /* Flags representing what doors the room has.      */
    BOOL clear;  /* States whether the room has been cleared or not. */

} MROOM;

GLOBAL MROOM floor[MAX_FLOOR_HEIGHT][MAX_FLOOR_WIDTH];
GLOBAL U8 gen_count;

INTERNAL BOOL generate_is_end_room (U8 x, U8 y)
{
    /* Only if we have one door are we an end room (start room does not count). */
    MROOM* room = &floor[y][x];
    if (room->type == ROOM_TYPE_NORMAL) {
        if (room->doors == ROOM_DOOR_U ||
            room->doors == ROOM_DOOR_R ||
            room->doors == ROOM_DOOR_D ||
            room->doors == ROOM_DOOR_L) {
                return TRUE;
        }
    }
    return FALSE;
}

INTERNAL BOOL generate_check_diagonals (U8 x, U8 y, U8 dir)
{
    /* Check to see if there are diagonal rooms where we plan to place. */
    switch (dir) {
        case (ROOM_DOOR_U): { return ((!floor[y-1][x-1].type) && (!floor[y-1][x+1].type)); } break;
        case (ROOM_DOOR_R): { return ((!floor[y-1][x+1].type) && (!floor[y+1][x+1].type)); } break;
        case (ROOM_DOOR_D): { return ((!floor[y+1][x-1].type) && (!floor[y+1][x+1].type)); } break;
        case (ROOM_DOOR_L): { return ((!floor[y-1][x-1].type) && (!floor[y+1][x-1].type)); } break;
    }
    return FALSE;
}

INTERNAL VOID generate_check_doors (U8 x, U8 y)
{
    /* Removes/adds doors depending on the room's neighbors. */
    MROOM* room = &floor[y][x];
    room->doors = 0x00;
    if ((y != (                 0)) && (floor[y-1][x].type)) { SET_FLAGS(room->doors, ROOM_DOOR_U); }
    if ((x != (MAX_FLOOR_WIDTH -1)) && (floor[y][x+1].type)) { SET_FLAGS(room->doors, ROOM_DOOR_R); }
    if ((y != (MAX_FLOOR_HEIGHT-1)) && (floor[y+1][x].type)) { SET_FLAGS(room->doors, ROOM_DOOR_D); }
    if ((x != (                 0)) && (floor[y][x-1].type)) { SET_FLAGS(room->doors, ROOM_DOOR_L); }
}

INTERNAL VOID generate_room_doors (U8 x, U8 y)
{
    /* Generate random doors at the four possible directions if possible. */
    MROOM* room = &floor[y][x];
    if ((y != (                 0)) && (((U8)rand()) % 2 == 0) && (generate_check_diagonals(x,y,ROOM_DOOR_U))) { SET_FLAGS(room->doors, ROOM_DOOR_U); }
    if ((x != (MAX_FLOOR_WIDTH -1)) && (((U8)rand()) % 2 == 0) && (generate_check_diagonals(x,y,ROOM_DOOR_R))) { SET_FLAGS(room->doors, ROOM_DOOR_R); }
    if ((y != (MAX_FLOOR_HEIGHT-1)) && (((U8)rand()) % 2 == 0) && (generate_check_diagonals(x,y,ROOM_DOOR_D))) { SET_FLAGS(room->doors, ROOM_DOOR_D); }
    if ((x != (                 0)) && (((U8)rand()) % 2 == 0) && (generate_check_diagonals(x,y,ROOM_DOOR_L))) { SET_FLAGS(room->doors, ROOM_DOOR_L); }
}

INTERNAL BOOL generate_room_neighbors (U8 x, U8 y)
{
    /* Generate a room at a given direction if there is a door there. */
    MROOM* room = &floor[y][x];
    BOOL generated = FALSE;
    if ((room->doors & ROOM_DOOR_U) && (floor[y-1][x].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_check_diagonals(x,y,ROOM_DOOR_U)) {
            generate_room(x,y-1);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_U);
        }
    }
    if ((room->doors & ROOM_DOOR_R) && (floor[y][x+1].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_check_diagonals(x,y,ROOM_DOOR_R)) {
            generate_room(x+1,y);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_R);
        }
    }
    if ((room->doors & ROOM_DOOR_D) && (floor[y+1][x].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_check_diagonals(x,y,ROOM_DOOR_D)) {
            generate_room(x,y+1);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_D);
        }
    }
    if ((room->doors & ROOM_DOOR_L) && (floor[y][x-1].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_check_diagonals(x,y,ROOM_DOOR_L)) {
            generate_room(x-1,y);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_L);
        }
    }
    return generated;
}

INTERNAL VOID generate_room (U8 x, U8 y)
{
    floor[y][x].type = ROOM_TYPE_NORMAL;
    generate_room_doors(x,y);
    gen_count++;
}

INTERNAL VOID generate_floor (VOID)
{
    U8 ix,iy, sx,sy;
    BOOL generating;
    BOOL special_room_boss;

    /* We will keep generating floors until we get one that fulfills all our rules. */
    while (TRUE) {
        /* Reset the floor in case there was a previous one. */
        gen_count = 0;
        for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
            for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
                floor[iy][ix].type   = ROOM_TYPE_NONE;
                floor[iy][ix].doors  = 0x00;
                floor[iy][ix].clear  = FALSE;
            }
        }

        /* Determine the location of the starting room. */
        /* Start rooms cannot be at the edge of the map. */
        sx = ((U8)rand()) % (MAX_FLOOR_WIDTH -2) + 1;
        sy = ((U8)rand()) % (MAX_FLOOR_HEIGHT-2) + 1;

        floor[sy][sx].type = ROOM_TYPE_START;
        floor[sy][sx].clear = TRUE; /* Start room is always clear. */

        /* Calculate what doors the start room should have. */
        /* We do this until we have at least one door. */
        while (!floor[sy][sx].doors) {
            generate_room_doors(sx,sy);
        }

        /* We have one room: the start room. */
        gen_count = 1;

        /* Loop through the floor and whilst there are doors with */
        /* no rooms create new rooms until the map is complete.   */
        generating = TRUE;
        while (generating) {
            generating = FALSE;
            for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
                for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
                    if (floor[iy][ix].type != ROOM_TYPE_NONE) {
                        if (generate_room_neighbors(ix,iy)) { /* Returns TRUE if new rooms were generated. */
                            generating = TRUE;
                            /* If we have more than enough rooms then leave early. */
                            if (gen_count >= MAX_FLOOR_ROOMS) {
                                goto endgen;
                            }
                        }
                    }
                }
            }
        }
        endgen:

        /* Go through and add and remove doors where needed. */
        for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
            for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
                generate_check_doors(ix,iy);
            }
        }

        /* If we are within the floor limits... */
        if ((gen_count >= MIN_FLOOR_ROOMS) && (gen_count <= MAX_FLOOR_ROOMS)) {
            /* ...and we have enough end rooms for all special room types... */
            U8 count = 0;
            for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
                for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
                    if (generate_is_end_room(ix,iy)) {
                        count++;
                    }
                }
            }
            if (count >= 2) {
                break; /* ...then we are done! */
            }
        }
    }

    /* @Improve: Make it so the boss spawns far away! */
    /* Assign special room types to random end rooms. */
    special_room_boss = FALSE;
    for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
        for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
            if (generate_is_end_room(ix,iy)) {
                if (!special_room_boss) {
                    floor[iy][ix].type = ROOM_TYPE_BOSS;
                    special_room_boss = TRUE;
                }
            }
        }
    }

    /* Set the player's current room position to the start room. */
    pdata.xroom = sx;
    pdata.yroom = sy;

    /* Update the player's room tile graphics to match the doors. */
    room_update_doors();

    /* Set the player's room positiion to the center. */
    a_player->x = ITOF(8+(((SCREEN_WIDTH-16)-16)/2));
    a_player->y = ITOF(16+(((SCREEN_HEIGHT-16)-16)/2));
    actor_update_sprite_pos(a_player);

    /* Debug print out the floor. */
    #if 0
    for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
        for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
            switch (floor[iy][ix].type) {
                case (ROOM_TYPE_NONE  ): printf("."); break;
                case (ROOM_TYPE_START ): printf("S"); break;
                case (ROOM_TYPE_NORMAL): printf("#"); break;
                case (ROOM_TYPE_ITEM  ): printf("I"); break;
                case (ROOM_TYPE_BOSS  ): printf("B"); break;
            }
        }
        printf("\n");
    }
    #endif
}

/*////////////////////////////////////////////////////////////////////////////*/

/* ROOM MANAGEMENT */

#define END_GAME_FADE_SPEED 10

#define ROOM_PLAYER_POS_U_X  72
#define ROOM_PLAYER_POS_U_Y  32
#define ROOM_PLAYER_POS_R_X 120
#define ROOM_PLAYER_POS_R_Y  72
#define ROOM_PLAYER_POS_D_X  72
#define ROOM_PLAYER_POS_D_Y 112
#define ROOM_PLAYER_POS_L_X  24
#define ROOM_PLAYER_POS_L_Y  72

#define ROOM_DOOR_POS_U_X  9
#define ROOM_DOOR_POS_U_Y  2
#define ROOM_DOOR_POS_R_X 17
#define ROOM_DOOR_POS_R_Y  9
#define ROOM_DOOR_POS_D_X  9
#define ROOM_DOOR_POS_D_Y 16
#define ROOM_DOOR_POS_L_X  1
#define ROOM_DOOR_POS_L_Y  9

#define ROOM_DOOR_U_VRAM_OFFSET 0x66
#define ROOM_DOOR_R_VRAM_OFFSET 0x6A
#define ROOM_DOOR_D_VRAM_OFFSET 0x6E
#define ROOM_DOOR_L_VRAM_OFFSET 0x72

#define ROOM_TRANSITION_FADE_SPEED  3
#define ROOM_TRANSITION_WAIT_SPEED  3
#define ROOM_TRANSITION_DOOR_SPEED 15

GLOBAL const U8 ROOM_DOOR_U_NONE[] = { 0xFF,0xFF,0xFF,0xFF,0x1F,0xE0,0x40,0x80,0x3F,0x80,0x3F,0x80,0x7F,0x80,0x3F,0xC0,0xFF,0xFF,0xFF,0xFF,0xF8,0x07,0x02,0x01,0xFC,0x01,0xFC,0x01,0xFE,0x01,0xFC,0x03,0x00,0xFF,0x7F,0x80,0x80,0x7F,0x00,0xFF,0x80,0xFF,0xFF,0xFF,0x10,0xFF,0x10,0xFF,0x00,0xFF,0xFD,0x03,0x03,0xFD,0x01,0xFF,0x03,0xFF,0xFF,0xFF,0x10,0xFF,0x10,0xFF };
GLOBAL const U8 ROOM_DOOR_R_NONE[] = { 0x22,0xFD,0x22,0xFD,0x22,0xFD,0xE2,0xFD,0x22,0xFD,0x22,0xFD,0x22,0xFD,0x34,0xFB,0x03,0xFF,0x4B,0x87,0xF3,0x07,0xF7,0x03,0xF7,0x03,0xF7,0x03,0xF7,0x03,0xF7,0x03,0x3E,0xFF,0x34,0xFB,0x22,0xFD,0xE2,0xFD,0x22,0xFD,0x22,0xFD,0x22,0xFD,0x22,0xFD,0xF7,0x03,0xF7,0x03,0xF7,0x03,0xF7,0x03,0xF7,0x03,0xF3,0x07,0x4B,0x87,0x03,0xFF };
GLOBAL const U8 ROOM_DOOR_D_NONE[] = { 0x08,0xFF,0x08,0xFF,0xFF,0xFF,0xC0,0xFF,0x80,0xFF,0xC0,0xBF,0xBF,0xC0,0x00,0xFF,0x08,0xFF,0x08,0xFF,0xFF,0xFF,0x01,0xFF,0x00,0xFF,0x01,0xFE,0xFE,0x01,0x00,0xFF,0x3F,0xC0,0x7F,0x80,0x3F,0x80,0x3F,0x80,0x40,0x80,0x1F,0xE0,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFE,0x01,0xFC,0x01,0xFC,0x01,0x02,0x01,0xF8,0x07,0xFF,0xFF,0xFF,0xFF };
GLOBAL const U8 ROOM_DOOR_L_NONE[] = { 0xC0,0xFF,0xD2,0xE1,0xCF,0xE0,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0x44,0xBF,0x44,0xBF,0x44,0xBF,0x47,0xBF,0x44,0xBF,0x44,0xBF,0x44,0xBF,0x2C,0xDF,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0xEF,0xC0,0xCF,0xE0,0xD2,0xE1,0xC0,0xFF,0x7C,0xFF,0x2C,0xDF,0x44,0xBF,0x47,0xBF,0x44,0xBF,0x44,0xBF,0x44,0xBF,0x44,0xBF };
GLOBAL const U8 ROOM_DOOR_U_OPEN[] = { 0xFF,0xFF,0xFF,0xFF,0x1F,0xE0,0x40,0x80,0x00,0x80,0x10,0x8F,0x5F,0x9F,0x7F,0x9F,0xFF,0xFF,0xFF,0xFF,0xF8,0x07,0x02,0x01,0x00,0x01,0x08,0xF1,0xFA,0xF9,0xFE,0xF9,0x7F,0x9F,0x7F,0x9F,0xBF,0xDF,0xDF,0xBF,0xBF,0xDF,0x9F,0xFF,0x9F,0xFF,0xDF,0xFF,0xFE,0xF9,0xFE,0xF9,0xFB,0xFD,0xFD,0xFB,0xFB,0xFD,0xF9,0xFF,0xF9,0xFF,0xFB,0xFF };
GLOBAL const U8 ROOM_DOOR_R_OPEN[] = { 0xFC,0xFF,0x8B,0xF4,0x17,0xE8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xFF,0xCB,0x07,0x83,0x07,0xE7,0xC3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0B,0xF4,0x97,0xE8,0xFC,0xFF,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xE7,0xC3,0x83,0x07,0xCB,0x07,0x03,0xFF };
GLOBAL const U8 ROOM_DOOR_D_OPEN[] = { 0xDF,0xFF,0x9F,0xFF,0x9F,0xFF,0xDF,0xBF,0xBF,0xDF,0xDF,0xBF,0x7F,0x9F,0x7F,0x9F,0xFB,0xFF,0xF9,0xFF,0xF9,0xFF,0xFD,0xFB,0xFB,0xFD,0xFD,0xFB,0xFE,0xF9,0xFE,0xF9,0x7F,0x9F,0x5F,0x9F,0x10,0x8F,0x00,0x80,0x40,0x80,0x1F,0xE0,0xFF,0xFF,0xFF,0xFF,0xFE,0xF9,0xFA,0xF9,0x08,0xF1,0x00,0x01,0x02,0x01,0xF8,0x07,0xFF,0xFF,0xFF,0xFF };
GLOBAL const U8 ROOM_DOOR_L_OPEN[] = { 0xC0,0xFF,0xD3,0xE0,0xC1,0xE0,0xE7,0xC3,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0x3F,0xFF,0xE9,0x17,0xD0,0x2F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE3,0xC7,0xE7,0xC3,0xC1,0xE0,0xD3,0xE0,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE8,0x17,0xD1,0x2F,0x3F,0xFF };
GLOBAL const U8 ROOM_DOOR_U_SHUT[] = { 0xFF,0xFF,0xFF,0xFF,0x1F,0xE0,0x40,0x80,0x00,0x80,0x10,0x8F,0x47,0x98,0x68,0x90,0xFF,0xFF,0xFF,0xFF,0xF8,0x07,0x02,0x01,0x00,0x01,0x08,0xF1,0xE2,0x19,0x16,0x09,0x6F,0x90,0x7F,0x90,0xB0,0xDF,0xDF,0xB0,0xB0,0xDF,0x90,0xFF,0x90,0xFF,0xD8,0xFF,0xF6,0x09,0xFE,0x09,0x0B,0xFD,0xFD,0x0B,0x0B,0xFD,0x09,0xFF,0x09,0xFF,0x1B,0xFF };
GLOBAL const U8 ROOM_DOOR_R_SHUT[] = { 0xFC,0xFF,0x8B,0xF4,0x17,0xE8,0xFE,0xFF,0x8B,0xF4,0x0B,0xF4,0x0B,0xF4,0x0B,0xF4,0x03,0xFF,0xCB,0x07,0x83,0x07,0x27,0xC3,0x87,0x63,0x47,0x23,0x47,0x23,0x47,0x23,0x0B,0xF4,0x0B,0xF4,0x0B,0xF4,0x8B,0xF4,0xFE,0xFF,0x0B,0xF4,0x97,0xE8,0xFC,0xFF,0x47,0x23,0x47,0x23,0x47,0x23,0x87,0x63,0x27,0xC3,0x83,0x07,0xCB,0x07,0x03,0xFF };
GLOBAL const U8 ROOM_DOOR_D_SHUT[] = { 0xD8,0xFF,0x90,0xFF,0x90,0xFF,0xD0,0xBF,0xBF,0xD0,0xD0,0xBF,0x7F,0x90,0x6F,0x90,0x1B,0xFF,0x09,0xFF,0x09,0xFF,0x0D,0xFB,0xFB,0x0D,0x0D,0xFB,0xFE,0x09,0xF6,0x09,0x68,0x90,0x47,0x98,0x10,0x8F,0x00,0x80,0x40,0x80,0x1F,0xE0,0xFF,0xFF,0xFF,0xFF,0x16,0x09,0xE2,0x19,0x08,0xF1,0x00,0x01,0x02,0x01,0xF8,0x07,0xFF,0xFF,0xFF,0xFF };
GLOBAL const U8 ROOM_DOOR_L_SHUT[] = { 0xC0,0xFF,0xD3,0xE0,0xC1,0xE0,0xE4,0xC3,0xE1,0xC6,0xE2,0xC4,0xE2,0xC4,0xE2,0xC4,0x3F,0xFF,0xE9,0x17,0xD0,0x2F,0x7F,0xFF,0xD1,0x2F,0xD0,0x2F,0xD0,0x2F,0xD0,0x2F,0xE2,0xC4,0xE2,0xC4,0xE2,0xC4,0xE1,0xC6,0xE4,0xC3,0xC1,0xE0,0xD3,0xE0,0xC0,0xFF,0xD0,0x2F,0xD0,0x2F,0xD0,0x2F,0xD1,0x2F,0x7F,0xFF,0xE8,0x17,0xD1,0x2F,0x3F,0xFF };

GLOBAL BOOL room_all_monsters_dead;

INTERNAL VOID room_update_doors (VOID)
{
    const U8* door_u;
    const U8* door_r;
    const U8* door_d;
    const U8* door_l;

    MROOM* room = &floor[pdata.yroom][pdata.xroom];

    door_u = ROOM_DOOR_U_NONE;
    door_r = ROOM_DOOR_R_NONE;
    door_d = ROOM_DOOR_D_NONE;
    door_l = ROOM_DOOR_L_NONE;

    /* Determine the door graphics. */
    if (room->doors & ROOM_DOOR_U) { if (room->clear) { door_u = ROOM_DOOR_U_OPEN; } else { door_u = ROOM_DOOR_U_SHUT; } }
    if (room->doors & ROOM_DOOR_R) { if (room->clear) { door_r = ROOM_DOOR_R_OPEN; } else { door_r = ROOM_DOOR_R_SHUT; } }
    if (room->doors & ROOM_DOOR_D) { if (room->clear) { door_d = ROOM_DOOR_D_OPEN; } else { door_d = ROOM_DOOR_D_SHUT; } }
    if (room->doors & ROOM_DOOR_L) { if (room->clear) { door_l = ROOM_DOOR_L_OPEN; } else { door_l = ROOM_DOOR_L_SHUT; } }

    /* Update the doors in VRAM. */
    set_bkg_data(ROOM_DOOR_U_VRAM_OFFSET,4, door_u);
    set_bkg_data(ROOM_DOOR_R_VRAM_OFFSET,4, door_r);
    set_bkg_data(ROOM_DOOR_D_VRAM_OFFSET,4, door_d);
    set_bkg_data(ROOM_DOOR_L_VRAM_OFFSET,4, door_l);
}

INTERNAL VOID room_transition (U8 dir)
{
    ACTOR* actor;

    HIDE_SPRITES;
    fade_to_black(ROOM_TRANSITION_FADE_SPEED);

    actor = a_actors;
    while (actor != (a_actors+TOTAL_NUMBER_OF_ACTORS)) {
        if (actor->cat != ACATE_PLAYER) {
            actor_deactivate(actor);
        }
        actor++;
    }

    switch (dir) {
        case (DIR_U): { pdata.yroom--; a_player->x = ITOF(ROOM_PLAYER_POS_D_X), a_player->y = ITOF(ROOM_PLAYER_POS_D_Y); } break;
        case (DIR_R): { pdata.xroom++; a_player->x = ITOF(ROOM_PLAYER_POS_L_X), a_player->y = ITOF(ROOM_PLAYER_POS_L_Y); } break;
        case (DIR_D): { pdata.yroom++; a_player->x = ITOF(ROOM_PLAYER_POS_U_X), a_player->y = ITOF(ROOM_PLAYER_POS_U_Y); } break;
        case (DIR_L): { pdata.xroom--; a_player->x = ITOF(ROOM_PLAYER_POS_R_X), a_player->y = ITOF(ROOM_PLAYER_POS_R_Y); } break;
    }
    actor_update_sprite_pos(a_player);

    /* Generate a random layout for the room. */
    if (!floor[pdata.yroom][pdata.xroom].clear) {
        switch (((U8)rand()) % 6) {
            case (0): {
                // Nothing...
            } break;
            case (1): {
                actor_create(ATYPE_GAPER, 72, 72);
            } break;
            case (2): {
                actor_create(ATYPE_GAPER, 56, 72);
                actor_create(ATYPE_GAPER, 72, 72);
                actor_create(ATYPE_GAPER, 88, 72);
            } break;
            case (3): {
                actor_create(ATYPE_GAPER, 72, 56);
                actor_create(ATYPE_GAPER, 56, 72);
                actor_create(ATYPE_GAPER, 88, 72);
                actor_create(ATYPE_GAPER, 72, 88);
            } break;
            case (4): {
                actor_create(ATYPE_GAPER, 72, 56);
                actor_create(ATYPE_GAPER, 72, 72);
                actor_create(ATYPE_GAPER, 72, 88);
            } break;
            case (5): {
                // @Incomplete: ...
            } break;
        }
    }

    /* This will mark the room clear if it's has no monsters in. */
    room_all_monsters_dead = FALSE;
    room_tick();

    /* Hacky way to get all doors to be open no matter what. */
    room_all_monsters_dead = floor[pdata.yroom][pdata.xroom].clear;
    floor[pdata.yroom][pdata.xroom].clear = TRUE;
    room_update_doors();
    floor[pdata.yroom][pdata.xroom].clear = room_all_monsters_dead;

    WAIT(ROOM_TRANSITION_WAIT_SPEED);

    /* If it's a boss room then that's the end of the game! */
    if (floor[pdata.yroom][pdata.xroom].type == ROOM_TYPE_BOSS) {
        SET_BKG_DATA(TILESET_ENDGAME);
        SET_MAP_DATA(TILEMAP_ENDGAME);

        actor = a_actors;
        while (actor != (a_actors+TOTAL_NUMBER_OF_ACTORS)) {
            actor_deactivate(actor);
            actor++;
        }

        WAIT(60);

        fade_from_black(END_GAME_FADE_SPEED);
        JOYPAD_WAIT_ANY;
        fade_to_black(END_GAME_FADE_SPEED);

        reset_flag = TRUE;
    } else {
        fade_from_black(ROOM_TRANSITION_FADE_SPEED);

        SHOW_SPRITES;

        /* If the room has enemies then wait a bit longer and show the doors shutting. */
        room_all_monsters_dead = floor[pdata.yroom][pdata.xroom].clear;
        if (!room_all_monsters_dead) {
            WAIT(ROOM_TRANSITION_DOOR_SPEED);
            room_update_doors();
        }
    }
}

INTERNAL VOID room_tick (VOID)
{
    /* Once all monsters are dead mark the room as clear and open the doors. */
    if (!room_all_monsters_dead) {
        ACTOR* actor = a_monsters;
        room_all_monsters_dead = TRUE;
        while (actor != a_monsters+TOTAL_NUMBER_OF_MONSTERS) {
            if (actor->state != ASTAT_DEAD) {
                if (actor->active) {
                    room_all_monsters_dead = FALSE;
                    break;
                }
            }
            actor++;
        }
        if (room_all_monsters_dead) {
            floor[pdata.yroom][pdata.xroom].clear = TRUE;
            room_update_doors();
        }
    }
}

INTERNAL BOOL room_current_clear (VOID)
{
    return floor[pdata.yroom][pdata.xroom].clear;
}

INTERNAL BOOL room_has_door_u (VOID)
{
    return (floor[pdata.yroom][pdata.xroom].doors & ROOM_DOOR_U);
}
INTERNAL BOOL room_has_door_r (VOID)
{
    return (floor[pdata.yroom][pdata.xroom].doors & ROOM_DOOR_R);
}
INTERNAL BOOL room_has_door_l (VOID)
{
    return (floor[pdata.yroom][pdata.xroom].doors & ROOM_DOOR_L);
}
INTERNAL BOOL room_has_door_d (VOID)
{
    return (floor[pdata.yroom][pdata.xroom].doors & ROOM_DOOR_D);
}

/*////////////////////////////////////////////////////////////////////////////*/
