/*////////////////////////////////////////////////////////////////////////////*/

/* STRUCTURES */

typedef const struct _ABASE_  ABASE;
typedef const struct _ASTATE_ ASTATE;
typedef       struct _ACTOR_  ACTOR;
typedef       struct _PLAYER_ PLAYER;

/* FUNCTIONS */

INTERNAL VOID joypad_wait            (U8 buttons                   );
INTERNAL BOOL joypad_waittimeout     (U8 buttons, U8 timeout       );
INTERNAL VOID fade_to_white          (U8 wait_period               );
INTERNAL VOID fade_from_white        (U8 wait_period               );
INTERNAL VOID fade_to_black          (U8 wait_period               );
INTERNAL VOID fade_from_black        (U8 wait_period               );
INTERNAL VOID actor_create           (U8 type, U8 state, U8 x, U8 y);
INTERNAL VOID actor_set_state        (ACTOR* actor, U8 state       );
INTERNAL VOID actor_update_all       (VOID                         );
INTERNAL VOID mon_gaper_update       (ACTOR* actor                 );
INTERNAL VOID player_update          (ACTOR* actor                 );
INTERNAL VOID status_init            (VOID                         );
INTERNAL VOID status_update_hearts   (VOID                         );
INTERNAL VOID status_update_counters (VOID                         );
INTERNAL VOID status_update_item     (VOID                         );
INTERNAL VOID status_update_score    (VOID                         );
INTERNAL VOID map_draw               (VOID                         );

/*////////////////////////////////////////////////////////////////////////////*/
