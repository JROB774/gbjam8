/*////////////////////////////////////////////////////////////////////////////*/

#define SPLASH_WAIT_PERIOD 120
#define SPLASH_DARK_PERIOD  60
#define SPLASH_FADE_SPEED    3

#define END_SPLASH_EARLY_WAIT fade_to_black(1); return;
#define END_SPLASH_EARLY_DARK                   return;

#define DO_SPLASH(num)                                                     \
SET_BKG_DATA(TILESET_SPLASH##num);                                         \
SET_MAP_DATA(TILEMAP_SPLASH##num);                                         \
fade_from_black(SPLASH_FADE_SPEED);                                        \
if (JOYPAD_WAITTIMEOUT_ANY(SPLASH_WAIT_PERIOD)) { END_SPLASH_EARLY_WAIT; } \
fade_to_black(SPLASH_FADE_SPEED);                                          \
if (JOYPAD_WAITTIMEOUT_ANY(SPLASH_DARK_PERIOD)) { END_SPLASH_EARLY_DARK; }

INTERNAL void SPLASH ()
{
    HIDE_SPRITES;
    HIDE_WIN;
    SHOW_BKG;

    #if !DEBUG_MODE
    DO_SPLASH(1);
    DO_SPLASH(2);
    #endif
}

/*////////////////////////////////////////////////////////////////////////////*/
