/*////////////////////////////////////////////////////////////////////////////*/

#define SCREEN_WIDTH        0xA0   /* (160) Width of the screen in pixels.    */
#define SCREEN_HEIGHT       0x90   /* (144) Height of the screen in pixels.   */

#define SCREEN_TILES_WIDTH  0x14   /* ( 20) Width of the screen in tiles.     */
#define SCREEN_TILES_HEIGHT 0x12   /* ( 18) Height of the screen in tiles.    */

#define TILE_WIDTH          0x08   /* (  8) Width of a tile in pixels.        */
#define TILE_HEIGHT         0x08   /* (  8) Height of a tile in pixels.       */

#define SPRITE_X_OFFSET     0x08   /* (  8) Sprite X offset in pixels.        */
#define SPRITE_Y_OFFSET     0x10   /* ( 16) Sprite Y offset in pixels.        */

#define BOOL                BOOLEAN
#define VOID                void

#define  U8                 UINT8
#define U16                 UINT16
#define U32                 UINT32
#define  S8                 INT8
#define S16                 INT16
#define S32                 INT32

#define INTERNAL            static
#define GLOBAL              static

#define DIR_U               0x01   /* Direction flag to represet up.          */
#define DIR_R               0x02   /* Direction flag to represet right.       */
#define DIR_D               0x04   /* Direction flag to represet down.        */
#define DIR_L               0x08   /* Direction flag to represet left.        */

#define BKG_PAL0             BGP_REG
#define SPR_PAL0            OBP0_REG
#define SPR_PAL1            OBP1_REG

typedef struct _RECT_ { U8 x, y, w, h; } RECT;

#define SET_SPR_DATA(name) set_sprite_data(name##_OFFSET, name##_LENGTH,        name)
#define SET_BKG_DATA(name) set_bkg_data   (name##_OFFSET, name##_LENGTH,        name)
#define SET_MAP_DATA(name) set_bkg_tiles  (name##_X,name##_Y,name##_W,name##_H, name)

#define   SET_FLAGS(x, flags) ((x) |=  (flags))
#define UNSET_FLAGS(x, flags) ((x) &= ~(flags))

#define WAIT(time)                      \
do                                      \
{                                       \
U8 _wait_;                              \
for (_wait_=0; _wait_<time; ++_wait_) { \
    wait_vbl_done();                    \
}                                       \
}                                       \
while (0)

#define CHECK_COLLISION(a, b)                  \
(!(((a->x+a->w)<b->x) || (a->x>(b->x+b->w)) || \
   ((a->y+a->h)<b->y) || (a->y>(b->y+b->h))))

#if DEBUG_MODE /* ----------------------------------------------------------- */

#include <gb/bgb_emu.h>
#include <stdio.h>

/* Some debugging utilities for the BGB emulator if we're in DEBUG_MODE. */
#define DEBUG_PROFILE_BEGIN(msg) BGB_PROFILE_BEGIN(msg        )
#define DEBUG_PROFILE_END(  msg) BGB_PROFILE_END  (msg        )
#define DEBUG_LOG_MESSAGE(  ...) BGB_MESSAGE_FMT  (__VA_ARGS__)

#else

#define DEBUG_PROFILE_BEGIN(msg)
#define DEBUG_PROFILE_END(  msg)
#define DEBUG_LOG_MESSAGE(  ...)

#endif  /* ------------------------------------------------------------------ */

/*////////////////////////////////////////////////////////////////////////////*/
