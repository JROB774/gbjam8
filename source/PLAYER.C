/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_DIR_U 0x01
#define PLAYER_DIR_R 0x02
#define PLAYER_DIR_D 0x04
#define PLAYER_DIR_L 0x08

typedef struct _PLAYER_
{
    U8 dir;

} PLAYER;

GLOBAL PLAYER player;

INTERNAL void player_update (ACTOR* actor)
{
    U8 old_dir = player.dir;

    if (JOYPAD_DOWN_PAD_U) { actor->y -= 1; player.dir |= PLAYER_DIR_U; } else { player.dir &= (~PLAYER_DIR_U); }
    if (JOYPAD_DOWN_PAD_R) { actor->x += 1; player.dir |= PLAYER_DIR_R; } else { player.dir &= (~PLAYER_DIR_R); }
    if (JOYPAD_DOWN_PAD_D) { actor->y += 1; player.dir |= PLAYER_DIR_D; } else { player.dir &= (~PLAYER_DIR_D); }
    if (JOYPAD_DOWN_PAD_L) { actor->x -= 1; player.dir |= PLAYER_DIR_L; } else { player.dir &= (~PLAYER_DIR_L); }

    /* If the player's direction has changed update the state. */
    if (old_dir != player.dir) {
             if (player.dir & PLAYER_DIR_U) { actor_set_state(actor, ASTATE_PLAYER_MOVE_U_0); }
        else if (player.dir & PLAYER_DIR_D) { actor_set_state(actor, ASTATE_PLAYER_MOVE_D_0); }
        else if (player.dir & PLAYER_DIR_L) { actor_set_state(actor, ASTATE_PLAYER_MOVE_L_0); }
        else if (player.dir & PLAYER_DIR_R) { actor_set_state(actor, ASTATE_PLAYER_MOVE_R_0); }
        else                                { actor_set_state(actor, ASTATE_PLAYER_IDLE    ); }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
