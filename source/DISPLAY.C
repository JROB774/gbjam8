/*////////////////////////////////////////////////////////////////////////////*/

#define TILE_EMPTY         0x00 /* ( 0) */
#define TILE_NUM_0         0x01 /* ( 1) */
#define TILE_NUM_1         0x02 /* ( 2) */
#define TILE_NUM_2         0x03 /* ( 3) */
#define TILE_NUM_3         0x04 /* ( 4) */
#define TILE_NUM_4         0x05 /* ( 5) */
#define TILE_NUM_5         0x06 /* ( 6) */
#define TILE_NUM_6         0x07 /* ( 7) */
#define TILE_NUM_7         0x08 /* ( 8) */
#define TILE_NUM_8         0x09 /* ( 9) */
#define TILE_NUM_9         0x10 /* (10) */
#define TILE_HEART_FULL    0x0B /* (11) */
#define TILE_HEART_NONE    0x0C /* (12) */
#define TILE_COUNTER_COIN  0x0D /* (13) */
#define TILE_COUNTER_BOMB  0x0E /* (14) */
#define TILE_COUNTER_KEY   0x0F /* (15) */
#define TILE_ITEM_TL       0x10 /* (16) */
#define TILE_ITEM_TR       0x11 /* (17) */
#define TILE_ITEM_BL       0x12 /* (18) */
#define TILE_ITEM_BR       0x13 /* (19) */
#define TILE_ITEM_BAR_NONE 0x14 /* (20) */
#define TILE_ITEM_BAR_HALF 0x15 /* (21) */
#define TILE_ITEM_BAR_FULL 0x16 /* (22) */

#define DISPLAY_MAP_WIDTH  0x08 /* ( 8) */
#define DISPLAY_MAP_HEIGHT 0x08 /* ( 8) */

GLOBAL U8 status_heart_tiles[]     = { TILE_HEART_FULL,TILE_HEART_FULL,TILE_HEART_FULL,      TILE_EMPTY,TILE_EMPTY,TILE_EMPTY             };
GLOBAL U8 status_counter_tiles[]   = { TILE_COUNTER_COIN,TILE_COUNTER_BOMB,TILE_COUNTER_KEY, TILE_NUM_0,TILE_NUM_0,TILE_NUM_0             };
GLOBAL U8 status_item_tiles[]      = { TILE_ITEM_TL,TILE_ITEM_TR,TILE_ITEM_BAR_NONE,         TILE_ITEM_BL,TILE_ITEM_BR,TILE_ITEM_BAR_NONE };
GLOBAL U8 status_highscore_tiles[] = { TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0                                  };
GLOBAL U8 status_score_tiles[]     = { TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0,TILE_NUM_0                                  };

GLOBAL U8 map_tiles[] =
{
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,
TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY,TILE_EMPTY
};

INTERNAL VOID status_init (VOID)
{
    status_update_hearts();
    status_update_counters();
    status_update_item();
    status_update_score();
}

INTERNAL VOID status_update_hearts (VOID)
{
    set_bkg_tiles(1,0, 3,2, status_heart_tiles);
}

INTERNAL VOID status_update_counters (VOID)
{
    set_bkg_tiles(5,0, 3,2, status_counter_tiles);
}

INTERNAL VOID status_update_item (VOID)
{
    set_bkg_tiles(9,0, 3,2, status_item_tiles);
}

INTERNAL VOID status_update_score (VOID)
{
    set_bkg_tiles(13,0, 6,1, status_highscore_tiles);
    set_bkg_tiles(13,1, 6,1, status_score_tiles);
}

INTERNAL VOID map_draw (VOID)
{
    /* So that sprites do not draw on top of the map tiles. */
    HIDE_SPRITES;

    /* Animate the map expanding from the center. */
    set_bkg_tiles(9,9, 2,2, map_tiles);
    WAIT(1);
    set_bkg_tiles(8,8, 4,4, map_tiles);
    WAIT(1);
    set_bkg_tiles(7,7, 6,6, map_tiles);
    WAIT(1);
    set_bkg_tiles(6,6, 8,8, map_tiles);
    WAIT(1);

    /* Wait until the user wants to close the map/unpause. */
    JOYPAD_WAIT_SELECT;

    /* Restore the original room tiles and show sprites. */
    SET_MAP_DATA(TILEMAP_ROOM);
    SHOW_SPRITES;
}

/*////////////////////////////////////////////////////////////////////////////*/
