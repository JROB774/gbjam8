/*////////////////////////////////////////////////////////////////////////////*/

#define GAPER_UPDATE_TARGET_RATE 0x0A /* (10) How often to re-target the player. */

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    if ((actor->animt % GAPER_UPDATE_TARGET_RATE) == 0) {
        FIXED theta = ATAN2(actor_list[0].y - actor->y, actor_list[0].x - actor->x);
        actor->ext0 = FDIV((FIXED)COS(FTOI(theta)),ITOF(25));
        actor->ext1 = FDIV((FIXED)SIN(FTOI(theta)),ITOF(25));
    }

    actor->x += actor->ext0;
    actor->y += actor->ext1;
}

/*////////////////////////////////////////////////////////////////////////////*/
