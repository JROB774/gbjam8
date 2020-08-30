/*////////////////////////////////////////////////////////////////////////////*/

/* An actor is any entity within the world (player, monster, item, etc.).     */

typedef const struct _ABASE_  ABASE;
typedef const struct _ASTATE_ ASTATE;

typedef struct _ACTOR_
{
    ASTATE* state;       /* Pointer into ASTATE_TABLE containing state info.  */
    ABASE*  base;        /* Pointer into ABASE_TABLE containing general info. */
    U8      type_id;     /* Identifier for the type of actor.                 */
    U8      state_id;    /* Identifier for the current actor state.           */
    U8      slot;        /* Starting slot in OAM for the meta-sprite data.    */
    U8      x, y;        /* Current (X,Y) position in the world.              */
    U8      state_timer; /* Timer used to track when state should be changed. */
    BOOL    active;      /* Whether the actor is currently active or not. If  */
                         /* an actor is not active then it can be replaced.   */
} ACTOR;

/* Unique identifiers for all the different actor types in the game.          */

#define ATYPE_UNKNOWN           0x00
#define ATYPE_PLAYER            0x01
#define ATYPE_GAPER             0x02
#define ATYPE_GUSHER            0x03 /* @UNIMPLEMENTED */
#define ATYPE_HORF              0x04 /* @UNIMPLEMENTED */
#define ATYPE_CLOTTY            0x05 /* @UNIMPLEMENTED */
#define ATYPE_MULLIGAN          0x06 /* @UNIMPLEMENTED */
#define ATYPE_ATTACKFLY         0x07 /* @UNIMPLEMENTED */
#define ATYPE_HOPPER            0x08 /* @UNIMPLEMENTED */
#define ATYPE_TEAR              0x09 /* @UNIMPLEMENTED */
#define ATYPE_BLOODTEAR         0x0A /* @UNIMPLEMENTED */
#define ATYPE_COIN              0x0B /* @UNIMPLEMENTED */
#define ATYPE_BOMB              0x0C /* @UNIMPLEMENTED */
#define ATYPE_KEY               0x0D /* @UNIMPLEMENTED */
#define ATYPE_HEART             0x0E /* @UNIMPLEMENTED */
#define ATYPE_MONSTRO           0x0F /* @UNIMPLEMENTED */

/* All of the different states for the different types of actors.             */

#define ASTATE_UNKNOWN_IDLE     0x00
#define ASTATE_PLAYER_IDLE      0x00
#define ASTATE_PLAYER_MOVE_U_0  0x01
#define ASTATE_PLAYER_MOVE_U_1  0x02
#define ASTATE_PLAYER_MOVE_R_0  0x03
#define ASTATE_PLAYER_MOVE_R_1  0x04
#define ASTATE_PLAYER_MOVE_D_0  0x05
#define ASTATE_PLAYER_MOVE_D_1  0x06
#define ASTATE_PLAYER_MOVE_L_0  0x07
#define ASTATE_PLAYER_MOVE_L_1  0x08
#define ASTATE_GAPER_MOVE_0     0x00
#define ASTATE_GAPER_MOVE_1     0x01
#define ASTATE_GUSHER_MOVE_0    0x01
#define ASTATE_GUSHER_MOVE_1    0x02
#define ASTATE_HORF_IDLE        0x00
#define ASTATE_HORF_FIRE        0x01
#define ASTATE_CLOTTY_MOVE_0    0x00
#define ASTATE_CLOTTY_MOVE_1    0x01
#define ASTATE_CLOTTY_FIRE      0x02
#define ASTATE_MULLIGAN_MOVE_0  0x00
#define ASTATE_MULLIGAN_MOVE_1  0x01
#define ASTATE_ATTACKFLY_MOVE_0 0x00
#define ASTATE_ATTACKFLY_MOVE_1 0x01
#define ASTATE_HOPPER_MOVE_0    0x00
#define ASTATE_HOPPER_MOVE_1    0x01

/* Predeclare all the custom actor actions for the ASTATE_TABLE.              */

INTERNAL void player_update (ACTOR* actor);
INTERNAL void  gaper_update (ACTOR* actor);

/* The following table contains generic information for each actor type. This */
/* information is the same across all instances of the particular actor type. */

typedef const struct _ABASE_
{
    U8 offset;  /* Base offset into the ASTATE_TABLE for the actor type.      */
    U8 spr_w;   /* Meta-sprite width in tiles for the actor.                  */
    U8 spr_h;   /* Meta-sprite height in tiles for the actor.                 */

} ABASE;

GLOBAL const ABASE ABASE_TABLE[] =
{
/* offset  spr_w  spr_h                                                       */
{  0x00,   0x00,  0x00  }, /* ATYPE_UNKNOWN                                   */
{  0x01,   0x02,  0x02  }, /* ATYPE_PLAYER                                    */
{  0x0A,   0x02,  0x02  }  /* ATYPE_GAPER                                     */
};

/* The following table contains all the unique actor states. These states are */
/* what decide what animation/frame to currently play, what extended actor    */
/* logic should be carried out, etc. Looking up a particular state is done by */
/* taking an actors base offset into the table and then adding the value for  */
/* the state you would like to retrieve from the table, like so:              */
/*                                                                            */
/*   U8 offset = my_actor->base->offset + my_actor->state_id;                 */
/*                                                                            */
/* This code gives the offset into ASTATE_TABLE for the actors current state. */

#define FLIP_NONE (0x00   )
#define FLIP_HORZ (S_FLIPX)
#define FLIP_VERT (S_FLIPY)

typedef void(*AACTION)(ACTOR* actor);

typedef const struct _ASTATE_
{
    AACTION action;  /* Extra logic to invoke on the actor's update.          */
    U8 vram_offset;  /* Offset into VRAM for this state's frame data.         */
    U8 ticks;        /* Number of ticks before changing to next_state.        */
    U8 flip;         /* Whether to flip sprites in the X/Y direction.         */
    U8 next_state;   /* Next state to transition to after this one.           */

} ASTATE;

GLOBAL const ASTATE ASTATE_TABLE[] =
{
/* ATYPE_UNKNOWN                                                              */
/* action          vram_offset  ticks  flip        next_state                 */
{  NULL,           0x00,        0,     FLIP_NONE,  ASTATE_UNKNOWN_IDLE     },
/* ATYPE_PLAYER                                                               */
/* action          vram_offset  ticks  flip        next_state                 */
{  player_update,  0x01,        0,     FLIP_NONE,  ASTATE_PLAYER_IDLE      },
{  player_update,  0x15,        15,    FLIP_NONE,  ASTATE_PLAYER_MOVE_U_1  },
{  player_update,  0x15,        15,    FLIP_HORZ,  ASTATE_PLAYER_MOVE_U_0  },
{  player_update,  0x0D,        15,    FLIP_NONE,  ASTATE_PLAYER_MOVE_R_1  },
{  player_update,  0x11,        15,    FLIP_NONE,  ASTATE_PLAYER_MOVE_R_0  },
{  player_update,  0x05,        15,    FLIP_NONE,  ASTATE_PLAYER_MOVE_D_1  },
{  player_update,  0x09,        15,    FLIP_NONE,  ASTATE_PLAYER_MOVE_D_0  },
{  player_update,  0x0D,        15,    FLIP_HORZ,  ASTATE_PLAYER_MOVE_L_1  },
{  player_update,  0x11,        15,    FLIP_HORZ,  ASTATE_PLAYER_MOVE_L_0  },
/* ATYPE_GAPER                                                                */
/* action          vram_offset  ticks  flip        next_state                 */
{  gaper_update,   0x19,        20,    FLIP_NONE,  ASTATE_GAPER_MOVE_1     },
{  gaper_update,   0x19,        20,    FLIP_HORZ,  ASTATE_GAPER_MOVE_0     },
};

/*////////////////////////////////////////////////////////////////////////////*/

#define MAX_NUMBER_OF_ACTORS 0x28 /* (40) The same as max sprite number. */

GLOBAL ACTOR actor_list[MAX_NUMBER_OF_ACTORS];

INTERNAL void actor_set_state (ACTOR* actor, U8 state_id)
{
    /* Set the new state and update the actor's sprites accordingly. */
    actor->state = &ASTATE_TABLE[actor->base->offset + state_id];
    actor->state_timer = 0;
    actor->state_id = state_id;
    for (j=0; j<(actor->base->spr_w*actor->base->spr_h); ++j) {
        set_sprite_tile(actor->slot+j, actor->state->vram_offset+j);
        set_sprite_prop(actor->slot+j, actor->state->flip);
    }
}

INTERNAL void actor_set_pos (ACTOR* actor, U8 x, U8 y)
{
    U8 ix,iy;

    actor->x = x;
    actor->y = y;

    x += (TILE_WIDTH     );
    y += (TILE_HEIGHT * 2);

    switch (actor->state->flip) {
        case (FLIP_NONE): {
            for (j=0,iy=0; j<actor->base->spr_h; ++iy,++j) {
                for (k=0,ix=0; k<actor->base->spr_w; ++ix,++k) {
                    move_sprite(actor->slot+(j*actor->base->spr_w+k), x+(ix*TILE_WIDTH), y+(iy*TILE_HEIGHT));
                }
            }
        } break;
        case (FLIP_HORZ): {
            for (j=0,iy=0; j<actor->base->spr_h; ++iy,++j) {
                for (k=0,ix=actor->base->spr_w-1; k<actor->base->spr_w; --ix,++k) {
                    move_sprite(actor->slot+(j*actor->base->spr_w+k), x+(ix*TILE_WIDTH), y+(iy*TILE_HEIGHT));
                }
            }
        } break;
        case (FLIP_VERT): {
            for (j=0,iy=actor->base->spr_h-1; j<actor->base->spr_h; --iy,++j) {
                for (k=0,ix=0; k<actor->base->spr_w; ++ix,++k) {
                    move_sprite(actor->slot+(j*actor->base->spr_w+k), x+(ix*TILE_WIDTH), y+(iy*TILE_HEIGHT));
                }
            }
        } break;
    }
}

INTERNAL void actor_create (U8 index, U8 type_id, U8 state_id, U8 x, U8 y)
{
    ACTOR* actor = &actor_list[index];

    actor->base        = &ABASE_TABLE[type_id];
    actor->type_id     = type_id;
    actor->slot        = index;
    actor->state_timer = 0;
    actor->active      = TRUE;

    actor_set_state(actor, state_id);
    actor_set_pos(actor, x, y);
}

INTERNAL void actor_update (ACTOR* actor)
{
    U8 state_index = actor->base->offset + actor->state_id;

    /* Perform specific logic for the actor. */
    if (actor->state->action) {
        actor->state->action(actor);
    }
    /* Update the actor's state when necessary. */
    actor->state_timer++;
    if (actor->state_timer >= actor->state->ticks) {
        actor_set_state(actor, actor->state->next_state);
    }
    /* Update the actor's final position. */
    actor_set_pos(actor, actor->x, actor->y);
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
