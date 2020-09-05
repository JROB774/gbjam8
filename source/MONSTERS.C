/*////////////////////////////////////////////////////////////////////////////*/

#define GAPER_UPDATE 0x0A    /* ( 10) How often to re-target the player. */
#define GAPER_SPEED  FP_HALF /* (0.5) The movement speed of the monster. */

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    if (actor->hp <= 0) { actor_deactivate(actor); }

    if ((actor->ticks % GAPER_UPDATE) == 0) {
        FIXED theta = ATAN2(a_player->y - actor->y, a_player->x - actor->x);
        actor->vx = FMUL(COS(FTOI(theta)),GAPER_SPEED);
        actor->vy = FMUL(SIN(FTOI(theta)),GAPER_SPEED);
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
