#include QMK_KEYBOARD_H
#include "gonzafg2.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  A   |  S   |  D   |  F   |  G   |-------.    ,-------|  H   |  J   |  K   |  L   |  Ñ   |  ´   |
 * |------+------+------+------+------+------| MUTE  |    | LOCK  |------+------+------+------+------+------|
 * | LCTL |  Z   |  X   |  C   |  V   |  B   |-------|    |-------|  N   |  M   |  ,   |  .   |  -   | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | LGUI | LALT | LWR  | LWRENT |LSFTMS|     | SPC | RSEENT| RSE  | RALT | RGUI |
 */
[_BASE] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    GFG_BSDL,
  KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
  KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,                GFG_LOCK,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, GFG_ESCAD,
                     KC_LGUI, KC_LALT, GFG_LWR, GFG_LWRENT, GFG_SFTMS,     KC_SPC, GFG_RSEENT, GFG_RSE, KC_RALT, KC_RGUI
),

/* Lower (numpad + simbolos LATAM, fila numerica se mantiene de Base)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  7   |  8   |  9   |  /   |  *   |                    |  (   |  )   |  \   |  !   |  ?   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  4   |  5   |  6   |  +   |  -   |-------.    ,-------|  {   |  }   |  ~   |  '   |  "   |  `   |
 * |------+------+------+------+------+------| BRDN  |    | BRUP  |------+------+------+------+------+------|
 * | LCTL |  1   |  2   |  3   |  .   |  0   |-------|    |-------|  [   |  ]   |  <   |  >   |  |   |  _   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | LGUI | LALT |      | LWRENT | LSFT |      | SPC  | RSEENT| RSE  | RALT | RGUI |
 */
[_LOWER] = LAYOUT(
  KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TAB,   KC_7,    KC_8,    KC_9,    KC_PSLS, KC_PAST,                                    KC_LPRN, KC_RPRN, KC_BSLS, KC_EXLM, KC_QUES, GFG_BSDL,
  KC_LSFT,  KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PMNS,                                    KC_LCBR, KC_RCBR, KC_TILD, KC_QUOT, KC_DQUO, KC_GRV,
  KC_LCTL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_0,    KC_BRID,                KC_BRIU,   KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_PIPE, KC_UNDS,
                     KC_LGUI, KC_LALT, _______, _______, KC_LSFT,        KC_SPC, _______, _______, KC_RALT, KC_RGUI
),

/* Raise (operadores programacion + navegacion)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  | F12  |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  !   |  @   |  #   |  $   |  %   |                    |      |QK_RPT|      |      | +=   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  ^   |      |  &   |  &&  |  ||  |-------.    ,-------| LEFT | DOWN |  UP  | RGHT | -=   |      |
 * |------+------+------+------+------+------| MUTE  |    | LOCK  |------+------+------+------+------+------|
 * | LCTL | =>   | ...  |  ==  | !==  | ===  |-------|    |-------| HOME | PGDN | PGUP | END  |      | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | LGUI | LALT |      | LWRENT | LSFT |      | SPC  | RSEENT|      | RALT | RGUI |
 */
[_RAISE] = LAYOUT(
  KC_ESC,   KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TAB,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                    XXXXXXX, QK_REP,  XXXXXXX, XXXXXXX, GFG_PLEQ,GFG_BSDL,
  KC_LSFT,  KC_CIRC, XXXXXXX, KC_AMPR, GFG_AND, GFG_OR,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, GFG_MIEQ,XXXXXXX,
  KC_LCTL,  GFG_ARROW,GFG_SPREAD,GFG_EQEQ,GFG_NEQ,GFG_TEQ,KC_MUTE,                GFG_LOCK, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, GFG_ESCAD,
                     KC_LGUI, KC_LALT, _______, _______, KC_LSFT,        KC_SPC, _______, _______, KC_RALT, KC_RGUI
),

/* Adjust (sistema, media, RGB)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |QK_BT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | SCRF | SCRA | SCRT | LOCK | FQUIT|                    | RGBTOG|RGBMOD|RGB_HUI|RGB_SAI|RGB_VAI|     |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| MOUSE|VOLDN | MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------| MUTE  |    | LOCK  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           |      |      |      |        |      |     |      |      |      |      |      |
 */
[_ADJUST] = LAYOUT(
  QK_BOOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  GFG_SCRF,GFG_SCRA,GFG_SCRT,GFG_LOCK,GFG_FQUIT,                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    TG(_MOUSE), KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                _______,   XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                     _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
),

/* Mouse */
[_MOUSE] = LAYOUT(
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                _______,   XXXXXXX, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, TG(_MOUSE),
                     _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
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

static void render_wpm(void) {
    oled_set_cursor(0, 13);
    oled_write_P(PSTR("WPM:\n"), false);
    char wpm_str[5];
    snprintf(wpm_str, sizeof(wpm_str), "%3d", get_current_wpm());
    oled_write(wpm_str, false);
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
        render_wpm();
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
