# Feature Weights — base de conocimiento de costo en flash

Catálogo de cuánto pesa cada feature en este firmware específico. Útil para decidir trade-offs cuando el AVR está cerca del límite (28KB).

## Metadatos del baseline

| Campo | Valor |
|---|---|
| Target QMK | `sofle/rev1` (ATmega32U4) |
| Flash usable | 28672 bytes (28KB - bootloader Caterina) |
| Versión QMK | 0.32.14 (master, 2026-05-17) |
| Compilador | avr-gcc 8.5.0 (Homebrew) |
| LTO | habilitado |
| Build actual | 28120 / 28672 bytes (98%, 552 libres) |

## Cómo leer esta tabla

- **🟢 Medido**: delta observado al togglear la feature en esta sesión, número confiable ±10%.
- **🟡 Estimado**: extrapolación a partir de mediciones parciales o documentación QMK, ±30%.
- **🔴 Doc-only**: sin medición propia, valor reportado en docs QMK o foros.

Los pesos **incluyen** interacciones con el resto del config actual. Cambiar el config puede mover los números.

## Features deshabilitables (high-level, en `rules.mk`)

| Feature | Estado actual | Peso | Confianza | Notas |
|---|---|---|---|---|
| `RGB_MATRIX_ENABLE` + driver ws2812 + 5 efectos | ON | **~3000 B** | 🟢 | Framework completo. Sin los efectos individuales, el costo base es ~2500 B. |
| `MOUSEKEY_ENABLE` | ON | ~700 B | 🟡 | Soporta `MS_*` keycodes. Capa `_MOUSE` lo requiere. |
| `OLED_ENABLE` + driver ssd1306 | ON | ~1850 B | 🟡 | Framework completo + driver. No incluye los `render_*` custom. |
| `WPM_ENABLE` | OFF | **~500 B** | 🟢 | Medido al quitarlo + simplificar `render_luna`. |
| `VIA_ENABLE` | OFF | ~2500 B | 🟡 | De la sesión anterior cuando se quitó. Incluye dynamic keymap. |
| `SPLIT_LAYER_STATE_ENABLE` | OFF | **~130 B** | 🟢 | Medido al quitarlo para meter STARLIGHT. |
| `SPLIT_TRANSPORT_MIRROR` | OFF | ~150 B | 🟡 | Quitado en la sesión inicial. |
| `SPLIT_OLED_ENABLE` | OFF | ~80 B | 🟡 | Para sincronizar contenido OLED entre mitades. |
| `SPLIT_MODS_ENABLE` | OFF | ~70 B | 🟡 | Para que slave conozca mods del master. |
| `SPLIT_LED_STATE_ENABLE` | OFF | ~50 B | 🟡 | Para sincronizar Caps Lock LED etc. |
| `ENCODER_MAP_ENABLE` | ON | ~180 B | 🟡 | Modo declarativo de encoders por capa. |
| `LTO_ENABLE` | ON | ahorra ~10-15% | 🟡 | Link-time optimization. NUNCA quitar. |

## Efectos RGB Matrix (incrementales sobre `RGB_MATRIX_ENABLE`)

Cada `ENABLE_RGB_MATRIX_*` agrega ~50-500 B según la complejidad del efecto. Costos medidos / estimados:

| Efecto | Peso aprox | Confianza | Notas |
|---|---|---|---|
| `TYPING_HEATMAP` | **~500 B** | 🟢 | El más pesado encontrado. Usa difusión térmica + paleta runtime + decay por LED. Quitarlo liberó ~500 B en esta sesión. |
| `SOLID_REACTIVE_MULTICROSS` | ~150 B | 🟡 | Activado actualmente (label `Cros`). |
| `SOLID_MULTISPLASH` | ~130 B | 🟡 | Activado actualmente (label `Wave`). |
| `MULTISPLASH` | **~88 B** | 🟢 | Medido al agregarlo. Activado actualmente (label `Rain`). Variante full-gradient de SOLID_MULTISPLASH. |
| `MY_WAVE` + `MY_RAIN` (custom, BG idle + drops) | **~406 B** | 🟢 | Medido al agregar ambos efectos custom en `rgb_matrix_user.inc`. Incluye 2 math funcs + 1 runner shared + 2 entries + 3 cases extra en OLED switch (SOLID_COLOR, iWav, iRai). |
| `STARLIGHT` | ~130 B | 🟢 | Medido vs BREATHING al hacer el swap. |
| `BREATHING` | ~50 B | 🟢 | Comparado con STARLIGHT en la sesión. |
| `CYCLE_LEFT_RIGHT` | ~50 B | 🟡 | Activado actualmente. |
| `SOLID_REACTIVE_SIMPLE` | ~50 B | 🟡 | Quitado al cambiar a MULTISPLASH/MULTICROSS. |
| `GRADIENT_LEFT_RIGHT` | ~25 B | 🟡 | Activado actualmente (default). |
| `RAINBOW_MOVING_CHEVRON` | ~150 B | 🔴 | Doc-only, no probado. |
| `CYCLE_UP_DOWN` | ~50 B | 🔴 | Doc-only. |
| `PIXEL_FLOW` | ~120 B | 🔴 | Doc-only. |
| `STARLIGHT_DUAL_HUE` | ~150 B | 🔴 | Variante de STARLIGHT. |

## OLED renderers custom (en `keymap.c`)

| Función | Peso | Notas |
|---|---|---|
| `render_logo` | ~150 B + 128 B PROGMEM | Logo GFG 32×32 + función. |
| `render_layer_state` actual | ~300 B + ~50 B strings | Switch 5 cases capa + switch 5 cases efecto RGB + lógica del timer del indicador. |
| `render_mod_status` (2 filas, mods con L/R) | ~120 B | Buffer 10 chars + 8 ifs + 1 write con autowrap. |
| `render_gata` (1 frame estático) | ~20 B + 128 B PROGMEM | Antes era ~150 B + 256 B PROGMEM (2 frames). |
| `render_luna` (ciclo sit/walk/run) | ~150 B + 640 B PROGMEM | 5 frames × 128 B + lógica con 2 timers. |
| Logo del slave + texto "Eres un Crack" | ~100 B + 128 B PROGMEM | Logo + 3 oled_write_P. |
| String `" by  SofleRGBv2     "` (master, 20 chars) | 21 B PROGMEM | Un solo oled_write_P, autowrap a 4 filas. |

## Indicadores efímeros (timers + lógica)

| Indicador | Peso | Notas |
|---|---|---|
| Indicador efecto RGB en fila 15 (2s al cambiar modo) | **~110 B** | 🟢 Medido. Compara `rgb_matrix_get_mode()` con `last_rgb_mode` static + timer. |

## Trucos descubiertos (para liberar bytes)

1. **Concatenar strings en un solo `oled_write_P`**: aprovechando que el cursor avanza automáticamente entre filas, escribir 4 strings con UN solo `oled_write_P(" by  SofleRGBv2rev2 ", false)` libera **~52 B** vs 4 llamadas separadas con `oled_set_cursor` cada una.

2. **Un solo buffer + un solo `oled_write` para múltiples filas**: el `render_mod_status` usa un buffer de 10 chars y un solo `oled_write`. El cursor hace autowrap entre fila 13 y 14. Sin esto, 2 buffers + 2 writes pesaban ~30 B más.

3. **Static vars con sentinel inicial**: en el indicador del efecto RGB, `last_rgb_mode = 0xFF` evita disparar el indicador al boot.

4. **PROGMEM no referenciado se descarta**: cuando simplificamos `render_luna` a walk loop sin usar `luna_sit`, `luna_run_a`, `luna_run_b`, el linker los descartó automáticamente (~384 B menos). Al volver a referenciarlos al hacer el ciclo, volvieron al binario.

5. **Mod-morph en `process_record_user`** es más liviano que `MT()`/`LT()` cuando la lógica es simple (ej. BSDL: tap=BSPC, shift+tap=DEL).

## Heurística rápida para decisiones de espacio

| Bytes libres | Qué puedes hacer |
|---|---|
| > 1000 | Agregar feature mediana (VIA está fuera, pero WPM + MULTISPLASH sí caben) |
| 500-1000 | Agregar efectos RGB extra, recuperar WPM_ENABLE |
| 100-500 | Agregar 1-2 efectos chicos, indicador OLED extra, mods reactivos |
| 50-100 | Solo cambios cosméticos (strings, layout) |
| 0-50 | Cada feature nueva requiere sacrificar algo |
| < 0 | Build falla, hay que reducir |

## Limitaciones de esta tabla

1. **Los pesos NO son aditivos**: features que comparten utilidades internas se "abaratan" entre sí. Quitar A solo te da el peso de A, pero quitar A+B juntas puede dar menos que sum(A) + sum(B).

2. **GCC LTO reorganiza**: el mismo código puede pesar distinto en builds distintos según qué más esté presente.

3. **Versión-dependiente**: cambios en QMK upstream pueden hacer las cifras obsoletas. Re-medir cada major version bump.

4. **RAM y EEPROM no contadas**: solo flash. Hay límites separados de SRAM (2.5KB) y EEPROM (1KB) que esta tabla no cubre.

## Cómo medir tu propio delta

Sin script (manual):

```bash
# 1. Compila con la feature actual:
qmk compile -kb sofle/rev1 -km gonzafg2 2>&1 | grep "approaching"
#    Output: 28120/28672 (98%, 552 bytes free)

# 2. Toggle la feature en rules.mk o config.h

# 3. Recompila y compara:
qmk compile -kb sofle/rev1 -km gonzafg2 2>&1 | grep "approaching"

# 4. delta = nuevo - viejo
```

Con script (futuro, ver propuesta de `scripts/measure-feature.sh` en discusión).

## Cuando actualizar esta tabla

- Al togglear cualquier feature de las listadas → anotar el delta real medido
- Al activar/desactivar efectos RGB → anotar costo individual
- Al hacer upgrade de QMK upstream → re-medir las features críticas (`RGB_MATRIX_ENABLE`, `OLED_ENABLE`, `VIA_ENABLE`)
- Al cambiar avr-gcc (improbable, pero si pasa)
