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
    U8  max_hearts; /* Maximum number of hearts the player can have right now.*/
    U8  hearts;     /* Current number of hearts the player has right now.     */
    U8  iframes;    /* Number of frames of invincibility that tick down.      */
    U8  dir_locked; /* Player's direction is locked whilst shooting.          */
    U8  cooldown;   /* Timer that dictates when the player can shoot.         */
    S32 score;      /* Score obtained for the current play session.           */
    U8  xroom;      /* Current horizontal room coordinate on the floor.       */
    U8  yroom;      /* Current vertical room coordinate on the floor.         */

} PDATA;

GLOBAL PDATA pdata;

INTERNAL VOID player_init (VOID)
{
    pdata.max_hearts = PLAYER_START_HEARTS;
    pdata.hearts     = PLAYER_START_HEARTS;
    pdata.iframes    = 0;
    pdata.dir_locked = FALSE;
    pdata.cooldown   = 0;
    pdata.score      = 0;
    pdata.xroom      = 0;
    pdata.yroom      = 0;
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
    UNSET_FLAGS(a_player->flags, AFLAG_HIDDEN);
    actor_update_sprite_pos(a_player);

    /* Remove all other actors when the player dies. */
    actor = a_actors;
    while (actor != (a_actors+TOTAL_NUMBER_OF_ACTORS)) {
        if (actor->cat != ACATE_PLAYER) {
            actor_deactivate(actor);
        }
        actor++;
    }

    fade_to_black(PLAYER_DEAD_FADE_SPEED);

    WAIT(20);

    /* Fade the player to black. */
    for (fade_timer=0; fade_timer<FADE_STEP_AMOUNT; ++fade_timer) {
        switch (fade_timer) {
            case (0): SPR_PAL0 = 0xE4; break;
            case (1): SPR_PAL0 = 0xE5; break;
            case (2): SPR_PAL0 = 0xE9; break;
            case (3): SPR_PAL0 = 0xF9; break;
            case (4): SPR_PAL0 = 0xFE; break;
            case (5): SPR_PAL0 = 0xFF; break;
        }
        WAIT(PLAYER_DEAD_FADE_SPEED);
    }

    actor_deactivate(a_player);

    WAIT(20);

    /* Reset the sprite data. */
    SPR_PAL0 = 0xE4;
    HIDE_SPRITES;

    reset_flag = TRUE;
}

#define CHECK_DOOR_COLLISION_VERT(a,b)                                                \
((((a->x+a->bounds.x+a->bounds.w)>=(b.x)) && ((b.x+b.w)>=(a->x+a->bounds.x))) &&      \
 (((a->y+ITOF(16))>=(b.y)) && ((b.y+b.h)>=(a->y))))

#define CHECK_DOOR_COLLISION_HORZ(a,b)                                                \
((((a->x+ITOF(16))>=(b.x)) && ((b.x+b.w)>=(a->x))) &&                                 \
 (((a->y+a->bounds.y+a->bounds.h)>=(b.y)) && ((b.y+b.h)>=(a->y+a->bounds.y))))

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

        /* Player performs the room bounds collision check themselves before firing tears so the tears don't spawn in walls. */
        /* And also so that we can if the player collides with a door in a cleared room then they will transition to the next. */
        /* @NOTE: Hardcoded width and height! */
        RECTF door;
        if (actor->x < ITOF(24)) {
            door.x = ITOF(  8);
            door.y = ITOF( 72);
            door.w = ITOF( 16);
            door.h = ITOF( 16);
            if (room_current_clear() && room_has_door_l() && CHECK_DOOR_COLLISION_HORZ(actor, door)) {
                room_transition(DIR_L);
            } else {
                actor->x = ITOF(24);
            }
        }
        if ((actor->x + ITOF(16)) > ITOF(136)) {
            door.x = ITOF(136);
            door.y = ITOF( 72);
            door.w = ITOF( 16);
            door.h = ITOF( 16);
            if (room_current_clear() && room_has_door_r() && CHECK_DOOR_COLLISION_HORZ(actor, door)) {
                room_transition(DIR_R);
            } else {
                actor->x = ITOF(136-16);
            }
        }
        if (actor->y < ITOF(32)) {
            door.x = ITOF( 72);
            door.y = ITOF( 16);
            door.w = ITOF( 16);
            door.h = ITOF( 16);
            if (room_current_clear() && room_has_door_u() && CHECK_DOOR_COLLISION_VERT(actor, door)) {
                room_transition(DIR_U);
            } else {
                actor->y = ITOF(32);
            }
        }
        if ((actor->y + ITOF(16)) > ITOF(128)) {
            door.x = ITOF( 72);
            door.y = ITOF(128);
            door.w = ITOF( 16);
            door.h = ITOF( 16);
            if (room_current_clear() && room_has_door_d() && CHECK_DOOR_COLLISION_VERT(actor, door)) {
                room_transition(DIR_D);
            } else {
                actor->y = ITOF(128-16);
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
