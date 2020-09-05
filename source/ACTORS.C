/*////////////////////////////////////////////////////////////////////////////*/

/* An actor is any entity within the world (player, monster, item, etc.). *****/

typedef VOID(*ATICK)(ACTOR* actor);

typedef struct _ACTOR_
{
    ATICK tick;   /* Custom behaviour for an actor that runs every tick.      */
    FIXED x,y;    /* Current (X,Y) position as fixed-point values.            */
    FIXED vx,vy;  /* Current (X,Y) velocity as fixed-point values.            */
    RECTF bounds; /* Bounding/collision box for the actor.                    */
    U16   hp;     /* Health points for the actor (not used by all actors).    */
    U8    cat;    /* Category of the actor type.                              */
    U8    flags;  /* Flags that define aspects of an entity.          (AFLAG) */
    U8    type;   /* Identifier for the type of actor.                (ATYPE) */
    U8    state;  /* Identifier for the current actor state.          (ASTAT) */
    U8    animi;  /* Identifier for the current actor animation.      (AANIM) */
    U8    animf;  /* The current frame of the animation being player.         */
    U8    animt;  /* Timer for the current animation frame.                   */
    U8    slot;   /* Starting slot in OAM for the actor's sprite data.        */
    U8    ext0;   /* Can be used to represent extra/custom data.              */
    U8    ext1;   /* Can be used to represent extra/custom data.              */
    U8    ext2;   /* Can be used to represent extra/custom data.              */
    U8    ext3;   /* Can be used to represent extra/custom data.              */
    BOOL  active; /* Whether the actor is currently active or not. An actor   */
                  /* that is not active can be replaced with a new actor.     */
} ACTOR;

/* Different categories of actors that control how they are sorted. ***********/

#define ACATE_PLAYER      0x01
#define ACATE_MONSTER     0x02
#define ACATE_TEAR        0x03

/* Flags that control generic aspects of an entity type or instance. **********/

#define AFLAG_NONE        0x00 /* No flags set.                               */
#define AFLAG_NOANIM      0x01 /* The actor is not animated.                  */
#define AFLAG_UNBOUND     0x02 /* The actor is not bound to the room.         */
#define AFLAG_HIDDEN      0x04 /* The actor will not be drawn.                */

// #define AFLAG_SOLID       0x04 /* The actor collides with tiles.              */
// #define AFLAG_HOSTILE     0x08 /* The actor can be hurt by the player.        */
// #define AFLAG_FLYING      0x10 /* The actor is flying.                        */
// #define AFLAG_NODAMAGE    0x20 /* The actor cannot take any damage.           */
// #define AFLAG_BOSS        0x40 /* The actor is a boss (show health bar).      */

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
    ATICK tick;   /* The tick function for the particular actor type.         */
    RECTF bounds; /* The bounding box for the particular actor type.          */
    U8    cat;    /* The category for the particular actor type.              */
    U16   hp;     /* The starting health points for the actor type.           */
    U8    state;  /* The starting state for the actor type.                   */
    U8    anim;   /* The starting animation for the actor type.               */
    U8    flags;  /* The general flags for the actor type.                    */

} ABASE;

GLOBAL const ABASE ABASE_TABLE[/*(ATYPE)*/] =
{
/* tick_function, bounds, category, start_hp, start_state, start_anim, flags                                                        */
{ A_PLAYER, { ITOF( 5),ITOF( 9),ITOF( 6),ITOF( 6) }, ACATE_PLAYER ,    0, ASTAT_IDLE, AANIM_PLAYER_I, AFLAG_NONE }, /* ATYPE_PLAYER */
{ A_GAPER , { ITOF( 5),ITOF( 9),ITOF( 6),ITOF( 6) }, ACATE_MONSTER,  100, ASTAT_MOVE, AANIM_GAPER_M , AFLAG_NONE }, /* ATYPE_GAPER  */
};

/* Macro utilities for accessing meta-sprite and animation actor table data. **/

#define GET_AMSPR_PTR(       actor  ) (AMSPR_TABLE+GET_AANIM_CURR_AMSPR(actor))
#define GET_AMSPR(           actor  ) (*(GET_AMSPR_PTR(actor)                ))
#define GET_AMSPR_SIZE(      actor  ) (*(GET_AMSPR_PTR(actor)                ))
#define GET_AMSPR_SPR(       actor,s) (*(GET_AMSPR_PTR(actor)+0x01+((s)<<1)  ))
#define GET_AMSPR_ATTR(      actor,s) (*(GET_AMSPR_PTR(actor)+0x02+((s)<<1)  ))

#define GET_AANIM_PTR(       actor  ) (AANIM_TABLE+actor->animi               )
#define GET_AANIM(           actor  ) (*(GET_AANIM_PTR(actor)                ))
#define GET_AANIM_FRAMES(    actor  ) (*(GET_AANIM_PTR(actor)                ))
#define GET_AANIM_LOOP(      actor  ) (*(GET_AANIM_PTR(actor)+0x01           ))
#define GET_AANIM_AMSPR(     actor,f) (*(GET_AANIM_PTR(actor)+0x02+((f)<<1)  ))
#define GET_AANIM_TICKS(     actor,f) (*(GET_AANIM_PTR(actor)+0x03+((f)<<1)  ))
#define GET_AANIM_CURR_AMSPR(actor  ) (GET_AANIM_AMSPR(actor,actor->animf    ))
#define GET_AANIM_CURR_TICKS(actor  ) (GET_AANIM_TICKS(actor,actor->animf    ))

/* The actor manager system that handles creating, destroying, and managing. **/

#define TOTAL_NUMBER_OF_ACTORS 25

GLOBAL ACTOR a_actors[TOTAL_NUMBER_OF_ACTORS];

GLOBAL U8 oam_slot_ptr = 0;

GLOBAL ACTOR* a_player   = a_actors+ 0; // Length =  1
GLOBAL ACTOR* a_monsters = a_actors+ 1; // Length = 10
GLOBAL ACTOR* a_tears    = a_actors+11; // Length = 10

GLOBAL U8 a_monster_count = 0;
GLOBAL U8 a_tear_count    = 0;

INTERNAL VOID actor_create (U8 type, U8 x, U8 y)
{
    U8 i;

    ACTOR* actor = NULL;
    switch (ABASE_TABLE[type].cat) {
        case (ACATE_PLAYER ): actor = a_player;                       break;
        case (ACATE_MONSTER): actor = a_monsters+(a_monster_count++); break;
        case (ACATE_TEAR   ): actor = a_tears   +(a_tear_count++   ); break;
    }

    actor->tick     = ABASE_TABLE[type].tick;
    actor->x        = ITOF(x);
    actor->y        = ITOF(y);
    actor->vx       = 0;
    actor->vy       = 0;
    actor->bounds.x = ABASE_TABLE[type].bounds.x;
    actor->bounds.y = ABASE_TABLE[type].bounds.y;
    actor->bounds.w = ABASE_TABLE[type].bounds.w;
    actor->bounds.h = ABASE_TABLE[type].bounds.h;
    actor->hp       = ABASE_TABLE[type].hp;
    actor->cat      = ABASE_TABLE[type].cat;
    actor->flags    = ABASE_TABLE[type].flags;
    actor->type     = type;
    actor->state    = ABASE_TABLE[type].state;
    actor->animi    = ABASE_TABLE[type].anim;
    actor->animf    = 0;
    actor->animt    = 0;
    actor->slot     = oam_slot_ptr;
    actor->ext0     = 0;
    actor->ext1     = 0;
    actor->ext2     = 0;
    actor->ext3     = 0;
    actor->active   = TRUE;

    for (i=0; i<GET_AMSPR_SIZE(actor); ++i) {
        set_sprite_tile(actor->slot+i, GET_AMSPR_SPR(actor,i));
        set_sprite_prop(actor->slot+i, GET_AMSPR_ATTR(actor,i));
    }

    oam_slot_ptr += 2; /* @Temporary!!! */
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

INTERNAL BOOL actor_anim_done (ACTOR* actor)
{
    return ((               !GET_AANIM_LOOP      (actor)  ) && /* Not Looping  */
            (actor->animf == GET_AANIM_FRAMES    (actor)-1) && /* Last Frame   */
            (actor->animt >= GET_AANIM_CURR_TICKS(actor)  ));  /* End of Frame */
}

INTERNAL VOID actor_tick_all (VOID)
{
    U8 j, sx,sy;
    ACTOR* a;

    /* Go through the list and update all of the active actors. */
    a = a_actors;
    while (a != a_actors+TOTAL_NUMBER_OF_ACTORS) {
        if (a->active) {
            /* Update the actor's current animation, if they are animated. */
            if (!(a->flags & AFLAG_NOANIM)) {
                if (!actor_anim_done(a)) {
                    a->animt++;
                    if (a->animt >= GET_AANIM_CURR_TICKS(a)) {
                        a->animt = 0;
                        a->animf++;
                        if (a->animf >= GET_AANIM_FRAMES(a)) {
                            if (GET_AANIM_LOOP(a)) {
                                a->animf = 0;
                            } else {
                                a->animt = 0xFF;
                                a->animf--;
                            }
                        }
                        for (j=0; j<GET_AMSPR_SIZE(a); ++j) {
                            set_sprite_tile(a->slot+j, GET_AMSPR_SPR(a,j));
                            set_sprite_prop(a->slot+j, GET_AMSPR_ATTR(a,j));
                        }
                    }
                }
            }

            /* Perform type-specific logic for the actor. */
            a->tick(a);

            /* Apply velocity. */
            a->x += a->vx;
            a->y += a->vy;

            /* Clamp bound actors within the room. */
            if (!(a->flags & AFLAG_UNBOUND)) {
                if (a->x < ITOF(24)) { a->x = ITOF(24); } else if ((a->x + ITOF(16)) > ITOF(136)) { a->x = ITOF(136-16); }
                if (a->y < ITOF(32)) { a->y = ITOF(32); } else if ((a->y + ITOF(16)) > ITOF(128)) { a->y = ITOF(128-16); }
            }

            /* Move the actor's meta-sprite. */
            if (!(a->flags & AFLAG_HIDDEN)) {
                sx = FTOI(a->x)+SPRITE_X_OFFSET;
                sy = FTOI(a->y)+SPRITE_Y_OFFSET;
            } else {
                sx = 0;
                sy = 0;
            }
            for (j=0; j<GET_AMSPR_SIZE(a); ++j) {
                move_sprite(a->slot+j, sx+(j<<3), sy);
            }
        }
        a++;
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
