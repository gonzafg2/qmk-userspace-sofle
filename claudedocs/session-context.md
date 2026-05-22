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
- ✅ **Flasheado al menos una vez** (sesión 2026-05-21, OLED master verificado en fotos)
- ✅ Símbolos LATAM correctos en LOWER + RAISE
- ✅ OLED master rediseñado: logo GFG real + WPM + capa abajo
- ✅ OLED slave: "Eres / un / Crack" + Luna pet animado
- ✅ Encoder push Base: Mute izq, Play der
- ⏳ Discusión abierta sobre thumb cluster — ver [thumb-cluster-iteration.md](./thumb-cluster-iteration.md)
- ⏳ Luna pet sin verificar físicamente — riesgo de que la posición o estética falle
- ✅ **RGB Matrix activo** desde 2026-05-22 (72 LEDs SK6812 MINI, 5 efectos, control en `_ADJUST`)
- ❌ WPM deshabilitado (sacrificado en 2026-05-22 para que RGB_MATRIX entrara en AVR; Luna animada pero no reactiva al tecleo)
- ❌ VIA deshabilitado (intercambiado por espacio para Luna pet)

## Sesión 2026-05-21 — qué se hizo

1. **Fix símbolos LATAM Mac en LOWER right side** (`keymap.c:38-45`): porté el mismo enfoque de keycodes posicionales que usa `zmk-config-corne` (línea 147-149). 17 keycodes mapeados, ver tabla en [decisions-log.md](./decisions-log.md).
2. **Fix RAISE** (`keymap.c:61-62`): 3 keycodes (`KC_AT`, `KC_CIRC`, `KC_AMPR`) que asumían US.
3. **OLED master reorganizado** (`keymap.c:152-174`): logo + by/Sofle + WPM + mods + capa abajo. Capa renombrada en OLED: Lwr→Lower, Rse→Raise, Adj→Conf.
4. **OLED slave reescrito** (`keymap.c:184-198`): "Eres / un / Crack" arriba + Luna pet 32×32 animado abajo.
5. **Logo cambiado** (`keymap.c:138-148`): de mark abstracto a "GFG" iniciales reales (Helvetica Neue Condensed Black 20px).
6. **WPM_ENABLE = yes** + **VIA_ENABLE = no** (trade-off explicado en decisions-log).
7. **Encoder push Base** (`keymap.c:22`, `gonzafg2.h:34`): `GFG_MUTM` Play→Mute, slot der `GFG_LOCK`→`KC_MPLY`. LOCK sigue accesible en Adjust.

Firmware final: **26044/28672 bytes (90%, 2628 libres)**.

## Sesión 2026-05-22 — qué se hizo

1. **Identificación correcta del PCB**: el usuario confirmó nombre comercial **Sofle RGB V2 Rev2.1** — Josef Adamcik v2.1 con mod RGB de Dane Evans. Coincide con `keyboards/sofle/rev1` mainline.
2. **Corrección de decisión obsoleta**: la nota del 2026-05-18 sobre "RGB no compila out-of-box" estaba equivocada. Mainline `keyboards/sofle/info.json` ya define todo lo necesario (`ws2812.pin=D3`, 72 LEDs, split [36,36], driver, layout). Sin necesidad de overrides.
3. **RGB_MATRIX activado** (`rules.mk` + `config.h` + `keymap.c`): brillo máx 150, modo default gradient L→R. Keycodes `RM_*` (no `RGB_*`) en `_ADJUST` mano izquierda.
4. **Sacrificios para caber en AVR**:
   - `WPM_ENABLE = yes → no` (liberó ~500 B)
   - `SPLIT_LAYER_STATE_ENABLE` removido (~130 B; sin impacto visible)
5. **Iteraciones de Luna**: primero a walk loop fijo (post-WPM), después **Luna ciclando** entre sit→walk→run cada 6s (los 5 sprites originales mantenidos, frijol-y-nieblita stay).
6. **Set final de 5 efectos RGB**: `GRADIENT_LEFT_RIGHT` (default), `STARLIGHT` (ambiental "estrellas"), `CYCLE_LEFT_RIGHT`, `TYPING_HEATMAP` (reactivo), `SOLID_REACTIVE_SIMPLE` (reactivo).
7. **Verificado físicamente**: gradient rojo→violeta enciende al boot. **Titileo en brillo alto confirmó undervolt** — no subir `RGB_MATRIX_MAXIMUM_BRIGHTNESS` arriba de 150 sin cambiar fuente USB.
8. **Firmware tras activar RGB_MATRIX**: ~99% del AVR (cerca del límite, varias decenas de bytes libres). Estable pero apretado.

### Iteraciones post-PR (OLED enriquecido)

Después del primer build de RGB_MATRIX, varias features adicionales sumaron al PR:

- **Indicador efímero del efecto RGB** en fila 15 del master OLED (2s al cambiar `RM_NEXT`/`RM_PREV`/`RM_TOGG`)
- **Gata del master estática** (sin respiración) para hacer espacio para el indicador anterior
- **`RGBv2` + `rev2`** agregados al master OLED (filas 7-8) — identificación del PCB
- **Mods en 2 filas** (13-14) con codificación posicional fija que distingue LCTL/RCTL/LSFT/RSFT/LGUI/RGUI
- **Capa alineada a la izquierda** (`Base `, `Lower`, `Raise`, `Conf.`, `Mouse`)
- **Truco recurrente para caber**: un solo buffer + un solo `oled_write*` aprovechando autowrap del cursor del OLED, en vez de múltiples `set_cursor` + `write_P` separados.

**Tamaño final del PR**: ~99% (10 bytes libres en el último compile). Para nuevas features se requiere sacrificar algo existente.

## Trade-offs aceptados

| Decisión | Por qué | Reversible |
|---|---|---|
| RGB_MATRIX activo (vs RGBLIGHT) | El usuario lo pidió. Efectos reactivos al tecleo (heatmap, solid reactive) | Sí, cambiando a `RGBLIGHT_ENABLE = yes` (más liviano) |
| Brillo RGB tope 150/255 | Undervolt confirmado en sesión al subir más allá | Sí, si se cambia a fuente USB con mejor amperaje |
| WPM OFF + Luna ciclando (no reactiva al WPM) | RGB_MATRIX cuesta ~3KB; WPM era el sacrificio menos disruptivo. Luna mantiene los 5 frames ciclando por timer | Sí, deshabilitando RGB_MATRIX o quitando MOUSEKEY |
| SPLIT_LAYER_STATE_ENABLE removido | Para meter STARLIGHT como 5to efecto. Slave no necesita saber capa porque no muestra OLED de capa ni RGB indicators per-capa | Sí, si se agregan indicadores RGB de capa en el slave |
| SPLIT_* otras features quitadas | Firmware excedía 28KB de ATmega32U4 | Sí, si liberamos espacio |
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
5. [feature-weights.md](./feature-weights.md) — costos en flash medidos por feature (consultar **antes de** togglar features)
6. El `README.md` raíz — para ver el keymap actual documentado
7. `keyboards/sofle/keymaps/gonzafg2/keymap.c` — código fuente del keymap
