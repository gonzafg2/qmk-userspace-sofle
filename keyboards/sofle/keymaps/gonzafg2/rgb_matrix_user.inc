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

#    define BG_VALUE 50 // 50/255 = ~20% de brillo idle. Subir/bajar a gusto.

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
        hsv.v     = BG_VALUE; // <-- esto es lo unico distinto del runner del core
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
