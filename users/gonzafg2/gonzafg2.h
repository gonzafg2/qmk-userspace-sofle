#pragma once

#include "quantum.h"

enum gfg_layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum gfg_keycodes {
    GFG_ARROW = QK_USER,
    GFG_SPREAD,
    GFG_EQEQ,
    GFG_NEQ,
    GFG_TEQ,
    GFG_AND,
    GFG_OR,
    GFG_PLEQ,
    GFG_MIEQ,
    GFG_SCRF,
    GFG_SCRA,
    GFG_SCRT,
    GFG_LOCK,
    GFG_FQUIT,
    GFG_BSDL,
};

#define GFG_LWR     MO(_LOWER)
#define GFG_RSE     MO(_RAISE)
#define GFG_ADJ     MO(_ADJUST)
#define GFG_ESCAD   LT(_ADJUST, KC_ESC)
#define GFG_SFTMS   LT(_MOUSE, KC_LSFT)
#define GFG_LWRENT  LT(_LOWER, KC_ENT)
#define GFG_RSEENT  LT(_RAISE, KC_ENT)

#define GFG_ESC_NIO LCTL(LSFT(LGUI(KC_2)))
