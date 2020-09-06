/*////////////////////////////////////////////////////////////////////////////*/

#define MONSTER_HIT_FLASH_DURATION 2
#define MONSTER_KILL_SCORE       100

INTERNAL VOID monster_hit (ACTOR* actor, U8 damage)
{
    /* If not dead invert the palette to show the monster was hit. */
    actor->hp -= damage;
    if (actor->hp > 0) {
        actor->ext0 = MONSTER_HIT_FLASH_DURATION; /* Stores how long the hit flash should last. */
        actor_invert_palette(actor, TRUE);
    } else {
        pdata.score += MONSTER_KILL_SCORE;
        if (pdata.score > PLAYER_MAX_SCORE) {
            pdata.score = PLAYER_MAX_SCORE;
        }
        status_update_score();
    }
}

#define GAPER_TARGET_RATE 10
#define GAPER_SPEED       (FP_HALF+FP_QUARTER)
#define GAPER_TARGET_AREA 24

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    switch (actor->state) {
        case (ASTAT_MOVE): {
            /* Make the Gaper target and move towards the player character. */
            /* We don't do this every frame as it's an expensive operation. */
            if ((actor->ticks % GAPER_TARGET_RATE) == 0) {
                FIXED tx = a_player->x + ITOF((rand() % GAPER_TARGET_AREA));
                FIXED ty = a_player->y + ITOF((rand() % GAPER_TARGET_AREA));
                FIXED theta = ATAN2(ty - actor->y, tx - actor->x);
                actor->vx = FMUL(COS(FTOI(theta)),GAPER_SPEED);
                actor->vy = FMUL(SIN(FTOI(theta)),GAPER_SPEED);
            }
            /* Return the palette to normal once the hit duration is up. */
            if (actor->ext0) {
                actor->ext0--;
                if (actor->ext0 == 0) {
                    actor_invert_palette(actor, FALSE);
                }
            }
            /* Kill the gaper. */
            if (actor->hp <= 0) {
                actor_anim_change(actor, AANIM_SPLAT_L, TRUE);
                actor_invert_palette(actor, FALSE);
                actor->state = ASTAT_DEAD;
                actor->vx = 0;
                actor->vy = 0;
            }
        } break;
        case (ASTAT_DEAD): {
            /* Once the death animation is complete remove the actor. */
            if (actor_anim_done(actor)) {
                actor_deactivate(actor);
            }
        } break;
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
