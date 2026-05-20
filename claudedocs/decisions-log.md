# Decisions log

Decisiones tomadas durante el desarrollo, con su justificación. Útil para entender el "por qué" antes de revertir algo.

## 2026-05-18 · Estructura QMK Userspace en vez de fork de qmk_firmware

**Decisión**: usar la estructura oficial `qmk_userspace` (qmk.json + GH Actions oficiales).

**Por qué**: replicar el flujo del repo del Corne (config separado, CI automatizado). Permite actualizar `qmk_firmware` a master sin merge conflicts. Estándar de QMK desde 2024.

**Alternativas descartadas**:
- Fork de `qmk_firmware`: pesado, mergear updates duele.
- Repo solo con keymap copiado: no tiene CI ni manifesto.

## 2026-05-18 · QMK en vez de migrar Sofle a ZMK

**Decisión**: mantener QMK (firmware preinstalado) en vez de migrar a ZMK.

**Por qué**: ZMK requiere nice!nano + batería LiPo (~USD 30 extra + tiempo). El Sofle es cableado, no se gana wireless sin reemplazar hardware. QMK ya está instalado.

**Reversible**: sí, si en algún momento quiere wireless.

## 2026-05-18 · Estilo de diagrama: Corne-style box-drawing Unicode

**Decisión**: usar `┌─┬─┐ │ ├─┼─┤ └─┴─┘` para los diagramas del README, sin asteriscos inline, con tablas de tap-hold aparte.

**Por qué**: el usuario aprobó el estilo del Corne y pidió replicar. Más limpio que el estilo `,---. | |` clásico de sofle docs.

**Confirmado por**: el usuario en preview side-by-side.

## 2026-05-18 · Capas: 5 (Base, Lower, Raise, Adjust, Mouse)

**Decisión**: replicar las 5 capas del Corne (no agregar ni quitar).

**Por qué**: mantener muscle memory con el Corne. Aprovechar las 16 teclas extras del Sofle (vs Corne 42) **dentro** de cada capa, no agregando más capas.

**Impacto técnico**: `DYNAMIC_KEYMAP_LAYER_COUNT 5` en config.h (default QMK = 4).

## 2026-05-18 · Encoder map por capa con `ENCODER_MAP_ENABLE`

**Decisión**: usar el feature moderno `ENCODER_MAP_ENABLE = yes` en vez de `encoder_update_user()` manual.

**Por qué**: más limpio, menos código, idiomatic QMK 2024+.

**Layout**:
- Base: vol / scroll-V
- Lower: brillo / scroll-H
- Raise: tab-nav (`⌘[`/`⌘]`) / word-nav (`⌥←`/`⌥→`)
- Adjust: media (prev/next) / brillo
- Mouse: scroll-V / scroll-H

## 2026-05-18 · RGB underglow deshabilitado

**Decisión**: `RGBLIGHT_ENABLE = no` por ahora.

**Por qué**: `keyboards/sofle/rev1` mainline NO trae configuración RGB out-of-box (no define `WS2812_DI_PIN` ni `RGBLED_NUM`). Activarlo provocaba error de compilación con todos los `RGB_*` keycodes "undeclared".

**Cómo activarlo después**:
1. Mirar el PCB del usuario para identificar el pin del data line RGB (probable D3)
2. Contar LEDs SK6812 por mitad (probable ~35)
3. Agregar a `keymaps/gonzafg2/config.h`:
   ```c
   #define WS2812_DI_PIN D3
   #define RGBLED_NUM 70
   ```
4. Cambiar `RGBLIGHT_ENABLE = yes` en rules.mk
5. Verificar que no exceda 28KB de AVR (RGB suma ~3KB)

## 2026-05-18 · SPLIT features quitadas para caber en AVR

**Decisión**: quitar `SPLIT_TRANSPORT_MIRROR`, `SPLIT_OLED_ENABLE`, `SPLIT_MODS_ENABLE`, `SPLIT_LED_STATE_ENABLE`. Mantener solo `SPLIT_LAYER_STATE_ENABLE` y `SPLIT_WPM_ENABLE`.

**Por qué**: build excedía 28KB del ATmega32U4 por 452 bytes.

**Impacto**: el OLED del slave (derecho) muestra contenido estático (logo + texto), no sincroniza con el master.

**Reversible**: sí, si liberamos espacio quitando otra feature.

## 2026-05-18 · `KC_MS_*` → `MS_*` (keycodes modernos)

**Decisión**: usar los keycodes nuevos `MS_LEFT`, `MS_DOWN`, `MS_UP`, `MS_RGHT`, `MS_WHLL`/`U`/`D`/`R`, `MS_BTN1`/`2`/`3`.

**Por qué**: QMK renombró los antiguos `KC_MS_*` / `KC_WH_*` / `KC_BTN*`. Los nuevos están bajo el feature `MOUSEKEY_ENABLE = yes`.

## 2026-05-18 · VIA habilitado pero sin vial.json custom

**Decisión**: `VIA_ENABLE = yes` pero usar la entrada Sofle existente de [usevia.app](https://usevia.app).

**Por qué**: VIA mainline ya soporta sofle/rev1. Los custom keycodes `GFG_*` aparecen como `Any` hex en VIA (limitación conocida, no es bug).

**Cómo mejorar**: generar `vial.json` con los GFG_* nombrados explícitamente (futuro, no necesario ahora).

## Decisiones pendientes (sin resolver)

Ver [thumb-cluster-iteration.md](./thumb-cluster-iteration.md):
- ¿Mantener doble Enter o consolidar a uno solo?
- ¿Reemplazar `LWR` y `RSE` solos por TAB/BSPC dedicados?
- ¿Otra alternativa que el usuario proponga?
