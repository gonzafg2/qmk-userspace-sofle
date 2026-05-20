#include QMK_KEYBOARD_H
#include "gonzafg2.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  A   |  S   |  D   |  F   |  G   |-------.    ,-------|  H   |  J   |  K   |  L   |  N   |  ´   |
 * |------+------+------+------+------+------| MUTM  |    | LOCK  |------+------+------+------+------+------|
 * | LGUI |  Z   |  X   |  C   |  V   |  B   |-------|    |-------|  N   |  M   |  ,   |  .   |  -   | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | LCTL | LALT | --- | LWR | SPC |       | ENT | RSE | --- | RALT | RCTL |
 */
[_BASE] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    GFG_BSDL,
  KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
  KC_LGUI,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    GFG_MUTM,               GFG_LOCK,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, GFG_ESCAD,
                     KC_LCTL, KC_LALT, XXXXXXX, GFG_LWR, KC_SPC,                  KC_ENT,   GFG_RSE, XXXXXXX, KC_RALT, KC_RCTL
),

/* Lower (numpad + simbolos LATAM, fila numerica se mantiene de Base)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  7   |  8   |  9   |  /   |  *   |                    |  (   |  )   |  \   |  !   |  ?   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |  4   |  5   |  6   |  +   |  -   |-------.    ,-------|  {   |  }   |  ~   |  '   |  "   |  `   |
 * |------+------+------+------+------+------| BRDN  |    | BRUP  |------+------+------+------+------+------|
 * | CMD  |  1   |  2   |  3   |  .   |  0   |-------|    |-------|  [   |  ]   |  <   |  >   |  |   |  _   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- |  ▼  | SPC |        | ENT | RSE | --- | RALT | RCTL |
 */
[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______,  KC_7,    KC_8,    KC_9,    KC_PSLS, KC_PAST,                                    KC_LPRN, KC_RPRN, KC_BSLS, KC_EXLM, KC_QUES, _______,
  _______,  KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PMNS,                                    KC_LCBR, KC_RCBR, KC_TILD, KC_QUOT, KC_DQUO, KC_GRV,
  _______,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_0,    KC_BRID,                KC_BRIU,   KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_PIPE, KC_UNDS,
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Raise (operadores programacion + navegacion + F-keys)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  | F12  |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  !   |  @   |  #   |  $   |  %   |                    |      |QK_RPT|      |      | +=   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |  ^   |      |  &   |  &&  |  ||  |-------.    ,-------| LEFT | DOWN |  UP  | RGHT | -=   |      |
 * |------+------+------+------+------+------| MUTM  |    | LOCK  |------+------+------+------+------+------|
 * | CMD  | =>   | ...  |  ==  |  !== |  === |-------|    |-------| HOME | PGDN | PGUP | END  |      | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- | LWR | SPC |        | ENT |  ▼  | --- | RALT | RCTL |
 */
[_RAISE] = LAYOUT(
  _______,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                    XXXXXXX, QK_REP,  XXXXXXX, XXXXXXX, GFG_PLEQ,_______,
  _______,  KC_CIRC, XXXXXXX, KC_AMPR, GFG_AND, GFG_OR,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, GFG_MIEQ,XXXXXXX,
  _______,  GFG_ARROW,GFG_SPREAD,GFG_EQEQ,GFG_NEQ,GFG_TEQ,_______,                _______,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Adjust (sistema, media, macros mac, mouse toggle)
 * Acceso: hold ambos LWR+RSE (tri-layer) | hold ESC pinky der | combo TAB+BSDL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | SCRF | SCRA | SCRT | LOCK | FQT  |                    |TGMOU |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | VOLD | MUTE | VOLU |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | MPRV | MPLY | MNXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           |     |     | --- |     |     |        |     |     | --- |     |     |
 */
[_ADJUST] = LAYOUT(
  QK_BOOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  GFG_SCRF,GFG_SCRA,GFG_SCRT,GFG_LOCK,GFG_FQUIT,                                  TG(_MOUSE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                _______,   XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Mouse (movimiento, scroll, clicks)
 * Acceso: hold encoder push izq (momentaneo) | tap TG_MOUSE desde Adjust (persistente)
 * Salir persistente: tap EXIT (esquina sup der o esquina inf der)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      | BTN1 | BTN3 | BTN2 |      | EXIT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | M_LF | M_DN | M_UP | M_RT |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |      |      |      |      |      |-------.    ,-------|      | S_LF | S_DN | S_UP | S_RT |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | CMD  |      |      |      |      |      |-------|    |-------|      |      |      |      |      | EXIT |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- |     | SPC |        | ENT |     | --- | RALT | RCTL |
 */
[_MOUSE] = LAYOUT(
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, TG(_MOUSE),
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_MOUSE),
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),             ENCODER_CCW_CW(MS_WHLD, MS_WHLU)            },
    [_LOWER]  = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),             ENCODER_CCW_CW(MS_WHLL, MS_WHLR)            },
    [_RAISE]  = { ENCODER_CCW_CW(LGUI(KC_LBRC), LGUI(KC_RBRC)), ENCODER_CCW_CW(LALT(KC_LEFT), LALT(KC_RIGHT)) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),             ENCODER_CCW_CW(KC_BRID, KC_BRIU)            },
    [_MOUSE]  = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU),             ENCODER_CCW_CW(MS_WHLL, MS_WHLR)            },
};
#endif

const uint16_t PROGMEM combo_caps_word[] = { KC_F, KC_J, COMBO_END };
const uint16_t PROGMEM combo_adjust[]    = { KC_TAB, GFG_BSDL, COMBO_END };

combo_t key_combos[] = {
    COMBO(combo_caps_word, CW_TOGG),
    COMBO(combo_adjust,    MO(_ADJUST)),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_270;
}

static void render_logo(void) {
    static const char PROGMEM gfg_logo[] = {
        // 32x32 GFG mark, raw bytes (4 pages of 32 cols)
        0x00,0x00,0xFC,0xFE,0x07,0x03,0x03,0x03,0x03,0x03,0x03,0x83,0xC3,0xE3,0x73,0x33,
        0x33,0x33,0x33,0x33,0x73,0xE3,0xC3,0x83,0x03,0x03,0x03,0x03,0x07,0xFE,0xFC,0x00,
        0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,
        0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
        0x00,0x00,0xFF,0xFF,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,
        0x00,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xFF,0xFF,0x00,0x00,
        0x00,0x00,0x3F,0x7F,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC1,0xC3,0xC7,0xCE,0xCC,
        0xCC,0xCC,0xCC,0xCC,0xCE,0xC7,0xC3,0xC1,0xC0,0xC0,0xC0,0xC0,0xE0,0x7F,0x3F,0x00,
    };
    oled_write_raw_P(gfg_logo, sizeof(gfg_logo));
}

static void render_layer_state(void) {
    oled_set_cursor(0, 6);
    oled_write_P(PSTR("Sofle\n"), false);
    oled_write_P(PSTR("by ZK\n\n"), false);
    oled_write_P(PSTR("LAYER\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:   oled_write_P(PSTR("Base "), false); break;
        case _LOWER:  oled_write_P(PSTR("Lwr  "), false); break;
        case _RAISE:  oled_write_P(PSTR("Rse  "), false); break;
        case _ADJUST: oled_write_P(PSTR("Adj  "), false); break;
        case _MOUSE:  oled_write_P(PSTR("Mouse"), false); break;
        default:      oled_write_P(PSTR("?    "), false);
    }
}

static void render_mod_status(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 11);
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("CTL ") : PSTR("    "), false);
    oled_set_cursor(0, 12);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SFT ") : PSTR("    "), false);
}

bool oled_task_user(void) {
    render_logo();
    if (is_keyboard_master()) {
        render_layer_state();
        render_mod_status();
    } else {
        oled_set_cursor(0, 6);
        oled_write_P(PSTR("gonzafg2\n\n"), false);
        oled_write_P(PSTR("typing\n"), false);
        oled_write_P(PSTR("with\n"), false);
        oled_write_P(PSTR("Sofle\n"), false);
    }
    return false;
}
#endif
