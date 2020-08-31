/*////////////////////////////////////////////////////////////////////////////*/

/* Some debugging utilities for the BGB emulator if we're in DEBUG_MODE. */
#if DEBUG_MODE
#include <gb/bgb_emu.h>
#define DEBUG_PROFILE_BEGIN(msg) BGB_PROFILE_BEGIN(msg        )
#define DEBUG_PROFILE_END(  msg) BGB_PROFILE_END  (msg        )
#define DEBUG_LOG_MESSAGE(  ...) BGB_MESSAGE_FMT  (__VA_ARGS__)
#else
#define DEBUG_PROFILE_BEGIN(msg)
#define DEBUG_PRFILE_END(   msg)
#define DEBUG_LOG_MESSAGE(  ...)
#endif

/*////////////////////////////////////////////////////////////////////////////*/
