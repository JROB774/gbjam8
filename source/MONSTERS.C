/*////////////////////////////////////////////////////////////////////////////*/

INTERNAL VOID A_GAPER (ACTOR* actor)
{
    FIXED theta = ATAN2(actor_list[0].y - actor->y, actor_list[0].x - actor->x);
    FIXED vx,vy;

    vx = COS(FTOI(theta));
    vy = SIN(FTOI(theta));

    actor->x += FDIV(vx,ITOF(25));
    actor->y += FDIV(vy,ITOF(25));
}

/*////////////////////////////////////////////////////////////////////////////*/
