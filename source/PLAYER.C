/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_SPEED 1

typedef struct _PLAYER_
{
    U8 dir;

} PLAYER;

GLOBAL PLAYER player;

INTERNAL void player_update (ACTOR* actor)
{
    U8 old_dir = player.dir;

    /* Move the player around the screen and update the current direction. */
    if (JOYPAD_DOWN_PAD_U) { actor->y -= PLAYER_SPEED; SET_FLAGS(player.dir, DIR_U); } else { UNSET_FLAGS(player.dir, DIR_U); }
    if (JOYPAD_DOWN_PAD_R) { actor->x += PLAYER_SPEED; SET_FLAGS(player.dir, DIR_R); } else { UNSET_FLAGS(player.dir, DIR_R); }
    if (JOYPAD_DOWN_PAD_D) { actor->y += PLAYER_SPEED; SET_FLAGS(player.dir, DIR_D); } else { UNSET_FLAGS(player.dir, DIR_D); }
    if (JOYPAD_DOWN_PAD_L) { actor->x -= PLAYER_SPEED; SET_FLAGS(player.dir, DIR_L); } else { UNSET_FLAGS(player.dir, DIR_L); }

    /* If the player's direction has changed update the state. */
    if (old_dir != player.dir) {
             if (player.dir & DIR_U) { actor_set_state(actor, ASTATE_PLAYER_MOVE_U_0); }
        else if (player.dir & DIR_D) { actor_set_state(actor, ASTATE_PLAYER_MOVE_D_0); }
        else if (player.dir & DIR_L) { actor_set_state(actor, ASTATE_PLAYER_MOVE_L_0); }
        else if (player.dir & DIR_R) { actor_set_state(actor, ASTATE_PLAYER_MOVE_R_0); }
        else                         { actor_set_state(actor, ASTATE_PLAYER_IDLE    ); }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
