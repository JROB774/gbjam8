/*////////////////////////////////////////////////////////////////////////////*/

/* Unique identifiers for all the different actor types in the game.          */
#define ACTORTYPE_UNKNOWN  0x00
#define ACTORTYPE_PLAYER   0x01
#define ACTORTYPE_GAPER    0x02

/* All of the different states for the different types of actors. Actors will */
/* not necessarily implement all of the states listed so not all states will  */
/* work with all actors. For example some states are PLAYER actor specific.   */
#define ACTORSTATE_IDLE    0x00

/* A collection of sprites in OAM that create a larger meta-sprite.           */
typedef struct _METASPRITE_
{
    U8 slot;             /* Starting slot in OAM for the meta-sprite.         */
    U8 w, h;             /* Size dimensions (W,H) for the meta-sprite.        */

} METASPRITE;

/* Information regarding the current state of a particular actor.             */
typedef struct _ACTORSTATE_
{
    U8 vram_offset;      /* Offset into VRAM for this state's frame data.     */
    U8 ticks;            /* Number of ticks before changing to next_state.    */
    U8 next_state;       /* Next state to transition to after this one.       */

} ACTORSTATE;

/* An actor is any entity within the world (player,enemy,item,etc.).          */
typedef struct _ACTOR_
{
    METASPRITE sprite;   /* Meta-sprite information for the actor instance.   */
    U8   type;           /* Identifier for the type of actor.                 */
    U8   state;          /* Identifier for the current actor state.           */
    U8   x, y;           /* Current (X,Y) position in the world.              */
    U8   state_timer;    /* Timer used to track when state should be changed. */
    BOOL active;         /* Whether the actor is currently active or not.     */

} ACTOR;

/* This table contains meta-sprite widths for all of the actor types.         */
GLOBAL const U8 METASPRITE_WIDTH_TABLE[] =
{
0x00, /* ACTORTYPE_UNKNOWN                                                    */
0x02, /* ACTORTYPE_PLAYER                                                     */
0x02, /* ACTORTYPE_GAPER                                                      */
};
/* This table contains meta-sprite heights for all of the actor types.        */
GLOBAL const U8 METASPRITE_HEIGHT_TABLE[] =
{
0x00, /* ACTORTYPE_UNKNOWN                                                    */
0x02, /* ACTORTYPE_PLAYER                                                     */
0x02, /* ACTORTYPE_GAPER                                                      */
};

/* Offsets into the ACTORSTATE_TABLE for each of the unique ACTORTYPES. These */
/* offsets act as the start of sub-list within the ACTORSTATE_TABLE for each  */
/* of a particular type of actors unique states. These offsets are looked up  */
/* using the ACTORTYPE making for an easy method of retrieving the offset.    */
GLOBAL const U8 ACTORSTATE_OFFSET_TABLE[] =
{
0x00, /* ACTORTYPE_UNKNOWN                                                    */
0x01, /* ACTORTYPE_PLAYER                                                     */
0x02, /* ACTORTYPE_GAPER                                                      */
};

/* This table contains every single different actor state in the game as one  */
/* large lookup table. The method for looking up a particular actors current  */
/* state information in this table can be done using the following method:    */
/*                                                                            */
/*   offset = ACTORSTATE_OFFSET_TABLE[actor.type] + actor.state;              */
/*                                                                            */
GLOBAL const ACTORSTATE ACTORSTATE_TABLE[] =
{
/* ACTORTYPE_UNKNOWN                                                          */
/* vram_offset  ticks  next_state                                             */
{  0x00,        0,     ACTORSTATE_IDLE }, /* ACTORSTATE_IDLE                  */
/* ACTORTYPE_PLAYER                                                           */
/* vram_offset  ticks  next_state                                             */
{  0x01,        0,     ACTORSTATE_IDLE }, /* ACTORSTATE_IDLE                  */
// ACTORTYPE_GAPER                                                            */
// vram_offset  ticks  next_state                                             */
{  0x05,        0,     ACTORSTATE_IDLE }, /* ACTORSTATE_IDLE                  */
};

/*////////////////////////////////////////////////////////////////////////////*/

#define MAX_NUMBER_OF_ACTORS 0x28 /* (40) The same as max sprite number. */

GLOBAL ACTOR actor_list[MAX_NUMBER_OF_ACTORS];

INTERNAL void actor_set_state (ACTOR* actor, U8 state)
{
    /* Set the new state and update the actor's sprites accordingly. */
    U8 state_index = ACTORSTATE_OFFSET_TABLE[actor->type] + state;
    actor->state_timer = 0;
    actor->state = state;
    for (i=0; i<(actor->sprite.w*actor->sprite.h); ++i) {
        set_sprite_tile(actor->sprite.slot+i, ACTORSTATE_TABLE[state_index].vram_offset+i);
    }
}

INTERNAL void actor_set_pos (ACTOR* actor, U8 x, U8 y)
{
    actor->x = x;
    actor->y = y;

    x += (TILE_WIDTH     );
    y += (TILE_HEIGHT * 2);

    for (i=0; i<actor->sprite.h; ++i) {
        for (j=0; j<actor->sprite.w; ++j) {
            move_sprite(actor->sprite.slot+(i*actor->sprite.w+j), x+(j*TILE_WIDTH), y+(i*TILE_HEIGHT));
        }
    }
}

INTERNAL void actor_create (U8 index, U8 type, U8 state, U8 x, U8 y)
{
    ACTOR* actor = &actor_list[index];

    actor->type        = type;
    actor->sprite.slot = index;
    actor->sprite.w    = METASPRITE_WIDTH_TABLE[type];
    actor->sprite.h    = METASPRITE_HEIGHT_TABLE[type];
    actor->state_timer = 0;
    actor->active      = TRUE;

    actor_set_state(actor, state);
    actor_set_pos(actor, x, y);
}

INTERNAL void actor_update (ACTOR* actor)
{
    /* Update the actor's state when necessary. */
    U8 state_index = ACTORSTATE_OFFSET_TABLE[actor->type] + actor->state;
    actor->state_timer++;
    if (actor->state_timer >= ACTORSTATE_TABLE[state_index].ticks) {
        actor_set_state(actor, ACTORSTATE_TABLE[state_index].next_state);
    }
}

INTERNAL void actor_update_all ()
{
    /* Go through the list and update all of the active actors. */
    for (i=0; i<MAX_NUMBER_OF_ACTORS; ++i) {
        ACTOR* actor = &actor_list[i];
        if (actor->active) {
            actor_update(actor);
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
