/*////////////////////////////////////////////////////////////////////////////*/

typedef struct _RECT_
{
    U8 x;
    U8 y;
    U8 w;
    U8 h;

} RECT;

INTERNAL BOOL check_collision (RECT* a, RECT* b)
{
    if (((a->x+a->w) < b->x) || (a->x > (b->x+b->w))) return FALSE;
    if (((a->y+a->h) < b->y) || (a->y > (b->y+b->h))) return FALSE;

    return TRUE;
}

/*////////////////////////////////////////////////////////////////////////////*/
