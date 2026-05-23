#pragma once

#define TAPPING_TERM 200
#define QUICK_TAP_TERM 150
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define FORCE_NKRO
#define DEBOUNCE 8

// Mouse: modo kinetic para movimiento smooth con momentum (mas natural,
// mas preciso al inicio del tap, acelera con hold).
#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY              8
#define MOUSEKEY_INTERVAL           8
#define MOUSEKEY_MOVE_DELTA         16     // px iniciales por tap (default 25)
#define MOUSEKEY_INITIAL_SPEED      50     // px/s arranque (default 100)
#define MOUSEKEY_BASE_SPEED         3000   // px/s tope normal (default 5000)
#define MOUSEKEY_DECELERATED_SPEED  400
#define MOUSEKEY_ACCELERATED_SPEED  3000

#define COMBO_TERM 50
#define COMBO_MUST_HOLD_PER_COMBO

#define CAPS_WORD_IDLE_TIMEOUT 5000

#define USB_SUSPEND_WAKEUP_DELAY 0
