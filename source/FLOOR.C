/*////////////////////////////////////////////////////////////////////////////*/

#define MAX_FLOOR_WIDTH  0x06
#define MAX_FLOOR_HEIGHT 0x07

#define MIN_FLOOR_ROOMS  0x05
#define MAX_FLOOR_ROOMS  0x0A

#define ROOM_TYPE_NONE   0x00
#define ROOM_TYPE_START  0x01
#define ROOM_TYPE_NORMAL 0x02
#define ROOM_TYPE_ITEM   0x03
#define ROOM_TYPE_BOSS   0x04

#define ROOM_DOOR_U      0x01
#define ROOM_DOOR_R      0x02
#define ROOM_DOOR_D      0x04
#define ROOM_DOOR_L      0x08

typedef struct _MROOM_
{
    U8   type;   /* Identifier stating what type of room it is.      */
    U8   layout; /* Identifier for what layout the room is using.    */
    U8   doors;  /* Flags representing what doors the room has.      */
    BOOL clear;  /* States whether the room has been cleared or not. */

} MROOM;

GLOBAL MROOM floor[MAX_FLOOR_HEIGHT][MAX_FLOOR_WIDTH];
GLOBAL U8 gen_count;

INTERNAL BOOL generate_no_diagonals (U8 x, U8 y, U8 dir)
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

INTERNAL VOID generate_room_doors (U8 x, U8 y)
{
    /* Generate doors at the four possible directions if possible. */
    MROOM* room = &floor[y][x];
    if ((y != (                 0)) && (((U8)rand()) % 2 == 0) && (generate_no_diagonals(x,y,ROOM_DOOR_U))) { room->doors |= ROOM_DOOR_U; }
    if ((x != (MAX_FLOOR_WIDTH -1)) && (((U8)rand()) % 2 == 0) && (generate_no_diagonals(x,y,ROOM_DOOR_R))) { room->doors |= ROOM_DOOR_R; }
    if ((y != (MAX_FLOOR_HEIGHT-1)) && (((U8)rand()) % 2 == 0) && (generate_no_diagonals(x,y,ROOM_DOOR_D))) { room->doors |= ROOM_DOOR_D; }
    if ((x != (                 0)) && (((U8)rand()) % 2 == 0) && (generate_no_diagonals(x,y,ROOM_DOOR_L))) { room->doors |= ROOM_DOOR_L; }
}

INTERNAL BOOL generate_room_neighbors (U8 x, U8 y)
{
    /* Generate a room at a given direction if there is a door there. */
    MROOM* room = &floor[y][x];
    BOOL generated = FALSE;
    if ((room->doors & ROOM_DOOR_U) && (floor[y-1][x].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_no_diagonals(x,y,ROOM_DOOR_U)) {
            generate_room(x,y-1);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_U);
        }
    }
    if ((room->doors & ROOM_DOOR_R) && (floor[y][x+1].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_no_diagonals(x,y,ROOM_DOOR_R)) {
            generate_room(x+1,y);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_R);
        }
    }
    if ((room->doors & ROOM_DOOR_D) && (floor[y+1][x].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_no_diagonals(x,y,ROOM_DOOR_D)) {
            generate_room(x,y+1);
            generated = TRUE;
        } else {
            UNSET_FLAGS(room->doors, ROOM_DOOR_D);
        }
    }
    if ((room->doors & ROOM_DOOR_L) && (floor[y][x-1].type == ROOM_TYPE_NONE)) {
        /* If there are diagonals then we can't put a room and just remove the door. */
        if (generate_no_diagonals(x,y,ROOM_DOOR_L)) {
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

    /* We will keep generating floors until we get one that fulfills all our rules. */
    while (TRUE) {
        /* Reset the floor in case there was a previous one. */
        gen_count = 0;
        for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
            for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
                floor[iy][ix].type   = ROOM_TYPE_NONE;
                floor[iy][ix].layout = 0x00;
                floor[iy][ix].doors  = 0x00;
                floor[iy][ix].clear  = FALSE;
            }
        }

        /* Determine the location of the starting room. */
        /* Start rooms cannot be at the edge of the map. */
        sx = ((U8)rand()) % (MAX_FLOOR_WIDTH -2) + 1;
        sy = ((U8)rand()) % (MAX_FLOOR_HEIGHT-2) + 1;

        floor[sy][sx].type = ROOM_TYPE_START;

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
        /* If we are within the floor limits then we are done. */
        if ((gen_count >= MIN_FLOOR_ROOMS) && (gen_count <= MAX_FLOOR_ROOMS)) {
            break;
        }
    }

    /* Go through and add and remove doors where needed. */
    for (iy=0; iy<MAX_FLOOR_HEIGHT; ++iy) {
        for (ix=0; ix<MAX_FLOOR_WIDTH; ++ix) {
            // @Incomplete: ...
        }
    }

    /* Debug print out the floor. */
    #if 1
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
