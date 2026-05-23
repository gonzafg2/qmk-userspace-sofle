# Feature Weights — base de conocimiento de costo en flash

Catálogo de cuánto pesa cada feature en este firmware específico. Útil para decidir trade-offs cuando el AVR está cerca del límite (28KB).

## Metadatos del baseline

| Campo | Valor |
|---|---|
| Target QMK | `sofle/rev1` (ATmega32U4) |
| Flash usable | 28672 bytes (28KB - bootloader Caterina) |
| Versión QMK | 0.32.14 (master, 2026-05-17) |
| Compilador | avr-gcc 8.5.0 (Homebrew, keg-only en `/opt/homebrew/opt/avr-gcc@8/bin`) |
| LTO | habilitado |
| Build actual | **28170 / 28672 bytes (98%, 502 libres)** — tras sesión 3 del 2026-05-23 (`SPLIT_LAYER_STATE_ENABLE` reactivado a costo 0 B) |
| Sesión 2 (mismo día) | 28170 / 28672 bytes (98%, 502 libres) — keymap reorg Tech Lead + MK_KINETIC_SPEED mouse + diagramas `[KEY]` |
| Sesión 1 (mismo día) | 28020 / 28672 bytes (97%, 652 libres) — NKRO + DEBOUNCE 8, quitando STARLIGHT + MULTICROSS |
| Build previo (pre-2026-05-23) | 28498 / 28672 bytes (99%, 174 libres) — con STARLIGHT + MULTICROSS, sin NKRO |

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
| `SPLIT_LAYER_STATE_ENABLE` | ON | **0 B (en este contexto)** | 🟢 | Reactivado 2026-05-23 sesión 3. Medición previa decía ~130 B (al quitarlo para meter STARLIGHT), pero al reactivarlo ahora costó **0 B** — LTO comparte código con algo ya presente en el build actual. Habilita futuro mostrar capa en OLED slave o RGB indicators per-layer en la mitad derecha. |
| `CHORDAL_HOLD` | OFF | **~1236 B** | 🟢 | Medido 2026-05-23 sesión 3: al activarlo (con array `chordal_hold_layout` PROGMEM en keymap.c), el binario subió de 28170 a 29406 (734 B over). **3-4× más pesado que la docs típica** (~340 B), probablemente por interacción con `HOLD_ON_OTHER_KEY_PRESS` + `PERMISSIVE_HOLD` activos + tamaño de matriz Sofle. **Descartado**: en este keymap solo aplica a `GFG_ESCAD` (único LT), el ROI no justifica sacrificar 1.2 KB de otras features. Si en el futuro se agregan home-row mods o más LT, re-evaluar. |
| `SPLIT_TRANSPORT_MIRROR` | OFF | ~150 B | 🟡 | Quitado en la sesión inicial. |
| `SPLIT_OLED_ENABLE` | OFF | ~80 B | 🟡 | Para sincronizar contenido OLED entre mitades. |
| `SPLIT_MODS_ENABLE` | OFF | ~70 B | 🟡 | Para que slave conozca mods del master. |
| `SPLIT_LED_STATE_ENABLE` | OFF | ~50 B | 🟡 | Para sincronizar Caps Lock LED etc. |
| `ENCODER_MAP_ENABLE` | ON | ~180 B | 🟡 | Modo declarativo de encoders por capa. |
| `LTO_ENABLE` | ON | ahorra ~10-15% | 🟡 | Link-time optimization. NUNCA quitar. |
| `NKRO_ENABLE` | ON | **368 B** | 🟢 | Medido 2026-05-23: 27652 → 28020 al activarlo. Cambia HID report a bitmap (~32 B/reporte) en vez de array 6KRO (8 B). Soluciona race condition de eventos solapados en split que rompía dead keys de macOS LATAM. |

## Efectos RGB Matrix (incrementales sobre `RGB_MATRIX_ENABLE`)

Cada `ENABLE_RGB_MATRIX_*` agrega ~50-500 B según la complejidad del efecto. Costos medidos / estimados:

| Efecto | Peso aprox | Confianza | Notas |
|---|---|---|---|
| `TYPING_HEATMAP` | **~500 B** | 🟢 | El más pesado encontrado. Usa difusión térmica + paleta runtime + decay por LED. Quitarlo liberó ~500 B en esta sesión. |
| `SOLID_REACTIVE_MULTICROSS` | ~150 B individual / **~458 B combinado** | 🟢 | **Quitado** 2026-05-23 junto con STARLIGHT para meter NKRO. La medición combinada (846 B liberados al quitar ambos + 2 cases OLED) demuestra que LTO produce dividendos no-lineales cuando se quitan varios efectos juntos. |
| `SOLID_MULTISPLASH` | ~130 B | 🟡 | **Activado** actualmente (label `Wave`). Quitarlo paradojicamente sube el binario por dependencias LTO compartidas con el runner de MY_WAVE custom. |
| `MULTISPLASH` | **~88 B** | 🟢 | Medido al agregarlo, luego **quitado**: MY_RAIN (iRai) lo reemplaza con BG idle pulsando. |
| `MY_WAVE` + `MY_RAIN` (custom, BG idle + drops) | **~406 B** | 🟢 | **Activados** actualmente (labels `iWav`, `iRai`). 2 math funcs + 1 runner shared + 2 entries en `rgb_matrix_user.inc` + cases en OLED switch. |
| Heartbeat LUT del BG (lub-dub-pausa, 32 frames PROGMEM) | **~84 B** | 🟢 | **Activo** dentro de MY_WAVE/MY_RAIN. Tabla 32 B + `pgm_read_byte(&lut[(uint8_t)(g_rgb_timer >> 5) & 0x1F])`. Sorprendentemente más liviano que el sinusoidal previo (-50 B): pgm_read_byte es más directo que sin8 + scale8 + suma. |
| Breathing sinusoidal del BG (sin8 + scale8) | **~134 B** | 🟢 | Medición intermedia, **reemplazado** por heartbeat LUT por ser más liviano. |
| `CYCLE_LEFT_RIGHT` | **~134 B** | 🟢 | **Quitado**: ambiental sustituible por el propio pulso del BG idle. Liberó espacio crítico para el breathing del BG. |
| `TYPING_HEATMAP` | **~500 B** | 🟢 | **Quitado**: el más pesado del set inicial, liberado al cambiar a MULTISPLASH/MULTICROSS. |
| `SOLID_REACTIVE_SIMPLE` | ~50 B | 🟡 | **Quitado** al cambiar a MULTISPLASH/MULTICROSS. |
| `STARLIGHT` | ~130 B individual / **~388 B combinado** | 🟢 | **Quitado** 2026-05-23 junto con MULTICROSS para meter NKRO. Ver nota de medición combinada en MULTICROSS. |
| `BREATHING` | ~50 B | 🟢 | Medido cuando estaba activado al inicio del PR; ahora **no está**. |
| `GRADIENT_LEFT_RIGHT` | ~25 B | 🟡 | **Activado** actualmente (default al boot, label `Grad`). |
| `SOLID_COLOR` | 0 B (always-on) | 🟢 | Always-on de QMK, no requiere ENABLE_*. Aparece en el ciclo como `RGB?` en el OLED. |
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

---

## Componentes del firmware — descripción y peso

Esta sección describe **qué hace cada componente activo**, su rol en el día a día del teclado, y su costo en flash en el build actual (2026-05-23 sesión 3, `28170 / 28672 B`).

### Núcleo QMK (no removible)

| Componente | Peso aprox | Descripción |
|---|---|---|
| Bootloader Caterina | (fuera del flash usable, 4 KB) | Permite entrar a modo flash con doble-tap del botón reset en el Pro Micro. No se toca desde el firmware. |
| TMK/QMK core + LUFA USB stack | ~10 KB | Maquinaria base: matriz de teclas → keycodes → reportes HID → USB. |
| Matrix scan + debounce | (incluido en core) | Lee la matriz GPIO cada ~1 ms. `DEBOUNCE 8` significa que un cambio debe mantenerse estable 8 ms antes de registrarse. |

### Comunicación USB / HID

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| `NKRO_ENABLE` + `FORCE_NKRO` | ON | **368 B** 🟢 | Cambia el formato HID de **6KRO** (8 bytes con array de 6 slots compartidos) a **NKRO** (bitmap de ~32 bytes con un bit por tecla, hasta ~240 teclas simultáneas). En este Sofle resuelve el síntoma de "presiono ´+vocal rápido y no sale la tilde". **Aclaración técnica**: los reportes HID en ambos modos son snapshots de estado (no eventos ordenados); el beneficio de NKRO viene de eliminar la ambigüedad de slots — en 6KRO los 6 slots se llenan en orden no estrictamente definido por la spec, lo que combinado con eventos solapados de un split (eventos del slave que llegan al master vía TRRS y se reportan en la misma ventana de polling USB que las teclas del master) puede generar reportes que macOS interpreta en un orden distinto al físico, rompiendo la dead key del layout LATAM. Empíricamente activar NKRO resolvió el bug; la causa exacta probablemente involucra también diferencias de timing/batching de reportes entre los dos modos en QMK. `FORCE_NKRO` asegura que arranque siempre en NKRO sin necesidad de hotkey. |
| `EXTRAKEY_ENABLE` | ON | (no medido individual) | Habilita teclas de sistema y consumer (volumen, media play/pause, brillo). Sin esto, encoder push de Mute/Play no funciona. |

### Iluminación RGB

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| `RGB_MATRIX_ENABLE` + driver ws2812 | ON | ~3000 B | Framework completo de RGB Matrix para 72 LEDs SK6812 MINI (36 por mitad). Permite efectos animados, brillo, color, modo reactivo a teclas. |
| `RGB_MATRIX_GRADIENT_LEFT_RIGHT` (label `Grad`) | ON | ~25 B | Default al boot. Gradiente horizontal estático. Bajo costo, ambiental. |
| `RGB_MATRIX_SOLID_MULTISPLASH` (label `Wave`) | ON | ~130 B | Splashes reactivos a teclas presionadas. **Mantenido pese a poder quitarlo**: comparte código LTO con el runner de `MY_WAVE` custom; quitarlo paradójicamente sube el binario. |
| `MY_WAVE` custom (label `iWav`) | ON | ~200 B (parte del bundle de 406 B) | Efecto propio: fondo idle con respiración tipo heartbeat (lub-dub-pausa) + drops reactivos al teclear. |
| `MY_RAIN` custom (label `iRai`) | ON | ~200 B (parte del bundle) | Variante de `MY_WAVE` con paleta tipo lluvia. Comparte runner con MY_WAVE. |
| Heartbeat LUT (32 frames PROGMEM) | ON | **84 B** 🟢 | Tabla precalculada del pulso BG, leída con `pgm_read_byte`. Más liviano que `sin8 + scale8` calculado en runtime. |

### OLED dual

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| `OLED_ENABLE` + driver ssd1306 | ON | ~1850 B | Framework para los 2 OLEDs SSD1306 (uno por mitad). |
| `render_logo` (master, GFG 32×32) | ON | ~150 B + 128 B PROGMEM | Logo arriba en el OLED master. |
| `render_layer_state` (master, capa + modo RGB) | ON | ~300 B + ~50 B strings | Muestra nombre de capa activa (Base/Lower/Raise/Adjust/Mouse) y código de efecto RGB cuando se cambia (indicador efímero 2s). |
| `render_mod_status` (master, mods L/R) | ON | ~120 B | Indica qué mods (Shift/Ctrl/Alt/GUI) están activos, por lado. |
| Logo slave + texto "Eres un Crack" | ON | ~100 B + 128 B PROGMEM | OLED de la mitad derecha. |
| `render_luna` (slave, pet animado walk loop) | ON | ~150 B + 640 B PROGMEM | Mascota Luna corriendo en loop fijo en el OLED slave. |

### Encoders

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| `ENCODER_ENABLE` + `ENCODER_MAP_ENABLE` | ON | ~180 B | Permite definir qué hace cada encoder por capa de forma declarativa (`encoder_map[]`). En Base: izq = volumen, der = scroll. En Lower/Raise: navegación de palabras/desktops/brillo. |

### Procesamiento de teclas

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| `MOUSEKEY_ENABLE` | ON | ~700 B | Permite usar el teclado como ratón (capa `_MOUSE`). Movimiento, click, scroll, todo desde teclas. |
| `CAPS_WORD_ENABLE` | ON | ~250 B | Doble-tap LShift activa CAPS WORD: solo la próxima palabra va en mayúsculas. Termina al espacio o tras 5 s sin teclear. |
| Mod-morph `GFG_BSDL` (BS / Shift+BS = Del) | ON | ~30 B | Hecho a mano en `process_record_user`, más liviano que un keycode `MT()` o `tap_dance`. |
| Custom keycodes `GFG_*` (operadores, macros macOS) | ON | ~400 B aprox | ~15 keycodes con `SEND_STRING(...)`: `=>`, `&&`, `||`, `==`, `!==`, `===`, `+=`, `-=`, screenshots, lock, force quit. |
| `LT()` / `MT()` hold-tap | ON | (incluido en core) | LWR/RSE thumb keys con hold = capa, tap = enter/space. `TAPPING_TERM 200`, `QUICK_TAP_TERM 150`, `PERMISSIVE_HOLD`, `HOLD_ON_OTHER_KEY_PRESS`. |
| `TAP_DANCE_ENABLE` | OFF | (libera ~400 B si OFF) | No se usa. |
| `COMBO_ENABLE` | OFF | (libera ~500 B si OFF) | No se usa (los combos quedaron descartados después de la sesión inicial). |
| `VIA_ENABLE` | OFF | (libera ~2500 B) | No se usa, demasiado pesado para AVR + RGB Matrix. |
| `WPM_ENABLE` | OFF | (libera ~500 B) | Se quitó para liberar espacio. Luna ya no muestra WPM. |

### Split (comunicación master ↔ slave)

| Componente | Estado | Peso | Descripción |
|---|---|---|---|
| Transport serial (default) | ON | (incluido en core) | Comunicación serial 1-wire entre las dos mitades por el cable TRRS. |
| `SPLIT_LAYER_STATE_ENABLE` | ON (desde 2026-05-23 sesión 3) | **0 B en este contexto** | Sincroniza el `layer_state` del master al slave por TRRS para que el slave sepa qué capa está activa. Reactivado en sesión 3 sin costo flash (LTO comparte código con otras features split presentes). Hoy no se usa visualmente, pero abre futuro: mostrar capa en OLED slave o pintar LEDs slave por capa. |
| `SPLIT_TRANSPORT_MIRROR` | OFF | ~150 B | Quitado en sesión inicial. |
| `SPLIT_OLED_ENABLE` | OFF | ~80 B | Quitado: cada OLED renderiza independientemente. |
| `SPLIT_MODS_ENABLE` | OFF | ~70 B | Quitado: slave no necesita conocer mods. |
| `SPLIT_LED_STATE_ENABLE` | OFF | ~50 B | Quitado: no hay Caps Lock LED físico. |

### Configuración (defines en `config.h`, peso ~0)

| Define | Valor | Descripción |
|---|---|---|
| `TAPPING_TERM` | 200 ms | Tiempo máximo que una hold-tap (`LT`, `MT`) considera "tap". Más allá es "hold". |
| `QUICK_TAP_TERM` | 150 ms | Si pulsas la misma hold-tap dos veces dentro de este tiempo, la 2da se interpreta como tap normal (no como hold). Útil para escribir "ll" o repetir letras rápido sin disparar capa. |
| `PERMISSIVE_HOLD` | (flag) | Cualquier otra tecla apretada-y-soltada **dentro** de una hold-tap dispara el hold inmediatamente. Mejora la sensación de capas rápidas. |
| `HOLD_ON_OTHER_KEY_PRESS` | (flag) | Más agresivo: ni siquiera espera que se suelte la otra tecla. Junto con PERMISSIVE_HOLD da capas casi instantáneas. |
| `DEBOUNCE` | 8 ms | Tiempo de estabilidad para confirmar un cambio de switch. Default QMK = 5 ms; subido a 8 ms el 2026-05-23 para margen anti-chatter sin latencia perceptible. |
| `FORCE_NKRO` | (flag) | Arranca siempre en NKRO. Sin esto, NKRO_ENABLE = yes hace que arranque en 6KRO y requiere keycode `NK_TOGG` para cambiar. |
| `COMBO_TERM` | 50 ms | (Ya no aplica porque COMBO_ENABLE = no, pero se mantiene el define por si se reactiva.) |
| `CAPS_WORD_IDLE_TIMEOUT` | 5000 ms | CAPS WORD se desactiva sola tras 5 s sin teclear. |
| `USB_SUSPEND_WAKEUP_DELAY` | 0 ms | Sin delay al despertar de suspensión USB. Útil tras dormir el Mac. |
| `OLED_TIMEOUT` | 60000 ms | OLEDs se apagan tras 1 min sin actividad. Quemado-de-pantalla preventivo. |
| `OLED_BRIGHTNESS` | 128 | Brillo medio de los OLEDs (0-255). |
| `DYNAMIC_KEYMAP_LAYER_COUNT` | 5 | Sobrescribe el default QMK (4) porque tenemos 5 capas. |
| `DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD` | (flag) | Doble-tap LShift activa CAPS WORD (en vez del default Caps Lock). |
| `RGB_MATRIX_MAXIMUM_BRIGHTNESS` | 150 | Tope de brillo RGB. Limita consumo USB (5V × ~1 A si todos los 72 LEDs estuvieran en blanco al 100%). |
| `RGB_MATRIX_DEFAULT_VAL` | 100 | Brillo al boot. |
| `RGB_MATRIX_DEFAULT_MODE` | `GRADIENT_LEFT_RIGHT` | Efecto al boot. |
| `MASTER_LEFT` | (flag) | La mitad izquierda es el master (la que se conecta al USB). |

### Resumen del balance actual

```
Total flash:        28672 bytes
Usado:              28170 bytes (98.3%)
Libre:                502 bytes (1.7%)

Mayor consumidor:   RGB_MATRIX_ENABLE (~3000 B = 10.5% del flash)
2do consumidor:     OLED_ENABLE + renderers custom (~2200 B = 7.7%)
3ro consumidor:     MOUSEKEY_ENABLE (~700 B = 2.4%)
Sesión 2026-05-23:  NKRO_ENABLE (368 B = 1.3%) + MK_KINETIC_SPEED (~150 B)
                    + SPLIT_LAYER_STATE_ENABLE (0 B, LTO compartido)
```

Con 502 B libres puedes:
- Agregar 1 efecto RGB chico tipo `BREATHING` (~50 B)
- `RAINBOW_MOVING_CHEVRON` (~150 B) ajustado pero entra
- 1-2 indicadores OLED extra

No caben (sin sacrificar algo):
- `CHORDAL_HOLD` (~1236 B medido en sesión 3, mucho más que docs típica de QMK)
- `UNICODE_ENABLE` (~500-1000 B + conflicto con LATAM Input Source en macOS)
- `WPM_ENABLE` + `STARLIGHT` juntos (~630 B)
- `VIA_ENABLE` (~2500 B)

No puedes:
- Reactivar `WPM_ENABLE` + `STARLIGHT` + `MULTICROSS` juntos (sumarían >800 B)
- Habilitar `VIA_ENABLE` (~2500 B, no cabe)
- Habilitar `TAP_DANCE_ENABLE` (~400 B, cabe pero deja muy poco margen)
