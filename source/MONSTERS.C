/*////////////////////////////////////////////////////////////////////////////*/

#define MONSTER_HIT_FLASH_DURATION 2

INTERNAL VOID monster_hit (ACTOR* actor, U8 damage)
{
    /* If not dead invert the palette to show the monster was hit. */
    actor->hp -= damage;
    if (actor->hp > 0) {
        actor->ext0 = MONSTER_HIT_FLASH_DURATION; /* Stores how long the hit flash should last. */
        actor_invert_palette(actor, TRUE);
    }
}

#define GAPER_UPDATE 10      /* How often to re-target the player. */
#define GAPER_SPEED  FP_HALF /* The movement speed of the monster. */

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    switch (actor->state) {
        case (ASTAT_MOVE): {
            /* Make the Gaper target and move towards the player character. */
            /* We don't do this every frame as it's an expensive operation. */
            if ((actor->ticks % GAPER_UPDATE) == 0) {
                FIXED theta = ATAN2(a_player->y - actor->y, a_player->x - actor->x);
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
