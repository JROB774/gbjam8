/*////////////////////////////////////////////////////////////////////////////*/

/* STRUCTURES */

typedef struct _RECTU_ RECTU;
typedef struct _RECTI_ RECTI;
typedef struct _RECTF_ RECTF;
typedef struct _PDATA_ PDATA;
typedef struct _ACTOR_ ACTOR;
typedef struct _ABASE_ ABASE;
typedef struct _MROOM_ MROOM;

/* FUNCTIONS */

INTERNAL VOID   joypad_wait              (U8 buttons                       );
INTERNAL BOOL   joypad_waittimeout       (U8 buttons, U8 timeout           );
INTERNAL VOID   fade_to_white            (U8 wait_period                   );
INTERNAL VOID   fade_from_white          (U8 wait_period                   );
INTERNAL VOID   fade_to_black            (U8 wait_period                   );
INTERNAL VOID   fade_from_black          (U8 wait_period                   );
INTERNAL ACTOR* actor_request_actor      (U8 cat                           );
INTERNAL U8     actor_request_oam        (U8 size                          );
INTERNAL ACTOR* actor_create             (U8 type, U8 x, U8 y              );
INTERNAL VOID   actor_anim_change        (ACTOR* actor, U8 anim, BOOL reset);
INTERNAL BOOL   actor_anim_done          (ACTOR* actor                     );
INTERNAL VOID   actor_invert_palette     (ACTOR* actor, BOOL invert        );
INTERNAL VOID   actor_deactivate         (ACTOR* actor                     );
INTERNAL VOID   actor_update_sprite_pos  (ACTOR* actor                     );
INTERNAL VOID   actor_tick_all           (VOID                             );
INTERNAL VOID   status_init              (VOID                             );
INTERNAL VOID   status_update_hearts     (VOID                             );
INTERNAL VOID   status_update_counters   (VOID                             );
INTERNAL VOID   status_update_item       (VOID                             );
INTERNAL VOID   status_update_score      (VOID                             );
INTERNAL VOID   map_draw                 (VOID                             );
INTERNAL VOID   monster_hit              (ACTOR* actor, U8 damage          );
INTERNAL VOID   player_init              (VOID                             );
INTERNAL VOID   player_damage            (VOID                             );
INTERNAL VOID   player_kill              (VOID                             );
INTERNAL VOID   ptear_kill               (ACTOR* actor                     );
INTERNAL VOID   room_update_doors        (VOID                             );
INTERNAL VOID   room_transition          (U8 dir                           );
INTERNAL VOID   room_tick                (VOID                             );
INTERNAL U8     generate_check_end_rooms (VOID                             );
INTERNAL BOOL   generate_check_diagonals (U8 x, U8 y, U8 dir               );
INTERNAL VOID   generate_check_doors     (U8 x, U8 y                       );
INTERNAL VOID   generate_room_doors      (U8 x, U8 y                       );
INTERNAL BOOL   generate_room_neighbors  (U8 x, U8 y                       );
INTERNAL VOID   generate_room            (U8 x, U8 y                       );
INTERNAL VOID   generate_floor           (VOID                             );

INTERNAL VOID   A_PLAYER                 (ACTOR* actor                     );
INTERNAL VOID   A_GAPER                  (ACTOR* actor                     );
INTERNAL VOID   A_PTEAR                  (ACTOR* actor                     );

/*////////////////////////////////////////////////////////////////////////////*/
