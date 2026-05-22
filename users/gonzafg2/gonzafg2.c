#include "gonzafg2.h"

// Tri-layer manual: solo activa/desactiva _ADJUST cuando se entra/sale del
// estado LOWER+RAISE. NO toca _ADJUST si esta activa por otra via (LT en
// ESC/A). Usa un flag para saber si fue el tri-layer quien la prendio.
layer_state_t layer_state_set_user(layer_state_t state) {
    static bool tri_adjust_on = false;
    bool both = (state & ((1UL << _LOWER) | (1UL << _RAISE))) == ((1UL << _LOWER) | (1UL << _RAISE));
    if (both && !tri_adjust_on) {
        tri_adjust_on = true;
        state |= (1UL << _ADJUST);
    } else if (!both && tri_adjust_on) {
        tri_adjust_on = false;
        state &= ~(1UL << _ADJUST);
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == GFG_BSDL) {
        if (record->event.pressed) {
            uint8_t reg_shift = get_mods() & MOD_MASK_SHIFT;
            uint8_t osm_shift = get_oneshot_mods() & MOD_MASK_SHIFT;
            if (reg_shift || osm_shift) {
                // Shift+BSDL = forward delete (tap unico, sin key repeat para
                // evitar Shift latched durante el hold; restauramos regular y
                // oneshot por separado para no promover oneshot a regular)
                del_mods(reg_shift);
                del_oneshot_mods(osm_shift);
                tap_code(KC_DEL);
                add_mods(reg_shift);
                add_oneshot_mods(osm_shift);
            } else {
                register_code(KC_BSPC);
            }
        } else {
            unregister_code(KC_BSPC);
        }
        return false;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case GFG_ARROW:
            tap_code16(LSFT(KC_0));
            tap_code16(LSFT(KC_NUBS));
            return false;
        case GFG_SPREAD:
            tap_code(KC_DOT);
            tap_code(KC_DOT);
            tap_code(KC_DOT);
            return false;
        case GFG_EQEQ:
            tap_code16(LSFT(KC_0));
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_NEQ:
            tap_code16(LSFT(KC_1));
            tap_code16(LSFT(KC_0));
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_TEQ:
            tap_code16(LSFT(KC_0));
            tap_code16(LSFT(KC_0));
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_AND:
            tap_code16(LSFT(KC_6));
            tap_code16(LSFT(KC_6));
            return false;
        case GFG_OR:
            tap_code(KC_GRV);
            tap_code(KC_GRV);
            return false;
        case GFG_PLEQ:
            tap_code(KC_RBRC);
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_MIEQ:
            tap_code(KC_SLSH);
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_GTEQ:
            tap_code16(LSFT(KC_NUBS));
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_LTEQ:
            tap_code(KC_NUBS);
            tap_code16(LSFT(KC_0));
            return false;
        case GFG_NULC:
            tap_code16(LSFT(KC_MINS));
            tap_code16(LSFT(KC_MINS));
            return false;
        case GFG_OPTC:
            tap_code16(LSFT(KC_MINS));
            tap_code(KC_DOT);
            return false;
        case GFG_POW:
            tap_code(KC_PAST);
            tap_code(KC_PAST);
            return false;

        case GFG_SCRF:
            tap_code16(LGUI(LSFT(KC_3)));
            return false;
        case GFG_SCRA:
            tap_code16(LGUI(LSFT(KC_4)));
            return false;
        case GFG_SCRT:
            tap_code16(LGUI(LSFT(KC_5)));
            return false;
        case GFG_LOCK:
            tap_code16(LGUI(LCTL(KC_Q)));
            return false;
        case GFG_FQUIT:
            tap_code16(LGUI(LALT(KC_ESC)));
            return false;

    }
    return true;
}
