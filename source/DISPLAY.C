/*////////////////////////////////////////////////////////////////////////////*/

#define DISPLAY_HEIGHT 0x0F /* (16) Height of the display in pixels. */

GLOBAL const U8 TILE_HEART_FULL[] = { 0x0B }; /* (11) */
GLOBAL const U8 TILE_HEART_NONE[] = { 0x0C }; /* (12) */

#if 0 /************************************************************************/

INTERNAL void display_hide_window_interrupt ()
{
    HIDE_WIN;
}

INTERNAL void display_enable ()
{
    /* Set up an interrupt handler to disble showing the window layer after a */
    /* certain point is reached. This allows our heads-up display to be at    */
    /* the top of the screen without issues -- as window has no transparency. */

    STAT_REG |= 0x40;           /* Enable LYC=LY interrupt.          */
    LYC_REG   = DISPLAY_HEIGHT; /* The scanline on which to trigger. */

    disable_interrupts();
    add_LCD(display_hide_window_interrupt);
    enable_interrupts();

    set_interrupts(LCD_IFLAG|VBL_IFLAG);
}

INTERNAL void display_disable ()
{
    disable_interrupts();
    remove_LCD(display_hide_window_interrupt);
    enable_interrupts();
}

#endif /***********************************************************************/

INTERNAL void display_draw_status ()
{
    set_bkg_tiles(1,0, 1,1, TILE_HEART_FULL);
    set_bkg_tiles(2,0, 1,1, TILE_HEART_FULL);
    set_bkg_tiles(3,0, 1,1, TILE_HEART_FULL);
}

INTERNAL void display_draw_map ()
{
    HIDE_SPRITES;
    SET_MAP_DATA(TILEMAP_MAP);
    JOYPAD_WAIT_SELECT;
    SET_MAP_DATA(TILEMAP_ROOM);
    SHOW_SPRITES;
}

/*////////////////////////////////////////////////////////////////////////////*/
