/*////////////////////////////////////////////////////////////////////////////*/

/* An actor is any entity within the world (player, monster, item, etc.). *****/

typedef VOID(*ATICK)(ACTOR* actor);

typedef struct _ACTOR_
{
    ATICK tick;   /* Custom behaviour for an actor that runs every tick.      */
    FIXED x,y;    /* Current (X,Y) position as fixed-point values.            */
    U16   hp;     /* Health points for the actor (not used by all actors).    */
    U8    flags;  /* Flags that define aspects of an entity.          (AFLAG) */
    U8    type;   /* Identifier for the type of actor.                (ATYPE) */
    U8    state;  /* Identifier for the current actor state.          (ASTAT) */
    U8    animi;  /* Identifier for the current actor animation.      (AANIM) */
    U8    animf;  /* The current frame of the animation being player.         */
    U8    animt;  /* Timer for the current animation frame.                   */
    U8    slot;   /* Starting slot in OAM for the actor's sprite data.        */
    FIXED ext0;   /* Can be used to represent extra/custom data.              */
    FIXED ext1;   /* Can be used to represent extra/custom data.              */
    FIXED ext2;   /* Can be used to represent extra/custom data.              */
    FIXED ext3;   /* Can be used to represent extra/custom data.              */
    BOOL  active; /* Whether the actor is currently active or not. An actor   */
                  /* that is not active can be replaced with a new actor.     */
} ACTOR;

/* Flags that control generic aspects of an entity type or instance. **********/

#define AFLAG_NONE        0x00 /* No flags set.                               */
#define AFLAG_UNBOUND     0x01 /* The actor is not bound to the room.         */
#define AFLAG_NOANIM      0x02 /* The actor is not animated.                  */
#define AFLAG_HOSTILE     0x04 /* The actor can be hurt by the player.        */
#define AFLAG_FLYING      0x08 /* The actor is flying.                        */
#define AFLAG_NODAMAGE    0x10 /* The actor cannot take any damage.           */
#define AFLAG_BOSS        0x20 /* The actor is a boss (show health bar).      */

/* Unique identifiers for all the different actor types in the game. **********/

#define ATYPE_PLAYER      0x00
#define ATYPE_GAPER       0x01

/* All of the different actor states (not all actors implement all states). ***/

#define ASTAT_IDLE        0x00 /* The actor is not doing anything.            */
#define ASTAT_MOVE        0x01 /* The actor is moving around.                 */
#define ASTAT_FIRE        0x02 /* The actor is firing a shot.                 */
#define ASTAT_HURT        0x03 /* The actor has been hurt by something.       */
#define ASTAT_DEAD        0x04 /* The actor has been killed.                  */
#define ASTAT_GETI        0x05 /* The actor got an item (ATYPE_PLAYER).       */

/* A list of all of the different meta-sprites used by actor animations. ******/

#define AATTR_NONE        0x00
#define AATTR_PAL1        S_PALETTE
#define AATTR_FLPX        S_FLIPX
#define AATTR_FLPY        S_FLIPY
#define AATTR_HIGH        S_PRIORITY

#define AMSPR_PLAYER_I0   0x00
#define AMSPR_PLAYER_MU0  0x05
#define AMSPR_PLAYER_MU1  0x0A
#define AMSPR_PLAYER_MR0  0x0F
#define AMSPR_PLAYER_MR1  0x14
#define AMSPR_PLAYER_MD0  0x19
#define AMSPR_PLAYER_MD1  0x1E
#define AMSPR_PLAYER_ML0  0x23
#define AMSPR_PLAYER_ML1  0x28
#define AMSPR_PLAYER_H0   0x2D
#define AMSPR_PLAYER_D0   0x32
#define AMSPR_PLAYER_G0   0x37
#define AMSPR_GAPER_M0    0x3C
#define AMSPR_GAPER_M1    0x41

GLOBAL const U8 AMSPR_TABLE[/*(AMSPR)*/] =
{
/* number_of_sprites, sprite_number, sprite_attribs, ...                      */
0x02,  0x00,AATTR_NONE, 0x02,AATTR_NONE, /* AMSPR_PLAYER_I0                   */
0x02,  0x04,AATTR_NONE, 0x06,AATTR_NONE, /* AMSPR_PLAYER_MU0                  */
0x02,  0x06,AATTR_FLPX, 0x04,AATTR_FLPX, /* AMSPR_PLAYER_MU1                  */
0x02,  0x08,AATTR_NONE, 0x0A,AATTR_NONE, /* AMSPR_PLAYER_MR0                  */
0x02,  0x0C,AATTR_NONE, 0x0E,AATTR_NONE, /* AMSPR_PLAYER_MR1                  */
0x02,  0x10,AATTR_NONE, 0x12,AATTR_NONE, /* AMSPR_PLAYER_MD0                  */
0x02,  0x14,AATTR_NONE, 0x16,AATTR_NONE, /* AMSPR_PLAYER_MD1                  */
0x02,  0x0A,AATTR_FLPX, 0x08,AATTR_FLPX, /* AMSPR_PLAYER_ML0                  */
0x02,  0x0E,AATTR_FLPX, 0x0C,AATTR_FLPX, /* AMSPR_PLAYER_ML1                  */
0x02,  0x18,AATTR_NONE, 0x1A,AATTR_NONE, /* AMSPR_PLAYER_H0                   */
0x02,  0x1C,AATTR_NONE, 0x1C,AATTR_FLPX, /* AMSPR_PLAYER_D0                   */
0x02,  0x1E,AATTR_NONE, 0x20,AATTR_NONE, /* AMSPR_PLAYER_G0                   */
0x02,  0x22,AATTR_NONE, 0x24,AATTR_NONE, /* AMSPR_GAPER_M0                    */
0x02,  0x24,AATTR_FLPX, 0x22,AATTR_FLPX, /* AMSPR_GAPER_M1                    */
};

/* All of the different animations for the different actor types. *************/

#define AANIM_PLAYER_I    0x00
#define AANIM_PLAYER_MU   0x04
#define AANIM_PLAYER_MR   0x0A
#define AANIM_PLAYER_MD   0x10
#define AANIM_PLAYER_ML   0x16
#define AANIM_PLAYER_H    0x1C
#define AANIM_PLAYER_D    0x20
#define AANIM_PLAYER_G    0x14
#define AANIM_GAPER_M     0x28

GLOBAL const U8 AANIM_TABLE[/*(AANIM)*/] =
{
/* number_of_frames, loop, frame_metasprite, frame_ticks, ...                 */
0x01,  TRUE ,  AMSPR_PLAYER_I0 ,255,                      /* AANIM_PLAYER_I   */
0x02,  TRUE ,  AMSPR_PLAYER_MU0, 20, AMSPR_PLAYER_MU1,20, /* AANIM_PLAYER_MU  */
0x02,  TRUE ,  AMSPR_PLAYER_MR0, 20, AMSPR_PLAYER_MR1,20, /* AANIM_PLAYER_MR  */
0x02,  TRUE ,  AMSPR_PLAYER_MD0, 20, AMSPR_PLAYER_MD1,20, /* AANIM_PLAYER_MD  */
0x02,  TRUE ,  AMSPR_PLAYER_ML0, 20, AMSPR_PLAYER_ML1,20, /* AANIM_PLAYER_ML  */
0x01,  FALSE,  AMSPR_PLAYER_H0 , 50,                      /* AANIM_PLAYER_H   */
0x01,  FALSE,  AMSPR_PLAYER_D0 , 50,                      /* AANIM_PLAYER_D   */
0x01,  FALSE,  AMSPR_PLAYER_G0 ,120,                      /* AANIM_PLAYER_G   */
0x02,  TRUE ,  AMSPR_GAPER_M0  , 20, AMSPR_GAPER_M1  ,20, /* AANIM_GAPER_M    */
};

/* A list containing base information about each particular actor type. *******/

typedef struct _ABASE_
{
    ATICK tick;  /* The tick function for the particular actor type.          */
    U16   hp;    /* The starting health points for the actor type.            */
    U8    state; /* The starting state for the actor type.                    */
    U8    anim;  /* The starting animation for the actor type.                */
    U8    flags; /* The general flags for the actor type.                     */

} ABASE;

GLOBAL const ABASE ABASE_TABLE[/*(ATYPE)*/] =
{
/* tick_function, start_hp, start_state, start_anim, flags                    */
{A_PLAYER,    0, ASTAT_IDLE, AANIM_PLAYER_I, AFLAG_NONE   }, /* ATYPE_PLAYER  */
{A_GAPER ,  100, ASTAT_MOVE, AANIM_GAPER_M , AFLAG_HOSTILE}, /* ATYPE_GAPER   */
};

/* The actor manager system that handles creating, destroying, and managing. **/

#define GET_AMSPR_SIZE(  actor   ) AMSPR_TABLE[GET_AANIM_FRAME(actor)]
#define GET_AMSPR_SPR(   actor, i) AMSPR_TABLE[GET_AANIM_FRAME(actor)+1+(i<<1)]
#define GET_AMSPR_ATTR(  actor, i) AMSPR_TABLE[GET_AANIM_FRAME(actor)+1+(i<<1)+1]
#define GET_AANIM_FRAME( actor   ) AANIM_TABLE[actor->animi+2+(actor->animf<<1)]
#define GET_AANIM_FRAMET(actor   ) AANIM_TABLE[actor->animi+2+(actor->animf<<1)+1]
#define GET_AANIM_LENGTH(actor   ) AANIM_TABLE[actor->animi]
#define GET_AANIM_LOOP(  actor   ) AANIM_TABLE[actor->animi+1]

#define MAX_NUMBER_OF_ACTORS 0x28 /* (40) The same as max sprite number. */

GLOBAL ACTOR actor_list[MAX_NUMBER_OF_ACTORS];
GLOBAL U8    actor_list_ptr = 0;

INTERNAL VOID actor_create (U8 type, U8 x, U8 y)
{
    ACTOR* actor;
    U8 i;

    actor = &actor_list[actor_list_ptr];

    actor->tick   = ABASE_TABLE[type].tick;
    actor->x      = ITOF(x);
    actor->y      = ITOF(y);
    actor->hp     = ABASE_TABLE[type].hp;
    actor->flags  = ABASE_TABLE[type].flags;
    actor->type   = type;
    actor->state  = ABASE_TABLE[type].state;
    actor->animi  = ABASE_TABLE[type].anim;
    actor->animf  = 0;
    actor->animt  = 0;
    actor->slot   = actor_list_ptr;
    actor->active = TRUE;

    for (i=0; i<GET_AMSPR_SIZE(actor); ++i) {
        set_sprite_tile(actor->slot+i, GET_AMSPR_SPR(actor,i));
        set_sprite_prop(actor->slot+i, GET_AMSPR_ATTR(actor,i));
    }

    actor_list_ptr += 2; /* @Temporary!!! */
}

INTERNAL BOOL actor_anim_done (ACTOR* actor)
{
    return ((!GET_AANIM_LOOP(actor)) && (actor->animf == GET_AANIM_LENGTH(actor)-1) && (actor->animt >= GET_AANIM_FRAMET(actor)));
}

INTERNAL VOID actor_anim_change (ACTOR* actor, U8 anim, BOOL reset)
{
    U8 i;
    actor->animi = anim;
    if (reset) {
        actor->animf = 0;
        actor->animt = 0;
    }
    for (i=0; i<GET_AMSPR_SIZE(actor); ++i) {
        set_sprite_tile(actor->slot+i, GET_AMSPR_SPR(actor,i));
        set_sprite_prop(actor->slot+i, GET_AMSPR_ATTR(actor,i));
    }
}

INTERNAL VOID actor_tick_all (VOID)
{
    ACTOR* actor;
    U8 i,j;

    /* Go through the list and update all of the active actors. */
    for (i=0; i<MAX_NUMBER_OF_ACTORS; ++i) {
        actor = &actor_list[i];
        if (actor->active) {
            /* Update the actor's current animation, if they are animated. */
            if (!(actor->flags & AFLAG_NOANIM)) {
                if (!actor_anim_done(actor)) {
                    actor->animt++;
                    if (actor->animt >= GET_AANIM_FRAMET(actor)) {
                        actor->animt = 0;
                        actor->animf++;
                        if (actor->animf >= GET_AANIM_LENGTH(actor)) {
                            if (GET_AANIM_LOOP(actor)) {
                                actor->animf = 0;
                            } else {
                                actor->animt = 0xFF;
                                actor->animf--;
                            }
                        }
                        for (j=0; j<GET_AMSPR_SIZE(actor); ++j) {
                            set_sprite_tile(actor->slot+j, GET_AMSPR_SPR(actor,j));
                            set_sprite_prop(actor->slot+j, GET_AMSPR_ATTR(actor,j));
                        }
                    }
                }
            }
            /* Perform specific logic for the actor. */
            if (actor->tick) {
                actor->tick(actor);
            }
            /* Update the actor's final position. */
            for (j=0; j<GET_AMSPR_SIZE(actor); ++j) {
                move_sprite(actor->slot+j, FTOI(actor->x)+(j<<3), FTOI(actor->y));
            }
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
