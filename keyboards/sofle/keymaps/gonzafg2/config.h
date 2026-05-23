#pragma once

#define MASTER_LEFT


#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 128

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// === RGB Matrix ===
// Pin (D3), led_count (72), split_count [36,36], layout y driver ws2812
// ya estan definidos en keyboards/sofle/info.json (mainline).
// Aqui solo defines esteticos y set acotado de efectos para AVR.
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_DEFAULT_VAL 100
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_STARLIGHT
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// Removidos por espacio para meter el BG pulsando:
// - CYCLE_LEFT_RIGHT: ambiental, sustituible por la pulsacion del BG idle.
// - MULTISPLASH: MY_RAIN custom (iRai) lo reemplaza con BG idle pulsando.
// SOLID_MULTISPLASH (Wave) se mantiene: LTO comparte codigo con MY_WAVE custom;
// quitarlo paradojicamente sube el tamano por dependencias internas del runner.

// Efectos custom propios en rgb_matrix_user.inc (BG tenue + drops reactivos)
#define RGB_MATRIX_CUSTOM_USER

