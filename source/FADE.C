/*////////////////////////////////////////////////////////////////////////////*/

#define FADE_STEP_AMOUNT 0x04 /* How many unique steps in the fade process. */

INTERNAL void fade_to_white (U8 wait_period)
{
    HIDE_SPRITES; /* We hide sprites as they do not seem to fade. */
    for (i=0; i<FADE_STEP_AMOUNT; ++i) {
        switch (i) {
            case (0): BGP_REG = 0xE4; break;
            case (1): BGP_REG = 0x90; break;
            case (2): BGP_REG = 0x40; break;
            case (3): BGP_REG = 0x00; break;
        }
        for (j=0; j<wait_period; ++j) {
            wait_vbl_done();
        }
    }
}

INTERNAL void fade_from_white (U8 wait_period)
{
    HIDE_SPRITES; /* We hide sprites as they do not seem to fade. */
    for (i=0; i<FADE_STEP_AMOUNT; ++i) {
        switch (i) {
            case (0): BGP_REG = 0x00; break;
            case (1): BGP_REG = 0x40; break;
            case (2): BGP_REG = 0x90; break;
            case (3): BGP_REG = 0xE4; break;
        }
        for (j=0; j<wait_period; ++j) {
            wait_vbl_done();
        }
    }
}

INTERNAL void fade_to_black (U8 wait_period)
{
    HIDE_SPRITES; /* We hide sprites as they do not seem to fade. */
    for (i=0; i<FADE_STEP_AMOUNT; ++i) {
        switch (i) {
            case (0): BGP_REG = 0xE4; break;
            case (1): BGP_REG = 0xF9; break;
            case (2): BGP_REG = 0xFE; break;
            case (3): BGP_REG = 0xFF; break;
        }
        for (j=0; j<wait_period; ++j) {
            wait_vbl_done();
        }
    }
}

INTERNAL void fade_from_black (U8 wait_period)
{
    HIDE_SPRITES; /* We hide sprites as they do not seem to fade. */
    for (i=0; i<FADE_STEP_AMOUNT; ++i) {
        switch (i) {
            case (0): BGP_REG = 0xFF; break;
            case (1): BGP_REG = 0xFE; break;
            case (2): BGP_REG = 0xF9; break;
            case (3): BGP_REG = 0xE4; break;
        }
        for (j=0; j<wait_period; ++j) {
            wait_vbl_done();
        }
    }
}

/*////////////////////////////////////////////////////////////////////////////*/
