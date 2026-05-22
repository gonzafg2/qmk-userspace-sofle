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
 * |------+------+------+------+------+------| MUTM  |    | PLAY  |------+------+------+------+------+------|
 * | LGUI |  Z   |  X   |  C   |  V   |  B   |-------|    |-------|  N   |  M   |  ,   |  .   |  -   | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | ---  | LALT | LCTL| LWR | SPC |       | ENT | RSE | RALT| RCTL | ---  |
 */
[_BASE] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    GFG_BSDL,
  KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
  KC_LGUI,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    GFG_MUTM,               KC_MPLY,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, GFG_ESCAD,
                     XXXXXXX, KC_LALT, KC_LCTL, GFG_LWR, KC_SPC,                  KC_ENT,   GFG_RSE, KC_RALT, KC_RCTL, XXXXXXX
),

/* Lower (numpad + simbolos LATAM, fila numerica se mantiene de Base)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  7   |  8   |  9   |  /   |  *   |                    |  (   |  )   |  \   |  !   |  ?   | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |  4   |  5   |  6   |  +   |  -   |-------.    ,-------|  {   |  }   |  ~   |  '   |  "   |  `   |
 * |------+------+------+------+------+------| BRDN  |    | BRUP  |------+------+------+------+------+------|
 * | CMD  |  1   |  2   |  3   |  .   |  0   |-------|    |-------|  [   |  ]   |  <   |  >   |  |   |  _   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- |  ▼  | SPC |        | ENT | RSE | --- | RALT | RCTL |
 */
// Right side: keycodes posicionales para macOS layout Spanish LATAM (mismo enfoque que zmk-config-corne)
[_LOWER] = LAYOUT(
  KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,      KC_F7,      KC_F8,        KC_F9,      KC_F10,     KC_F11,
  _______,  KC_7,    KC_8,    KC_9,    KC_PSLS, KC_PAST,                                    S(KC_8),    S(KC_9),    A(KC_MINS),   KC_EXLM,    S(KC_MINS), _______,
  _______,  KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PMNS,                                    KC_QUOT,    KC_BSLS,    A(KC_RBRC),   KC_MINS,    S(KC_2),    A(KC_BSLS),
  _______,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_0,    KC_BRID,                KC_BRIU,   S(KC_QUOT), S(KC_BSLS), KC_NUBS,      S(KC_NUBS), KC_GRV,     S(KC_SLSH),
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Raise (operadores programacion + navegacion)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  =   |  >=  |  <=  |  ??  |  ?.  |  **  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  !   |  @   |  #   |  $   |  %   |                    |      |QK_REP|      |      |      | BSDL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |  ^   |  +=  |  &   |  &&  |  ||  |-------.    ,-------| LEFT | DOWN |  UP  | RGHT | -=   |      |
 * |------+------+------+------+------+------| MUTM  |    | PLAY  |------+------+------+------+------+------|
 * | CMD  | =>   | ...  |  ==  |  !== |  === |-------|    |-------| HOME | PGDN | PGUP | END  |      | ESCAD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- | LWR | SPC |        | ENT |  ▼  | --- | RALT | RCTL |
 */
[_RAISE] = LAYOUT(
  S(KC_0),  GFG_GTEQ,GFG_LTEQ,GFG_NULC,GFG_OPTC,GFG_POW,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,  KC_EXLM,    A(KC_Q),   KC_HASH, KC_DLR,  KC_PERC,                                XXXXXXX, QK_REP,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______,  A(KC_QUOT), GFG_PLEQ,  S(KC_6), GFG_AND, GFG_OR,                                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, GFG_MIEQ,XXXXXXX,
  _______,  GFG_ARROW,GFG_SPREAD,GFG_EQEQ,GFG_NEQ,GFG_TEQ,_______,                _______,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______,
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Adjust (sistema, media, macros mac, mouse toggle, RGB)
 * Acceso: hold ambos LWR+RSE (tri-layer) | hold ESC pinky der
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT | TOG  | NXT  | HU+  | SA+  | VA+  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SP+  | SP-  | PRV  | HU-  | SA-  | VA-  |                    |TGMOU |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | SCRF | SCRA | SCRT | LOCK | FQT  |-------.    ,-------|      | VOLD | MUTE | VOLU |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | MPRV | MPLY | MNXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           |     |     | --- |     |     |        |     |     | --- |     |     |
 */
[_ADJUST] = LAYOUT(
  QK_BOOT,  RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RM_SPDU,  RM_SPDD, RM_PREV, RM_HUED, RM_SATD, RM_VALD,                                    TG(_MOUSE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  GFG_SCRF,GFG_SCRA,GFG_SCRT,GFG_LOCK,GFG_FQUIT,                                  XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                _______,   XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),

/* Mouse (movimiento, scroll, clicks)
 * Acceso: hold encoder push izq (momentaneo) | tap TG_MOUSE desde Adjust (persistente)
 * Salir persistente: tap EXIT (esquina sup der o esquina inf der)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | BTN1 | BTN3 | BTN2 |      |      | EXIT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | M_LF | M_DN | M_UP | M_RT |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | SFT  |      |      |      |      |      |-------.    ,-------| S_LF | S_DN | S_UP | S_RT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | CMD  |      |      |      |      |      |-------|    |-------|      |      |      |      |      | EXIT |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *           | CTL | ALT | --- |     | SPC |        | ENT |     | --- | RALT | RCTL |
 */
[_MOUSE] = LAYOUT(
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, XXXXXXX, TG(_MOUSE),
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, XXXXXXX,
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_MOUSE),
                     _______, _______, _______, _______, _______,                _______,   _______, _______, _______, _______
),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),             ENCODER_CCW_CW(MS_WHLU, MS_WHLD)            },
    [_LOWER]  = { ENCODER_CCW_CW(KC_BRIU, KC_BRID),             ENCODER_CCW_CW(MS_WHLR, MS_WHLL)            },
    [_RAISE]  = { ENCODER_CCW_CW(LGUI(KC_RBRC), LGUI(KC_LBRC)), ENCODER_CCW_CW(LALT(KC_RIGHT), LALT(KC_LEFT)) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_MNXT, KC_MPRV),             ENCODER_CCW_CW(KC_BRIU, KC_BRID)            },
    [_MOUSE]  = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD),             ENCODER_CCW_CW(MS_WHLR, MS_WHLL)            },
};
#endif


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_270;
}

static void render_logo(void) {
    static const char PROGMEM gfg_logo[] = {
        // 32x32 "GFG" iniciales, Helvetica Neue Condensed Black 20px, SSD1306 vertical LSB-first
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0xF8,0xFE,0xFF,0x07,0x07,0xC7,0xDF,0xDE,0xDC,0x00,0x00,0xFE,0xFE,0xFE,0xCE,
        0xCE,0xCE,0xCE,0x0E,0x00,0x00,0xF8,0xFE,0xFF,0x07,0x07,0xC7,0xDF,0xDE,0xDC,0x00,
        0x00,0x1F,0x3F,0x7F,0x70,0x70,0x71,0x3F,0x7F,0x7F,0x00,0x00,0x7F,0x7F,0x7F,0x01,
        0x01,0x01,0x01,0x00,0x00,0x00,0x1F,0x3F,0x7F,0x70,0x70,0x71,0x3F,0x7F,0x7F,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    oled_write_raw_P(gfg_logo, sizeof(gfg_logo));
}

static void render_layer_state(void) {
    static uint8_t last_rgb_mode = 0xFF;
    static uint16_t rgb_mode_timer = 0;
    static bool show_rgb = false;

    uint8_t current_mode = rgb_matrix_get_mode();
    if (current_mode != last_rgb_mode) {
        if (last_rgb_mode != 0xFF) {
            rgb_mode_timer = timer_read();
            show_rgb = true;
        }
        last_rgb_mode = current_mode;
    }
    if (show_rgb && timer_elapsed(rgb_mode_timer) > 2000) {
        show_rgb = false;
    }

    oled_set_cursor(0, 5);
    oled_write_P(PSTR(" by  SofleRGBv2rev2 "), false);

    oled_set_cursor(0, 15);
    if (show_rgb) {
        switch (current_mode) {
            case RGB_MATRIX_GRADIENT_LEFT_RIGHT:    oled_write_P(PSTR("Grad "), false); break;
            case RGB_MATRIX_STARLIGHT:              oled_write_P(PSTR("Star "), false); break;
            case RGB_MATRIX_CYCLE_LEFT_RIGHT:       oled_write_P(PSTR("Cycl "), false); break;
            case RGB_MATRIX_TYPING_HEATMAP:         oled_write_P(PSTR("Heat "), false); break;
            case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:  oled_write_P(PSTR("Reac "), false); break;
            default:                                oled_write_P(PSTR("RGB? "), false);
        }
    } else {
        switch (get_highest_layer(layer_state)) {
            case _BASE:   oled_write_P(PSTR(" Base"), false); break;
            case _LOWER:  oled_write_P(PSTR("Lower"), false); break;
            case _RAISE:  oled_write_P(PSTR("Raise"), false); break;
            case _ADJUST: oled_write_P(PSTR(" Conf"), false); break;
            case _MOUSE:  oled_write_P(PSTR("Mouse"), false); break;
            default:      oled_write_P(PSTR("  ?  "), false);
        }
    }
}

// Gata pet (master OLED): frame estatico 32x32 - sentada alerta con cabeza separada
// Cabeza arriba con sombra de cuello, cuerpo redondo abajo, cola enroscada
// (antes ten\xC3\xADa 2 frames con "respiraci\xC3\xB3n"; simplificado para liberar flash
// que ocupa el indicador del modo RGB en render_layer_state)
static const char PROGMEM gata_a[] = {
    0x00,0x00,0x00,0x00,0x00,0xE0,0xF8,0xFE,0xFC,0xF0,0xF0,0xF0,0xF0,0xF0,0xFC,0xFE,
    0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x0F,0x1F,0x3F,0x7F,0x79,0xDF,0xCF,0xCF,0xDF,0xFF,0x79,0x7F,
    0xBF,0xDF,0xCF,0xC0,0xC0,0x80,0x80,0x00,0x00,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xF0,0xF8,0xFC,0xFE,0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF9,0xF3,0xFF,0x7C,0x00,
    0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x7B,0x7F,0x7B,0x7F,0x7F,0x7F,
    0x7F,0x7F,0x7F,0x7F,0x7B,0x7F,0x7B,0x1F,0x1F,0x0F,0x07,0x03,0x03,0x05,0x00,0x00,
};

static void render_gata(void) {
    oled_set_cursor(0, 9);
    oled_write_raw_P(gata_a, 128);
}

static void render_mod_status(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 13);
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("CTL ") : PSTR("    "), false);
    oled_set_cursor(0, 14);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SFT ") : PSTR("    "), false);
}


// Luna pet: 5 frames 32x32 — sit / walk_a / walk_b / run_a / run_b
static const char PROGMEM luna_sit[] = {
    0x00,0x00,0x00,0x00,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFE,0x9E,0xFF,0xFF,0xFF,0xFF,0x9F,0xFE,
    0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x06,0x0F,0x1B,0x1A,0xFA,0xFB,0xFF,0xFE,
    0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xE0,0x00,0x00,0x83,0x7C,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x7F,0x7F,
    0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x1F,0x0F,0x07,0x04,0x02,0x01,0x00,0x00,
};
static const char PROGMEM luna_walk_a[] = {
    0x00,0x78,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0x78,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0x00,
    0x00,0xF0,0xFF,0xFF,0xCF,0xCF,0x7F,0xFF,0xFF,0xCF,0xCF,0xFF,0xFF,0xF8,0xF0,0xE0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0x80,0x40,0x70,0x1C,0x07,0x01,0x00,0x00,
    0x00,0x00,0x01,0x03,0x07,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x7F,
    0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0x3F,0xFF,0xEF,0xE6,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x7F,0x7F,0x7F,0x00,
    0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x00,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM luna_walk_b[] = {
    0x00,0x78,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0x78,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0x00,
    0x00,0xF0,0xFF,0xFF,0xCF,0xCF,0x7F,0xFF,0xFF,0xCF,0xCF,0xFF,0xFF,0xF8,0xF0,0xE0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0x80,0x40,0x70,0x1C,0x07,0x01,0x00,0x00,
    0x00,0x00,0x01,0x03,0x07,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x7F,
    0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0x3F,0xFF,0xEF,0xE6,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x00,0x07,0x07,0x07,0x00,
    0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x7F,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,
};
static const char PROGMEM luna_run_a[] = {
    0x00,0x00,0x00,0x80,0xE0,0xC0,0x00,0x00,0x00,0x00,0xC0,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xE0,0xF8,0xFC,0x9F,0x9F,0x7F,0xFF,0xFE,0x9E,0x9F,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0x60,0x70,0x30,0x18,0x10,
    0x00,0x03,0x07,0x07,0x0F,0x0F,0x8F,0xEF,0x7F,0x1F,0x1F,0x3F,0xFF,0xFF,0x3F,0x3F,
    0x3F,0x3F,0x3F,0x3F,0xBF,0xFF,0x7F,0x1F,0x1F,0x1F,0x7F,0xE7,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x08,0x0E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x0C,
    0x00,0x00,0x08,0x0E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0E,0x08,0x00,
};
static const char PROGMEM luna_run_b[] = {
    0x00,0x00,0x00,0x80,0xE0,0xC0,0x00,0x00,0x00,0x00,0xC0,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xE0,0xF8,0xFC,0x9F,0x9F,0x7F,0xFF,0xFE,0x9E,0x9F,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,
    0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0x60,0x70,0x30,0x18,0x10,
    0x00,0x03,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,
    0x3F,0x3F,0x3F,0x3F,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x03,0x03,0x03,0x00,
    0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,
};

static void render_luna(void) {
    static uint16_t luna_frame_timer = 0;
    static uint16_t luna_state_timer = 0;
    static uint8_t luna_flip = 0;
    static uint8_t luna_state = 0; // 0=sit, 1=walk, 2=run

    if (timer_elapsed(luna_state_timer) > 6000) {
        luna_state = (luna_state + 1) % 3;
        luna_state_timer = timer_read();
        luna_frame_timer = timer_read();
        luna_flip = 0;
    }

    const char *frame;
    uint16_t period;
    if (luna_state == 0) {
        frame = luna_sit;
        period = 0;
    } else if (luna_state == 1) {
        frame = luna_flip ? luna_walk_a : luna_walk_b;
        period = 400;
    } else {
        frame = luna_flip ? luna_run_a : luna_run_b;
        period = 200;
    }

    if (period > 0 && timer_elapsed(luna_frame_timer) > period) {
        luna_flip ^= 1;
        luna_frame_timer = timer_read();
    }

    oled_set_cursor(0, 12);
    oled_write_raw_P(frame, 128);
}

bool oled_task_user(void) {
    render_logo();
    if (is_keyboard_master()) {
        render_layer_state();
        render_gata();
        render_mod_status();
    } else {
        oled_set_cursor(0, 5);
        oled_write_P(PSTR("Eres "), false);
        oled_set_cursor(0, 7);
        oled_write_P(PSTR(" un  "), false);
        oled_set_cursor(0, 9);
        oled_write_P(PSTR("Crack"), false);
        render_luna();
    }
    return false;
}
#endif
