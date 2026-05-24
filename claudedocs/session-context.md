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
   - `SPLIT_LAYER_STATE_ENABLE` removido (~130 B; sin impacto visible). NOTA: reactivado en sesión 2026-05-23 (3) sin costo (0 B medidos en nuevo contexto)
5. **Iteraciones de Luna**: primero a walk loop fijo (post-WPM), después **Luna ciclando** entre sit→walk→run cada 6s (los 5 sprites originales mantenidos, frijol-y-nieblita stay).
6. **Set inicial de efectos RGB** (luego iterado): `GRADIENT_LEFT_RIGHT` (default), `STARLIGHT`, `CYCLE_LEFT_RIGHT`, `TYPING_HEATMAP`, `SOLID_REACTIVE_SIMPLE`. Después de varias iteraciones el **set final shipped** quedó: `GRADIENT_LEFT_RIGHT`, `STARLIGHT`, `SOLID_MULTISPLASH`, `SOLID_REACTIVE_MULTICROSS` + custom `MY_WAVE` + `MY_RAIN` con BG idle heartbeat. `SOLID_COLOR` siempre activo (always-on en QMK).
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

## Sesión 2026-05-23 — fix dead-key intermitente en LATAM (NKRO)

**Síntoma**: al escribir rápido en macOS LATAM, la tecla ´ "no hacía nada" y había que repetirla para que ´+vocal combinara en á/é/í/ó/ú. Intermitente, más frecuente al inicio de uso del Mac.

**Diagnóstico** (ver [decisions-log.md](./decisions-log.md)): race condition entre las dos mitades del split + modo HID 6KRO. Los eventos del slave (donde está ´) llegan al USB tan cerca de los del master (vocales) que macOS no puede determinar cuál vino primero, rompiendo el dead key.

**Cambios aplicados**:
1. `users/gonzafg2/config.h`: + `FORCE_NKRO`, + `DEBOUNCE 8`
2. `users/gonzafg2/rules.mk`: + `NKRO_ENABLE = yes`
3. `keyboards/sofle/keymaps/gonzafg2/config.h`: – `ENABLE_RGB_MATRIX_STARLIGHT`, – `ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS`
4. `keyboards/sofle/keymaps/gonzafg2/keymap.c`: – 2 cases del switch OLED (`Star`, `Cros`)
5. `~/dotfiles/zsh/.zshrc`: + bloque PATH para `avr-gcc@8` (keg-only en Homebrew, hasta hoy nunca había compilado local — todo era CI)

**Medición de pesos** (✅ compilado local con avr-gcc 8.5.0):
- NKRO_ENABLE: **368 B medidos** (27652 → 28020)
- STARLIGHT + MULTICROSS + 2 cases OLED (combinado): **846 B liberados** — mucho más que la suma individual estimada (~320 B), confirmando que LTO produce dividendos no-lineales al quitar varios efectos juntos
- Tamaño final: **28020 / 28672 bytes (97%, 652 libres)**

**Validación pendiente**: probar físicamente tras flashear que ´+vocal funciona consistente al escribir rápido.

## Sesión 2026-05-23 (sesión 2) — reorganización keymap workflow Tech Lead + mouse kinetic

Tras resolver el bug de dead keys, el user revisó el keymap completo y pidió 10 cambios para acomodar su workflow diario como Tech Lead en macOS (window management, screenshare zoom, mouse preciso, layout más ergonómico).

**Cambios aplicados** (detalle completo en [decisions-log.md](./decisions-log.md) entrada "Sesión 2"):

1. **Convención `[KEY]` en diagramas ASCII** — keymap.c (comentarios) + README.md. Notación: `[KEY]` = heredada de Base, `KEY` = asignada en capa, `---` = bloqueada (`XXXXXXX`), `▼` = thumb activo. Thumb clusters de Lower/Raise/Mouse corregidos (estaban desincronizados con código real).
2. **Lower thumbs externos**: `KC_PEQL` (= numpad) izq + `KC_PENT` (Enter numpad) der — únicas posiciones realmente libres en thumb cluster.
3. **Raise fila 1 mano der**: 6 keycodes window mgmt mac (Mission Control, App Exposé, Space prev/next, Zoom-, Zoom+).
4. **Raise fila 2 col 6-9**: SCRA/SCRT/LOCK/FQT movidas desde Adjust (sobre cursores). `QK_REP` movido a col 10.
5. **Raise fila 3 col 3 izq**: `-=` reemplaza `^` (junto a `+=`). Fila 3 col 10 der: Spotlight (LGUI+SPC).
6. **Adjust**: eliminado `GFG_SCRF` (enum + handler). Media (VOL/MUTE y PREV/PLAY/NEXT) movida col 7-9 → 8-10.
7. **Mouse cascada completa**: botones BTN→fila 2, movimiento→fila 3, scroll→fila 4. Más cómodo para dedos descansados.
8. **Mouse precisión**: `MK_KINETIC_SPEED` activado + params tuneados (`MOVE_DELTA 16`, `INITIAL_SPEED 50`, `BASE_SPEED 3000`).

**Medición**: +150 B neto (de 28020 → 28170 / 28672, 502 libres, 97% → 98%). NKRO+combos 0 B, MK_KINETIC +150 B, GFG_SCRF -30 B.

## Sesión 2026-05-23 (sesión 5) — aperturas LATAM ¡/¿ + limpieza thumbs Lower + cosmético

Tras flashear las sesiones 1-4, el user revisó el thumb cluster de Base y abrió un ciclo de pulido (detalle en [decisions-log.md](./decisions-log.md) entrada "Sesión 5"):

1. **Cosmético**: `---` (slots `XXXXXXX`) → celda vacía en diagramas ASCII de keymap.c y README.md. Convención actualizada al inicio del keymap.
2. **Lower thumbs externos eliminados**: `KC_PEQL` y `KC_PENT` (cols 0 y 13 fila 4 Lower) → `XXXXXXX`. Revierte sesión 2 punto 2 — el usuario reportó bajo uso real (calculadora vía Spotlight, Enter ya en thumb interior).
3. **Raise col 0 fila 2**: `LCTL(KC_O)` (JBk neovim) → `KC_EQL` (¿ apertura). Usuario no usa Neovim regularmente.
4. **Raise col 1 fila 2**: `KC_EXLM` (!) → `S(KC_EQL)` (¡ apertura). `!` simple sigue en Lower.
5. **Hipótesis LATAM Mac de `¿`/`¡`**: tecla US `=` produce `¿` sin shift y `¡` con shift (convención ISO LATAM). Verificar al flashear; si falla, probar `A(KC_1)` para `¡` y `A(S(KC_1))`/`A(KC_SLSH)` para `¿`.
6. **SFT y CMD en Raise — mantenidos** tras investigación de combos `Cmd+arrow`/`Cmd+Shift+arrow`: navegación y selección por línea/archivo son críticas cuando las flechas viven en Raise.
7. **Pendientes deferidos**: col 12 fila 4 Raise sigue `XXXXXXX` (candidatos `&`, `!=`, `++`, `<<`, etc.); Adjust ~24 slots libres sin tocar (Hyperkey, macros IDE, sleep display considerados pero no implementados).

**Tamaño**: 28170 / 28672 (502 libres, sin cambio). Todos los cambios zero-cost.

## Sesión 2026-05-23 (sesión 4) — ajustes post-flasheo

Tras flashear y probar, 6 ajustes basados en feedback de uso real (detalle en [decisions-log.md](./decisions-log.md) entrada "Sesión 4"):

1. **Mouse aceleración**: `MOUSEKEY_BASE_SPEED 3000 → 2000` (sentía muy rápido al hold)
2. **TGMOU**: Adjust fila 2 col 6 → fila 3 col 6 (coherencia con bloque media VOL/MUTE)
3. **Mouse scroll**: cols 9-12 → cols 8-11 fila 4 (alineado vertical con movimiento y botones)
4. **`ZM0` reset zoom**: nuevo `LGUI(KC_0)` en Raise fila 2 col 11 (reemplaza `[BSDL]` heredado). Labels `SPC-/SPC+` renombrados a `SPCL/SPCR` para claridad
5. **Emoji picker**: nuevo `LGUI(LCTL(KC_SPC))` en Raise fila 3 col 11 al lado de SPOT
6. **Neovim `JBk`**: nuevo `LCTL(KC_O)` jump back en Raise fila 2 col 0 (reemplaza `[TAB]` heredado). `[SFT]` y `[CMD]` mantenidos heredados — son modifiers críticos en Raise

**Nota sobre Spaces lento**: el delay entre cambiar Space y poder tipear es animación nativa de macOS (~300 ms), no firmware. Recomendado activar `System Settings → Accessibility → Display → Reduce Motion`.

**Tamaño**: 28170 / 28672 (502 libres, sin cambio). Todos los cambios fueron 0 B.

## Sesión 2026-05-23 (sesión 3) — `SPLIT_LAYER_STATE_ENABLE` activado, `CHORDAL_HOLD` descartado

Tras quedar con 502 B libres, evaluamos qué features de productividad valdrían la pena.

**Cambios aplicados** (detalle en [decisions-log.md](./decisions-log.md) entrada "Sesión 3"):

1. **`SPLIT_LAYER_STATE_ENABLE = yes`**: habilita que el slave sepa la capa activa. Costo medido: **0 B** (la medición previa de ~130 B no aplica en el contexto actual; LTO comparte código). Sin uso visible aún, abre puerta a mostrar capa en OLED slave o RGB indicators per-layer.
2. **`CHORDAL_HOLD` probado y descartado**: pesó **1236 B** (3-4× más que la docs típica de QMK). No cabe + ROI marginal en este keymap (solo aplica a `GFG_ESCAD`, único LT). Si en futuro se agregan home-row mods, re-evaluar.
3. **`UNICODE_ENABLE` descartado sin probar**: tamaño 500-1000 B + conflicto con LATAM Input Source en macOS. Alternativas no-firmware (Ctrl+Cmd+Space, Text Replacements, Raycast) son mejores.

**Tamaño final**: 28170 / 28672 (502 libres, sin cambio vs sesión 2).

## Trade-offs aceptados

| Decisión | Por qué | Reversible |
|---|---|---|
| RGB_MATRIX activo (vs RGBLIGHT) | El usuario lo pidió. Efectos reactivos al tecleo (heatmap, solid reactive) | Sí, cambiando a `RGBLIGHT_ENABLE = yes` (más liviano) |
| Brillo RGB tope 150/255 | Undervolt confirmado en sesión al subir más allá | Sí, si se cambia a fuente USB con mejor amperaje |
| WPM OFF + Luna ciclando (no reactiva al WPM) | RGB_MATRIX cuesta ~3KB; WPM era el sacrificio menos disruptivo. Luna mantiene los 5 frames ciclando por timer | Sí, deshabilitando RGB_MATRIX o quitando MOUSEKEY |
| SPLIT_LAYER_STATE_ENABLE (reactivado 2026-05-23 sesión 3, costo 0 B) | Habilita futuro mostrar capa en OLED slave o RGB indicators per-layer. Sin uso visible aún. | Sí, `= no` y vuelve al estado anterior |
| SPLIT_* otras features quitadas | Firmware excedía 28KB de ATmega32U4 | Sí, si liberamos espacio |
| VIA con custom keycodes hex | VIA mainline no conoce los `GFG_*` | Sí, generando vial.json |
| STARLIGHT + MULTICROSS removidos (2026-05-23) | Liberar 846 B para meter NKRO (368 B) y resolver dead-key intermitente en LATAM. Set RGB final shipped: `Grad`, `Wave`, `iWav`, `iRai` (4 efectos vs 6 previos) | Sí, requiere desactivar NKRO o sacrificar otra cosa |

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
