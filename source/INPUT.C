/*////////////////////////////////////////////////////////////////////////////*/

#define J_ANY 0xFF           /* Define to represent any joypad button. */

GLOBAL U8 joypad_prev_state; /* Previous frame's joypad button state.  */
GLOBAL U8 joypad_curr_state; /* Current frame's joypad button state.   */

#define UPDATE_JOYPAD_STATE            \
do                                     \
{                                      \
joypad_prev_state = joypad_curr_state; \
joypad_curr_state = joypad();          \
}                                      \
while (0)

#define JOYPAD_PRESSED( buttons         ) ((!(joypad_prev_state & (buttons         ))) && ( (joypad_curr_state & (buttons))))
#define JOYPAD_RELEASED(buttons         ) (( (joypad_prev_state & (buttons         ))) && (!(joypad_curr_state & (buttons))))
#define JOYPAD_DOWN(    buttons         ) (  (joypad()          & (buttons         )))
#define JOYPAD_UP(      buttons         ) ( !(joypad()          & (buttons         )))
#define JOYPAD_WAIT(    buttons         ) (   joypad_wait         (buttons         ))
#define JOYPAD_WAITTIME(buttons, timeout) (   joypad_waittime     (buttons, timeout))

/* Macros for checking if a button was pressed.       */
#define JOYPAD_PRESSED_START   JOYPAD_PRESSED(J_START )
#define JOYPAD_PRESSED_SELECT  JOYPAD_PRESSED (J_SELECT)
#define JOYPAD_PRESSED_A       JOYPAD_PRESSED (J_A     )
#define JOYPAD_PRESSED_B       JOYPAD_PRESSED (J_B     )
#define JOYPAD_PRESSED_PAD_U   JOYPAD_PRESSED (J_UP    )
#define JOYPAD_PRESSED_PAD_R   JOYPAD_PRESSED (J_RIGHT )
#define JOYPAD_PRESSED_PAD_D   JOYPAD_PRESSED (J_DOWN  )
#define JOYPAD_PRESSED_PAD_L   JOYPAD_PRESSED (J_LEFT  )
#define JOYPAD_PRESSED_ANY     JOYPAD_PRESSED (J_ANY   )
/* Macros for checking if a button was released.      */
#define JOYPAD_RELEASED_START  JOYPAD_RELEASED(J_START )
#define JOYPAD_RELEASED_SELECT JOYPAD_RELEASED(J_SELECT)
#define JOYPAD_RELEASED_A      JOYPAD_RELEASED(J_A     )
#define JOYPAD_RELEASED_B      JOYPAD_RELEASED(J_B     )
#define JOYPAD_RELEASED_PAD_U  JOYPAD_RELEASED(J_UP    )
#define JOYPAD_RELEASED_PAD_R  JOYPAD_RELEASED(J_RIGHT )
#define JOYPAD_RELEASED_PAD_D  JOYPAD_RELEASED(J_DOWN  )
#define JOYPAD_RELEASED_PAD_L  JOYPAD_RELEASED(J_LEFT  )
#define JOYPAD_RELEASED_ANY    JOYPAD_RELEASED(J_ANY   )
/* Macros for checking if a button is currently down. */
#define JOYPAD_DOWN_START      JOYPAD_DOWN    (J_START )
#define JOYPAD_DOWN_SELECT     JOYPAD_DOWN    (J_SELECT)
#define JOYPAD_DOWN_A          JOYPAD_DOWN    (J_A     )
#define JOYPAD_DOWN_B          JOYPAD_DOWN    (J_B     )
#define JOYPAD_DOWN_PAD_U      JOYPAD_DOWN    (J_UP    )
#define JOYPAD_DOWN_PAD_R      JOYPAD_DOWN    (J_RIGHT )
#define JOYPAD_DOWN_PAD_D      JOYPAD_DOWN    (J_DOWN  )
#define JOYPAD_DOWN_PAD_L      JOYPAD_DOWN    (J_LEFT  )
#define JOYPAD_DOWN_ANY        JOYPAD_DOWN    (J_ANY   )
/* Macros for checking if a button is currently up.   */
#define JOYPAD_UP_START        JOYPAD_UP      (J_START )
#define JOYPAD_UP_SELECT       JOYPAD_UP      (J_SELECT)
#define JOYPAD_UP_A            JOYPAD_UP      (J_A     )
#define JOYPAD_UP_B            JOYPAD_UP      (J_B     )
#define JOYPAD_UP_PAD_U        JOYPAD_UP      (J_UP    )
#define JOYPAD_UP_PAD_R        JOYPAD_UP      (J_RIGHT )
#define JOYPAD_UP_PAD_D        JOYPAD_UP      (J_DOWN  )
#define JOYPAD_UP_PAD_L        JOYPAD_UP      (J_LEFT  )
#define JOYPAD_UP_ANY          JOYPAD_UP      (J_ANY   )
/* Macros for waiting until a button is pressed.      */
#define JOYPAD_WAIT_START      JOYPAD_WAIT    (J_START )
#define JOYPAD_WAIT_SELECT     JOYPAD_WAIT    (J_SELECT)
#define JOYPAD_WAIT_A          JOYPAD_WAIT    (J_A     )
#define JOYPAD_WAIT_B          JOYPAD_WAIT    (J_B     )
#define JOYPAD_WAIT_PAD_U      JOYPAD_WAIT    (J_UP    )
#define JOYPAD_WAIT_PAD_R      JOYPAD_WAIT    (J_RIGHT )
#define JOYPAD_WAIT_PAD_D      JOYPAD_WAIT    (J_DOWN  )
#define JOYPAD_WAIT_PAD_L      JOYPAD_WAIT    (J_LEFT  )
#define JOYPAD_WAIT_ANY        JOYPAD_WAIT    (J_ANY   )

/* Internal implementation of the JOYPAD_WAIT macro. */
INTERNAL void joypad_wait (U8 buttons)
{
    while (TRUE) {
        UPDATE_JOYPAD_STATE;
        if (JOYPAD_PRESSED(buttons)) {
            break;
        }
        wait_vbl_done();
    }
}

/* Internal implementation of the JOYPAD_WAITTIME macro. */
INTERNAL BOOL joypad_waittime (U8 buttons, U8 timeout)
{
    for (i=0; i<timeout; ++i) {
        UPDATE_JOYPAD_STATE;
        if (JOYPAD_PRESSED(buttons)) {
            return TRUE;
        }
        wait_vbl_done();
    }
    return FALSE;
}

/*////////////////////////////////////////////////////////////////////////////*/
