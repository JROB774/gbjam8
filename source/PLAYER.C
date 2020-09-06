/*////////////////////////////////////////////////////////////////////////////*/

#define PLAYER_MAX_SCORE       999999
#define PLAYER_HIT_SCORE           50
#define PLAYER_DEAD_FADE_SPEED     10
#define PLAYER_START_HEARTS         3
#define PLAYER_IFRAMES             50
#define PLAYER_FIRE_RATE_COOLDOWN  15
#define PLAYER_TEAR_SPEED     ITOF( 2)
#define PLAYER_SPEED          ITOF( 1)
#define PLAYER_KNOCKBACK      ITOF(10)
#define PLAYER_TEAR_KNOCKBACK ITOF( 2)
#define PLAYER_TEAR_DAMAGE    ITOF( 3)+FP_HALF

typedef struct _PDATA_
{
    U8  max_hearts; /* Maximum number of hearts the player can have right now. */
    U8  hearts;     /* Current number of hearts the player has right now.      */
    U8  iframes;    /* Number of frames of invincibility that tick down.       */
    U8  dir_locked; /* Player's direction is locked whilst shooting.           */
    U8  cooldown;   /* Timer that dictates when the player can shoot.          */
    S32 score;      /* Score obtained for the current play session.            */

} PDATA;

GLOBAL PDATA pdata;

INTERNAL VOID player_init (VOID)
{
    pdata.max_hearts = PLAYER_START_HEARTS;
    pdata.hearts     = PLAYER_START_HEARTS;
    pdata.iframes    = 0;
    pdata.dir_locked = FALSE;
    pdata.cooldown   = 0;
}

INTERNAL VOID player_damage (VOID)
{
    pdata.iframes = PLAYER_IFRAMES;
    pdata.hearts--;

    pdata.score -= PLAYER_HIT_SCORE;
    if (pdata.score < 0) {
        pdata.score = 0;
    }

    status_update_hearts();
    status_update_score();

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
    actor = a_actors;
    while (actor != (a_actors+TOTAL_NUMBER_OF_ACTORS)) {
        if (actor->cat != ACATE_PLAYER) {
            actor_deactivate(actor);
        }
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

        if (!pdata.dir_locked) {
            actor_anim_change(actor, anim, FALSE);
        }

        /* Check collision with hostile enemies. */
        if ((actor->ticks % 2) == 0) {
            if (!pdata.iframes) { /* No need to check if we have iframes. */
                ACTOR* enemy = a_monsters;
                while (enemy != (a_monsters+TOTAL_NUMBER_OF_MONSTERS)) {
                    if (enemy->active && enemy->state != ASTAT_DEAD) {
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

        /* Handle firing tears. */
        if (pdata.cooldown) { pdata.cooldown--; }
        if (JOYPAD_DOWN_A) {
            /* If the player is idle change to the down animation as it just looks better. */
            if (actor->animi == AANIM_PLAYER_I) {
                actor_anim_change(actor, AANIM_PLAYER_MD, FALSE);
            }
            pdata.dir_locked = TRUE;
            if (!pdata.cooldown) { /* If we've cooled down from the last shot. */
                ACTOR* tear = actor_create(ATYPE_PTEAR, FTOI(actor->x) + 4, FTOI(actor->y)); /* @NOTE: Hardcoded values! */
                pdata.cooldown = PLAYER_FIRE_RATE_COOLDOWN;
                if (tear) { /* Could be NULL! */
                    tear->ext0 = actor->animi; /* Store direction in ext0. */
                }
            }
        } else {
            pdata.dir_locked = FALSE;
        }
    }
}

INTERNAL VOID ptear_kill (ACTOR* actor)
{
    UNSET_FLAGS(actor->flags, AFLAG_HIDDEN); /* Make sure the tear is visible as we flicker them. */
    actor_anim_change(actor, AANIM_PTEAR_D, TRUE);
    actor->state = ASTAT_DEAD;
}

INTERNAL VOID A_PTEAR (ACTOR* actor)
{
    switch (actor->state) {
        case (ASTAT_IDLE): {
            /* We flicker tears as there will be a lot of them on screen. */
            /*if ((actor->ticks % 2) == 0) {
                TOGGLE_FLAGS(actor->flags, AFLAG_HIDDEN);
            }*/

            /* If the tear hits the edge of the wall then kill it. */
            /* @NOTE: Hardcoded width and height! */
            if ((actor->x < ITOF(24) || (actor->x + ITOF(8)) > ITOF(136)) ||
                (actor->y < ITOF(32) || (actor->y + ITOF(8)) > ITOF(128))) {
                ptear_kill(actor);
            }

            /* Move the tear based on its direction which is stored in ext0. */
            switch (actor->ext0) {
                case (AANIM_PLAYER_I ):
                case (AANIM_PLAYER_MD): { actor->y += PLAYER_TEAR_SPEED; } break;
                case (AANIM_PLAYER_MU): { actor->y -= PLAYER_TEAR_SPEED; } break;
                case (AANIM_PLAYER_ML): { actor->x -= PLAYER_TEAR_SPEED; } break;
                case (AANIM_PLAYER_MR): { actor->x += PLAYER_TEAR_SPEED; } break;
            }

            /* Check collision with hostile enemies. */
            if ((actor->ticks % 2) == 0) {
                ACTOR* enemy = a_monsters;
                while (enemy != (a_monsters+TOTAL_NUMBER_OF_MONSTERS)) {
                    if (enemy->active && enemy->state != ASTAT_DEAD) {
                        if (CHECK_COLLISION(actor, enemy)) {
                            monster_hit(enemy, PLAYER_TEAR_DAMAGE);
                            ptear_kill(actor);
                            break; /* There's no need to continue looping. */
                        }
                    }
                    enemy++;
                }
            }
        } break;
        case (ASTAT_DEAD): {
            if (actor_anim_done(actor)) {
                actor_deactivate(actor);
            }
        } break;
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
