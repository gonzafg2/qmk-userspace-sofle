#include "gonzafg2.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case GFG_ARROW:   SEND_STRING("=>");  return false;
        case GFG_SPREAD:  SEND_STRING("..."); return false;
        case GFG_EQEQ:    SEND_STRING("=="); return false;
        case GFG_NEQ:     SEND_STRING("!=="); return false;
        case GFG_TEQ:     SEND_STRING("==="); return false;
        case GFG_AND:     SEND_STRING("&&"); return false;
        case GFG_OR:      SEND_STRING("||"); return false;
        case GFG_PLEQ:    SEND_STRING("+="); return false;
        case GFG_MIEQ:    SEND_STRING("-="); return false;

        case GFG_SCRF:    SEND_STRING(SS_LGUI(SS_LSFT("3"))); return false;
        case GFG_SCRA:    SEND_STRING(SS_LGUI(SS_LSFT("4"))); return false;
        case GFG_SCRT:    SEND_STRING(SS_LGUI(SS_LSFT("5"))); return false;
        case GFG_LOCK:    SEND_STRING(SS_LGUI(SS_LCTL("q"))); return false;
        case GFG_FQUIT:   SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_ESC)))); return false;

        case GFG_BSDL: {
            uint8_t mods = get_mods() | get_oneshot_mods();
            if (mods & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);
                tap_code(KC_DEL);
                set_mods(mods);
            } else {
                tap_code(KC_BSPC);
            }
            return false;
        }
    }
    return true;
}
