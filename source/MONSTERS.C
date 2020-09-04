/*////////////////////////////////////////////////////////////////////////////*/

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    if ((actor->animt % 5) == 0) {
        FIXED theta = ATAN2(actor_list[0].y - actor->y, actor_list[0].x - actor->x);
        actor->ext0 = FDIV((FIXED)COS(FTOI(theta)),ITOF(25));
        actor->ext1 = FDIV((FIXED)SIN(FTOI(theta)),ITOF(25));
    }

    actor->x += actor->ext0;
    actor->y += actor->ext1;
}

/*////////////////////////////////////////////////////////////////////////////*/
