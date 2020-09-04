/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_SPEED ITOF(1);

GLOBAL U8 player_dir;

INTERNAL VOID A_PLAYER (ACTOR* actor)
{
    U8 old_dir = player_dir;

    /* Move the player around the screen and update the current direction. */
    if (JOYPAD_DOWN_PAD_U) { actor->y -= PLAYER_SPEED; SET_FLAGS(player_dir, DIR_U); } else { UNSET_FLAGS(player_dir, DIR_U); }
    if (JOYPAD_DOWN_PAD_R) { actor->x += PLAYER_SPEED; SET_FLAGS(player_dir, DIR_R); } else { UNSET_FLAGS(player_dir, DIR_R); }
    if (JOYPAD_DOWN_PAD_D) { actor->y += PLAYER_SPEED; SET_FLAGS(player_dir, DIR_D); } else { UNSET_FLAGS(player_dir, DIR_D); }
    if (JOYPAD_DOWN_PAD_L) { actor->x -= PLAYER_SPEED; SET_FLAGS(player_dir, DIR_L); } else { UNSET_FLAGS(player_dir, DIR_L); }

    /* If the player's direction has changed update the state. */
    if (old_dir != player_dir) {
             if (player_dir & DIR_U) { actor_anim_change(actor, AANIM_PLAYER_MU, FALSE); }
        else if (player_dir & DIR_D) { actor_anim_change(actor, AANIM_PLAYER_MD, FALSE); }
        else if (player_dir & DIR_L) { actor_anim_change(actor, AANIM_PLAYER_ML, FALSE); }
        else if (player_dir & DIR_R) { actor_anim_change(actor, AANIM_PLAYER_MR, FALSE); }
        else                         { actor_anim_change(actor, AANIM_PLAYER_I , TRUE ); }
    }

    /* Display the map screen and pause the game until SELECT is pressed. */
    if (JOYPAD_PRESSED_SELECT) {
        map_draw();
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
