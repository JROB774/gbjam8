/*////////////////////////////////////////////////////////////////////////////*/

#define FADE_STEP_AMOUNT 0x06 /* (6) How many steps in the fade process. */

GLOBAL U8 fade_timer;

INTERNAL VOID fade_to_white (U8 wait_period)
{
    for (fade_timer=0; fade_timer<FADE_STEP_AMOUNT; ++fade_timer) {
        switch (fade_timer) {
            case (0): BKG_PAL0 = 0xE4; break;
            case (1): BKG_PAL0 = 0xA4; break;
            case (2): BKG_PAL0 = 0x94; break;
            case (3): BKG_PAL0 = 0x90; break;
            case (4): BKG_PAL0 = 0x40; break;
            case (5): BKG_PAL0 = 0x00; break;
        }
        WAIT(wait_period);
    }
}

INTERNAL VOID fade_from_white (U8 wait_period)
{
    for (fade_timer=0; fade_timer<FADE_STEP_AMOUNT; ++fade_timer) {
        switch (fade_timer) {
            case (0): BKG_PAL0 = 0x00; break;
            case (1): BKG_PAL0 = 0x40; break;
            case (2): BKG_PAL0 = 0x90; break;
            case (3): BKG_PAL0 = 0x94; break;
            case (4): BKG_PAL0 = 0xA4; break;
            case (5): BKG_PAL0 = 0xE4; break;
        }
        WAIT(wait_period);
    }
}

INTERNAL VOID fade_to_black (U8 wait_period)
{
    for (fade_timer=0; fade_timer<FADE_STEP_AMOUNT; ++fade_timer) {
        switch (fade_timer) {
            case (0): BKG_PAL0 = 0xE4; break;
            case (1): BKG_PAL0 = 0xE5; break;
            case (2): BKG_PAL0 = 0xE9; break;
            case (3): BKG_PAL0 = 0xF9; break;
            case (4): BKG_PAL0 = 0xFE; break;
            case (5): BKG_PAL0 = 0xFF; break;
        }
        WAIT(wait_period);
    }
}

INTERNAL VOID fade_from_black (U8 wait_period)
{
    for (fade_timer=0; fade_timer<FADE_STEP_AMOUNT; ++fade_timer) {
        switch (fade_timer) {
            case (0): BKG_PAL0 = 0xFF; break;
            case (1): BKG_PAL0 = 0xFE; break;
            case (2): BKG_PAL0 = 0xF9; break;
            case (3): BKG_PAL0 = 0xE9; break;
            case (4): BKG_PAL0 = 0xE5; break;
            case (5): BKG_PAL0 = 0xE4; break;
        }
        WAIT(wait_period);
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
