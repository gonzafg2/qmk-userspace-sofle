# Session context — origen y estado del repo

## Punto de partida

El usuario (gonzafg2) tenía un Corne v3 split funcionando con ZMK ([zmk-config-corne](https://github.com/gonzafg2/zmk-config-corne)) y quería replicar el flujo en su nuevo Sofle RGB de [ZoneKeyboards Chile](https://zonekeyboards.cl/keyboards/sofle-rgb-zk). El Corne es BLE wireless (nice!nano); el Sofle es **cableado USB-C** (Pro Micro), entonces firmware distinto: **QMK** en vez de ZMK.

## Decisión de arquitectura

**Estructura QMK Userspace** (estándar oficial QMK, equivalente a `gh.com/qmk/qmk_userspace`):
- Keymap mantenido fuera del fork de `qmk_firmware`
- Build automatizado por GitHub Actions (`qmk/.github/.github/workflows/qmk_userspace_*`)
- Cada push a `main` regenera el `.hex` y lo publica como release `latest`

Misma filosofía que el repo del Corne (config separado del firmware, CI build), pero adaptado al stack QMK.

## Sesión inicial — pasos ejecutados

1. **Identificación hardware via fotos**: Sofle RGB by Dane Evans (serigrafía "Power by Sofle RGB, Dane Evans" en el PCB), Pro Micro clon USB-C ATmega32U4 5V, switches MX (Gateron Blue confirmado), mix de LEDs backlight blanco + RGB SK6812, 2 encoders EC11 con push, 2 OLEDs SSD1306.
2. **Estructura del repo creada**: `qmk.json`, `users/gonzafg2/`, `keyboards/sofle/keymaps/gonzafg2/`, `.github/workflows/build_binaries.yml`.
3. **Keymap diseñado**: 5 capas (Base, Lower, Raise, Adjust, Mouse), encoder map por capa, OLED dual con logo + capa + WPM, combos (F+J caps_word, TAB+BSDL adjust), macros macOS (screenshots, lock, force quit), operadores prog (`=>`, `&&`, `||`, `==`, `!==`, `===`, `+=`, `-=`).
4. **Build verde en CI**: 4 iteraciones para resolver:
   - `ENCODER_RESOLUTION` redefinido (ya viene en `keyboard.json`)
   - `KC_MS_*`/`KC_WH_*`/`KC_BTN*` renombrados a `MS_*`/`MS_WHL*`/`MS_BTN*` en QMK actual
   - `DYNAMIC_KEYMAP_LAYER_COUNT` por defecto = 4, subido a 5
   - Firmware 452B sobre el límite de ATmega32U4 (28KB) → quitamos `SPLIT_TRANSPORT_MIRROR`, `SPLIT_OLED_ENABLE`, `SPLIT_MODS_ENABLE`, `SPLIT_LED_STATE_ENABLE`
5. **README reescrito** con diagramas Corne-style (box-drawing Unicode) + tablas auxiliares (tap-hold, encoders por capa, combos, macros).

## Estado actual

- ✅ Repo creado y pushed: https://github.com/gonzafg2/qmk-userspace-sofle
- ✅ CI verde — release `latest` con `sofle_rev1_gonzafg2.hex` listo para flashear
- ✅ README documentado y con diagramas limpios
- ⏳ Discusión abierta sobre thumb cluster — ver [thumb-cluster-iteration.md](./thumb-cluster-iteration.md)
- ❌ RGB underglow deshabilitado (decisión documentada en [decisions-log.md](./decisions-log.md))
- ❌ Sin probar físicamente — el usuario aún no flasheó

## Trade-offs aceptados

| Decisión | Por qué | Reversible |
|---|---|---|
| RGB underglow OFF | sofle/rev1 mainline no trae config RGB out-of-box; agregarlo requiere override del keyboard con `WS2812_DI_PIN` y `RGBLED_NUM` | Sí, agregando defines |
| SPLIT_* features quitadas | Firmware excedía 28KB de ATmega32U4 | Sí, si liberamos espacio |
| VIA con custom keycodes hex | VIA mainline no conoce los `GFG_*` | Sí, generando vial.json |

## Convenciones de pulgar (importante para próximas iteraciones)

- Thumb más interno y alto (col 5 izq / col 1 der) = **posición de reposo** del pulgar — ahí va lo más usado
- Actualmente: `SFT/MOUS` (izq) y `SPC` (der)
- Thumbs 1-4 izq y 2-5 der = **alcanzables con desviación** del pulgar
- Físicamente confirmado por `keyboards/sofle/rev1/keyboard.json` que tiene `h: 1.5` en esas posiciones

## Para retomar en futuras sesiones

Lee primero:
1. Este archivo (contexto general)
2. [thumb-cluster-iteration.md](./thumb-cluster-iteration.md) — debate abierto sin resolver
3. [decisions-log.md](./decisions-log.md) — qué se decidió y por qué
4. [hardware-notes.md](./hardware-notes.md) — observaciones del PCB
5. El `README.md` raíz — para ver el keymap actual documentado
6. `keyboards/sofle/keymaps/gonzafg2/keymap.c` — código fuente del keymap
