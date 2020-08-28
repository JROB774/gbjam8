/*////////////////////////////////////////////////////////////////////////////*/

GLOBAL U8 joypad_prev_state; /* Previous frame's joypad button state. */
GLOBAL U8 joypad_curr_state; /* Current frame's joypad button state.  */

#define UPDATE_JOYPAD_STATE            \
do                                     \
{                                      \
joypad_prev_state = joypad_curr_state; \
joypad_curr_state = joypad();          \
}                                      \
while (0)

/* Macros for checking if a button was pressed.       */
#define JOYPAD_PRESSED_START   ((!(joypad_prev_state & J_START )) && ( (joypad_curr_state & J_START )))
#define JOYPAD_PRESSED_SELECT  ((!(joypad_prev_state & J_SELECT)) && ( (joypad_curr_state & J_SELECT)))
#define JOYPAD_PRESSED_A       ((!(joypad_prev_state & J_A     )) && ( (joypad_curr_state & J_A     )))
#define JOYPAD_PRESSED_B       ((!(joypad_prev_state & J_B     )) && ( (joypad_curr_state & J_B     )))
#define JOYPAD_PRESSED_PAD_U   ((!(joypad_prev_state & J_UP    )) && ( (joypad_curr_state & J_UP    )))
#define JOYPAD_PRESSED_PAD_R   ((!(joypad_prev_state & J_RIGHT )) && ( (joypad_curr_state & J_RIGHT )))
#define JOYPAD_PRESSED_PAD_D   ((!(joypad_prev_state & J_DOWN  )) && ( (joypad_curr_state & J_DOWN  )))
#define JOYPAD_PRESSED_PAD_L   ((!(joypad_prev_state & J_LEFT  )) && ( (joypad_curr_state & J_LEFT  )))

/* Macros for checking if a button was released.      */
#define JOYPAD_RELEASED_START  (( (joypad_prev_state & J_START )) && (!(joypad_curr_state & J_START )))
#define JOYPAD_RELEASED_SELECT (( (joypad_prev_state & J_SELECT)) && (!(joypad_curr_state & J_SELECT)))
#define JOYPAD_RELEASED_A      (( (joypad_prev_state & J_A     )) && (!(joypad_curr_state & J_A     )))
#define JOYPAD_RELEASED_B      (( (joypad_prev_state & J_B     )) && (!(joypad_curr_state & J_B     )))
#define JOYPAD_RELEASED_PAD_U  (( (joypad_prev_state & J_UP    )) && (!(joypad_curr_state & J_UP    )))
#define JOYPAD_RELEASED_PAD_R  (( (joypad_prev_state & J_RIGHT )) && (!(joypad_curr_state & J_RIGHT )))
#define JOYPAD_RELEASED_PAD_D  (( (joypad_prev_state & J_DOWN  )) && (!(joypad_curr_state & J_DOWN  )))
#define JOYPAD_RELEASED_PAD_L  (( (joypad_prev_state & J_LEFT  )) && (!(joypad_curr_state & J_LEFT  )))

/* Macros for checking if a button is currently down. */
#define JOYPAD_DOWN_START  ( (joypad() & J_START ))
#define JOYPAD_DOWN_SELECT ( (joypad() & J_SELECT))
#define JOYPAD_DOWN_A      ( (joypad() & J_A     ))
#define JOYPAD_DOWN_B      ( (joypad() & J_B     ))
#define JOYPAD_DOWN_PAD_U  ( (joypad() & J_UP    ))
#define JOYPAD_DOWN_PAD_R  ( (joypad() & J_RIGHT ))
#define JOYPAD_DOWN_PAD_D  ( (joypad() & J_DOWN  ))
#define JOYPAD_DOWN_PAD_L  ( (joypad() & J_LEFT  ))

/* Macros for checking if a button is currently up.   */
#define JOYPAD_UP_START    (!(joypad() & J_START ))
#define JOYPAD_UP_SELECT   (!(joypad() & J_SELECT))
#define JOYPAD_UP_A        (!(joypad() & J_A     ))
#define JOYPAD_UP_B        (!(joypad() & J_B     ))
#define JOYPAD_UP_PAD_U    (!(joypad() & J_UP    ))
#define JOYPAD_UP_PAD_R    (!(joypad() & J_RIGHT ))
#define JOYPAD_UP_PAD_D    (!(joypad() & J_DOWN  ))
#define JOYPAD_UP_PAD_L    (!(joypad() & J_LEFT  ))

/*////////////////////////////////////////////////////////////////////////////*/
