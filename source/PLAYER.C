/*////////////////////////////////////////////////////////////////////////////*/

INTERNAL void player_update (ACTOR* actor)
{
    if (JOYPAD_DOWN_PAD_U) { actor->y -= 1; }
    if (JOYPAD_DOWN_PAD_R) { actor->x += 1; }
    if (JOYPAD_DOWN_PAD_D) { actor->y += 1; }
    if (JOYPAD_DOWN_PAD_L) { actor->x -= 1; }
}

/*////////////////////////////////////////////////////////////////////////////*/
