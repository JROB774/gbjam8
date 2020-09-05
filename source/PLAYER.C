/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_DEAD_FADE_SPEED   10
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

    status_update_hearts();

    if (pdata.hearts == 0) {
        player_kill();
    }
}

INTERNAL VOID player_kill (VOID)
{
    ACTOR* actor;

    actor_anim_change(a_player, AANIM_PLAYER_D, TRUE);
    a_player->state = ASTAT_DEAD;

    /* Kill all other actors when the player dies. */
    actor = a_monsters;
    while (actor != (a_monsters+a_monster_count)) {
        actor_deactivate(actor);
        actor++;
    }
    actor = a_tears;
    while (actor != (a_tears+a_tear_count)) {
        actor_deactivate(actor);
        actor++;
    }

    fade_to_black(PLAYER_DEAD_FADE_SPEED);

    while (TRUE) {}
}

INTERNAL VOID A_PLAYER (ACTOR* actor)
{
    /* Decrease velocity over time as the force diminishes. */
    if (actor->vx != 0) { actor->vx = FDIV(actor->vx,ITOF(2)); }
    if (actor->vy != 0) { actor->vy = FDIV(actor->vy,ITOF(2)); }

    /* Player logic depends on if the actor is dead or alive. */
    if (actor->state != ASTAT_DEAD) {
        U8 anim = AANIM_PLAYER_I;

        /* Flash the chracter whilst they are invincible. */
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
        if ((actor->ticks % 2) == 0) {
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
