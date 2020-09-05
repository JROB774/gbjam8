/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_START_HEARTS       3
#define PLAYER_IFRAMES           40
#define PLAYER_SPEED       ITOF(  1)
#define PLAYER_KNOCKBACK   ITOF( 10)

typedef struct _PDATA_
{
    U8 max_hearts; /* Maximum number of hearts the player can have right now. */
    U8 hearts;     /* Current number of hearts the player has right now.      */
    U8 iframes;    /* Number of frames of invincibility that tick down.       */

} PDATA;

GLOBAL PDATA pdata;

INTERNAL VOID player_init (VOID)
{
    pdata.max_hearts = PLAYER_START_HEARTS;
    pdata.hearts     = PLAYER_START_HEARTS;
    pdata.iframes    = 0;
}

INTERNAL VOID player_damage (VOID)
{
    pdata.iframes = PLAYER_IFRAMES;
    pdata.hearts--;

    if (pdata.hearts == 0) {
        player_kill();
    }

    status_update_hearts();
}

INTERNAL VOID player_kill (VOID)
{
    actor_anim_change(a_player, AANIM_PLAYER_D, TRUE);
    a_player->state = ASTAT_DEAD;
}

INTERNAL VOID A_PLAYER (ACTOR* actor)
{
    if (actor->vx != 0) { actor->vx = FDIV(actor->vx,ITOF(2)); }
    if (actor->vy != 0) { actor->vy = FDIV(actor->vy,ITOF(2)); }

    if (actor->state == ASTAT_DEAD) {
        // @Incomplete: ...
    } else {
        U8 anim = AANIM_PLAYER_I;

        if (pdata.iframes) {
            TOGGLE_FLAGS(actor->flags, AFLAG_HIDDEN);
            pdata.iframes--;
        }

        /* Display the map screen and pause the game until SELECT is pressed. */
        if (JOYPAD_PRESSED_SELECT) { map_draw(); }

        /* Move the player around the screen and update the current direction. */
        if (JOYPAD_DOWN_PAD_R) { actor->x += PLAYER_SPEED; anim = AANIM_PLAYER_MR; }
        if (JOYPAD_DOWN_PAD_L) { actor->x -= PLAYER_SPEED; anim = AANIM_PLAYER_ML; }
        if (JOYPAD_DOWN_PAD_U) { actor->y -= PLAYER_SPEED; anim = AANIM_PLAYER_MU; }
        if (JOYPAD_DOWN_PAD_D) { actor->y += PLAYER_SPEED; anim = AANIM_PLAYER_MD; }

        actor_anim_change(actor, anim, FALSE);

        /* Check collision with hostile enemies. */
        if ((actor->animt % 2) == 0) {
            if (!pdata.iframes) { /* No need to check if we have iframes. */
                ACTOR* enemy = a_monsters;
                while (enemy != (a_monsters+a_monster_count)) {
                    if (enemy->active) {
                        if (CHECK_COLLISION(actor, enemy)) {
                            /* Perform knockback on the player relative to the damaging enemy. */
                            FIXED theta = ATAN2(actor->y - enemy->y, actor->x - enemy->x);
                            actor->vx += FMUL(COS(FTOI(theta)),PLAYER_KNOCKBACK);
                            actor->vy += FMUL(SIN(FTOI(theta)),PLAYER_KNOCKBACK);
                            player_damage();
                            break; /* There's no need to continue looping. */
                        }
                    }
                    enemy++;
                }
            }
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
