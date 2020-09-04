/*////////////////////////////////////////////////////////////////////////////*/

#define GAPER_UPDATE 0x0A    /* ( 10) How often to re-target the player. */
#define GAPER_SPEED  FP_HALF /* (0.5) The movement speed of the monster. */

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    if ((actor->animt % GAPER_UPDATE) == 0) {
        FIXED theta = ATAN2(actor_list[0].y - actor->y, actor_list[0].x - actor->x);
        actor->vx = FMUL(COS(FTOI(theta)),GAPER_SPEED);
        actor->vy = FMUL(SIN(FTOI(theta)),GAPER_SPEED);
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
