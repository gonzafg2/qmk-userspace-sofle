// Efectos RGB Matrix custom: combinan fondo idle tenue + drops reactivos.
//
// Basados en multisplash_anim.h / solid_splash_anim.h del core QMK,
// pero en lugar de iniciar cada LED con value=0 (apagado), arrancan en
// BG_VALUE (brillo tenue). Los drops se suman encima con qadd8 saturado.
//
// El brillo del BG queda modulado por el VAL global (RM_VALU/RM_VALD),
// asi que si el usuario baja el brillo general el BG tambien baja.

RGB_MATRIX_EFFECT(MY_WAVE)
RGB_MATRIX_EFFECT(MY_RAIN)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// El BG idle "late" tipo corazón: patrón lub-dub-pausa con lookup table
// piecewise. Más visceral que un sinusoidal puro.
//
// Estructura del latido (32 frames, ~32ms cada uno = ciclo ~1s = ~60 BPM):
//   Frames 0-7  : Lub (sistole), pulso rapido alto. Pico ~88 (~35%).
//   Frames 8-11 : Pausa corta a reposo.
//   Frames 12-19: Dub (diastole), pulso secundario menor. Pico ~70.
//   Frames 20-31: Pausa larga (~400ms de quietud antes del proximo latido).
//
// Pico del Lub a 88 (vs 70 del sinusoidal anterior) = ~10% mas brillo
// absoluto, mas notorio.
//
// Optimizaciones AVR:
// - PROGMEM: tabla en flash, no RAM (32 bytes).
// - (uint8_t)(g_rgb_timer >> 5) & 0x1F: shift /32 ms + cast a uint8_t
//   + AND mod 32 = indice 0-31 sin division 32-bit.
// - Macro inline en el runner: evita RCALL/RET.
static const uint8_t PROGMEM heartbeat_lut[32] = {
    // Lub (0-7): sube rapido al pico, baja
    25, 50, 75, 88, 88, 70, 50, 30,
    // Pausa corta (8-11)
    20, 18, 18, 20,
    // Dub (12-19): pico menor que el Lub
    35, 55, 70, 70, 65, 50, 35, 25,
    // Pausa larga (20-31): casi flat en valle
    20, 18, 16, 15, 15, 15, 15, 15,
    15, 15, 15, 16,
};
#    define BG_PULSE() pgm_read_byte(&heartbeat_lut[(uint8_t)(g_rgb_timer >> 5) & 0x1F])

// Math para un solo color (igual que SOLID_SPLASH_math)
static hsv_t my_wave_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

// Math para arcoiris (igual que SPLASH_math)
static hsv_t my_rain_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.h += effect;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

// Runner generico: identico a effect_runner_reactive_splash del core
// pero hsv.v inicial = BG_VALUE en vez de 0. Eso da el fondo tenue.
static bool my_reactive_bg_runner(effect_params_t* params, reactive_splash_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        hsv_t hsv = rgb_matrix_config.hsv;
        hsv.v     = BG_PULSE(); // BG idle respira en lugar de ser fijo
        for (uint8_t j = 0; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        hsv.v     = scale8(hsv.v, rgb_matrix_config.hsv.v);
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

bool MY_WAVE(effect_params_t* params) {
    return my_reactive_bg_runner(params, &my_wave_math);
}

bool MY_RAIN(effect_params_t* params) {
    return my_reactive_bg_runner(params, &my_rain_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
