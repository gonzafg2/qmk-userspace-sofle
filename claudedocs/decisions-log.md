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

## ~~2026-05-18 · RGB underglow deshabilitado~~ (ANULADA — ver 2026-05-22)

**Decisión original**: `RGBLIGHT_ENABLE = no`.

**Por qué (al momento)**: se asumió que `keyboards/sofle/rev1` mainline no traía configuración RGB out-of-box. Esto resultó ser **falso** al verificar en 2026-05-22: mainline `keyboards/sofle/info.json` sí define `ws2812.pin=D3`, 72 LEDs (split 36/36), driver ws2812 y el layout RGB matrix completo. La decisión original se tomó sin verificar `info.json` (solo se miró `keyboard.json` de `rev1/`).

**Reemplazada por**: la entrada del 2026-05-22 más abajo.

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

## 2026-05-21 · Símbolos LATAM Mac: keycodes posicionales en LOWER + RAISE

**Decisión**: reemplazar aliases US-centric (`KC_LPRN`, `KC_LCBR`, `KC_TILD`, `KC_AT`, `KC_CIRC`, `KC_AMPR`, etc.) por keycodes posicionales que produzcan el símbolo correcto en macOS con layout Spanish LATAM.

**Por qué**: el Mac re-interpreta los scancodes USB según el layout activo. `KC_LPRN = LSFT(KC_9)` en US = `(`, pero en LATAM Mac = `)`. Mismo problema que resolvimos en el Corne (ZMK) — porteado a QMK con la tabla de mapeo equivalente.

**Mapeo verificado** (todos en LOWER right side y RAISE columnas afectadas):
- `(` = `S(KC_8)` · `)` = `S(KC_9)` · `\` = `A(KC_MINS)` · `?` = `S(KC_MINS)` · `_` = `S(KC_SLSH)`
- `{` = `KC_QUOT` · `}` = `KC_BSLS` · `~` = `RALT(KC_RBRC)` · `'` = `KC_MINS` · `"` = `S(KC_2)` · `` ` `` = `A(KC_BSLS)`
- `[` = `S(KC_QUOT)` · `]` = `S(KC_BSLS)` · `<` = `KC_NUBS` · `>` = `S(KC_NUBS)` · `|` = `KC_GRV`
- `@` = `RALT(KC_Q)` · `^` = `A(KC_QUOT)` · `&` = `S(KC_6)`

**Macros `GFG_*` en `users/gonzafg2/gonzafg2.c`** ya estaban correctas (usan `LSFT(KC_0)` para `=`, `KC_RBRC` para `+`, `KC_SLSH` para `-`, etc.) — no requirieron cambios.

**Gotcha QMK**: solo existen aliases cortos para mods izquierdos (`S()`, `A()`, `C()`, `G()`). Para mods derechos hay que usar la forma completa `RALT()` / `RCTL()` etc. `RA(...)` no existe y falla con `implicit declaration`.

## 2026-05-21 · OLED master: layout reorganizado con capa abajo + WPM

**Decisión**: reescribir el contenido del master OLED:
- Logo `GFG` arriba (filas 0-3)
- "by / Sofle" (filas 5-6)
- WPM en tiempo real (filas 8-9)
- CTL/SFT mods condicionales (filas 13-14)
- **Capa actual en la parte inferior** (fila 15), nombres completos: Base / Lower / Raise / Conf / Mouse

**Por qué**: el layout previo mostraba "Sofle / by ZK / LAYER / [capa]" pero "LAYER" (5 chars) hacía wrap incorrecto y se veía como una "R" colgada. El nuevo layout es más legible, más informativo (WPM), y la capa queda donde la vista cae naturalmente.

**Costo flash**: `WPM_ENABLE = yes` agregó ~880 bytes. Llegamos al 97% (28KB AVR).

## 2026-05-21 · Logo: cambio de mark abstracto a iniciales "GFG"

**Decisión**: reemplazar el bitmap del logo (un símbolo abstracto con dos triángulos opuestos, comentado como "GFG mark" pero que no decía GFG) por las **iniciales reales "GFG"** en Helvetica Neue Condensed Black 20px, centradas en 32×32.

**Por qué**: el comentario del código decía "GFG mark" pero el bitmap dibujaba un símbolo de "sync/swap" (⇅), no las iniciales. El usuario pidió que dijera GFG de verdad.

**Cómo se generó**: script Python con PIL + Helvetica Neue Condensed Black (en `/System/Library/Fonts/HelveticaNeue.ttc` index 9), size 20, output empaquetado a formato SSD1306 vertical LSB-first (128 bytes = 4 páginas × 32 cols).

## 2026-05-21 · VIA deshabilitado para hacer espacio para Luna pet

**Decisión**: `VIA_ENABLE = no` en `keymaps/gonzafg2/rules.mk`. Reemplaza la decisión previa del 2026-05-18.

**Por qué**: VIA gastaba ~2.5 KB de flash. Después de habilitar `WPM_ENABLE` (~880 B) llegamos al 97% (844 bytes libres). Para meter Luna pet (5 frames × 128 bytes = 640 B + ~150 B de lógica) sin reventar el AVR, había que liberar espacio. VIA era el más pesado y prescindible.

**Impacto**: el usuario pierde el editor VIA. Para remapear teclas hay que editar `keymap.c` y recompilar/reflashear.

**Reversible**: sí, si en algún momento prioriza VIA sobre Luna pet o si se cambia el controlador a uno con más flash (Elite-C, KB2040, etc).

## 2026-05-21 · Luna pet animado en slave OLED

**Decisión**: agregar gato Luna animado en la parte inferior del slave OLED (filas 12-15), debajo del texto "Eres / un / Crack".

**Por qué**: el usuario lo pidió ("Veamos como se ve el gato"). Da feedback visual del WPM en tiempo real.

**Implementación**:
- 5 frames 32×32 (sit / walk_a / walk_b / run_a / run_b)
- Sprites generados con Python + PIL usando primitivas (elipses, triángulos, rectángulos), NO son el Luna canónico de HellSingCoder
- Estado según WPM: `< 10` = sit estático, `< 40` = walk alterna cada 400 ms, `>= 40` = run alterna cada 200 ms
- Posicionado con `oled_set_cursor(0, 12)` + `oled_write_raw_P(frame, 128)`

**Trade-off**: los sprites son simples y pueden verse "blob-y" en el OLED real. Si no convencen, regenerar con sprites más detallados o copiar Luna canónico.

## 2026-05-21 · Encoder push en Base: Mute izq, Play der

**Decisión**:
- Izq: `GFG_MUTM` cambia de `LT(_MOUSE, KC_MPLY)` a `LT(_MOUSE, KC_MUTE)` (en `gonzafg2.h`). Tap = Mute, hold = capa Mouse. El nombre "MUTM" ahora cuadra con lo que hace (Mute + Mouse).
- Der: el slot pasa de `GFG_LOCK` a `KC_MPLY` directo. Tap = Play/Pause, sin hold.

**Por qué**: el usuario reportó que los encoder push "no funcionaban" en Base. Análisis:
1. `GFG_MUTM` con tap = Play era poco perceptible (si no hay app de media activa, no pasa nada visible).
2. `GFG_LOCK` con tap = lock screen es destructivo — un tap accidental te bloquea la sesión.
3. El nombre del izq decía "MUTM" pero hacía Play, inconsistente.

Mute + Play es más coherente con la rotación del encoder (que ya controla volumen izq + scroll der) y elimina el riesgo del lock accidental. `GFG_LOCK` sigue accesible desde la capa Adjust.

## 2026-05-22 · RGB_MATRIX activado (reemplaza decisión del 2026-05-18)

**Decisión**: `RGB_MATRIX_ENABLE = yes` con driver `ws2812`. Set acotado de 5 efectos. Brillo máx 150. Modo default `RGB_MATRIX_GRADIENT_LEFT_RIGHT`.

**Por qué**: el usuario lo pidió ("este Sofle es un RGB"). El PCB es **Sofle RGB V2 Rev2.1** (Josef Adamcik + mod RGB de Dane Evans) con 72 LEDs SK6812 MINI (58 per-key + 14 underglow, 36 per side).

**Hallazgo importante**: mainline `keyboards/sofle/info.json` ya configura `ws2812.pin=D3`, `rgb_matrix.split_count=[36,36]`, layout completo, y driver. **No** se necesita override en `config.h` de esos valores — solo defines estéticos.

**Trade-off para caber en AVR**: el framework RGB_MATRIX cuesta ~3KB y excedió por 498 bytes. Sacrificio elegido: **`WPM_ENABLE = no`** + simplificar `render_luna()` (sin reactividad a velocidad de tecleo). Luna sigue animándose, solo pierde el cambio sit/walk/run según WPM.

> ⚠️ Nota: la primera versión de `render_luna()` post-WPM fue un walk loop fijo. **El estado final shipped** es Luna ciclando por timer entre `sit → walk → run → sit` cada 6 segundos — ver "Iteraciones de la misma sesión" más abajo (iteración #1) para el código real.

**Configuración final** (`keyboards/sofle/keymaps/gonzafg2/config.h`):
```c
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_DEFAULT_VAL 100
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_STARLIGHT
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS

// Efectos custom propios en rgb_matrix_user.inc con BG idle heartbeat
#define RGB_MATRIX_CUSTOM_USER
```

⚠️ La lista de `#define ENABLE_*` original (que incluía `CYCLE_LEFT_RIGHT`, `TYPING_HEATMAP`, `SOLID_REACTIVE_SIMPLE`) fue iterada varias veces durante el desarrollo del PR. Lo de arriba refleja el **estado final shipped**, no la primera versión activada. Ver "Iteraciones post-PR original" más abajo y `feature-weights.md` para el historial completo.

**Keycodes en `_ADJUST`** (mano izquierda): se usan los nombres modernos `RM_*`, NO los legacy `RGB_*` (esos son solo para `RGBLIGHT_ENABLE`).

Layout inicial al activar RGB_MATRIX (después corregido — ver iteraciones):
- Row 0 cols 1-5: `RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU`
- Row 1 cols 1-5: `RM_SPDD, RM_PREV, RM_HUED, RM_SATD, RM_VALD`
- Thumb col 6 izq: `RM_SPDU` ⚠️ se descubrió que ese slot es el encoder push izquierdo (matrix [4,5]) con cold joint — no registra eventos. Corregido en iteración posterior moviendo `RM_SPDU` a row 1 col 0.

**Layout final correcto**:
- Row 0 cols 1-5: `RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU`
- Row 1 col 0-5: `RM_SPDU, RM_SPDD, RM_PREV, RM_HUED, RM_SATD, RM_VALD` (RM_SPDU agregado al inicio)
- Thumb col 6 izq: `XXXXXXX` (encoder push roto, no se asigna nada útil)

**Tamaño tras activar RGB_MATRIX** (antes de iteraciones de OLED): muy cerca del límite del AVR (~99%).

### Indicador del efecto RGB en master OLED (post-PR)

**Decisión**: la fila 15 del master OLED (que normalmente muestra la capa actual) **reemplaza temporalmente la capa por el nombre del efecto RGB** durante 2 segundos cuando el modo cambia. Implementado en `render_layer_state()` comparando `rgb_matrix_get_mode()` con un `last_rgb_mode` static cada frame.

**Por qué**: el usuario quería saber qué efecto tiene activo al ciclar con `RM_NEXT`/`RM_PREV`. La idea original era un indicador fijo en fila 12 (~120 B), pero el usuario propuso "reemplazar la capa por unos segundos" como alternativa más elegante (no requiere fila adicional, solo se ve cuando lo necesitas).

**Trade-off para meterlo en AVR**: convertí la **gata pet del master** de animada (2 frames con respiración cada 1500ms) a **estática** (solo `gata_a`). Liberó ~140 B; el indicador costó ~110 B; quedaron **+30 B netos** de margen. La gata del slave (Luna ciclando) NO fue tocada — sigue con sus 5 frames y 3 estados.

**Labels usados**: `Grad`, `Star`, `Cycl`, `Heat`, `Reac` (4 chars, consistentes con el ancho del OLED en orientación vertical).

### Iteraciones de OLED post-PR original

Tras los fixes de Copilot y nuevas features pedidas por el usuario, el OLED master quedó así:

- **Filas 7-8**: agregado texto `RGBv2` y `rev2` para identificación del PCB. Optimización: las 4 strings (` by  `, `Sofle`, `RGBv2`, `rev2 `) se escriben con UN solo `oled_write_P` concatenado (` by  SofleRGBv2rev2 `) aprovechando autowrap del cursor. Esto ahorró ~52 bytes vs llamadas separadas.
- **Gata pet**: movida de filas 8-11 a 9-12 para hacer espacio.
- **Filas 13-14**: indicador completo de los 8 mods (LCTL/RCTL/LALT/RALT/LSFT/RSFT/LGUI/RGUI) con codificación posicional en 2 filas:
  - Fila 13: `[LCTL][RCTL][ ][LALT][RALT]` → chars `C C   A A`
  - Fila 14: `[LSFT][RSFT][ ][LGUI][RGUI]` → chars `S S   M M`
  - Mismo truco de un solo buffer + un solo write con autowrap.
- **Fila 15**: capa **alineada a la izquierda** (`Base `, `Lower`, `Raise`, `Conf.`, `Mouse`). `Conf.` con punto final indica abreviación (Config no cabe en 5 chars).

**Tamaño tras todas las iteraciones**: ~99% del AVR (~10-30 bytes libres dependiendo del momento exacto; el número exacto se ve en el último `qmk compile` output, no en estos docs que se desactualizan rápido).

### Iteraciones de la misma sesión

1. **Luna ciclando entre sit/walk/run** (`keymap.c:render_luna`): después de quitar WPM, en vez de dejar Luna en walk loop fijo, se agregó un segundo timer (`luna_state_timer`) que cambia el estado cada 6 segundos (`sit → walk → run → sit`). Reincorpora los frames `luna_sit/luna_run_a/luna_run_b` que el linker había descartado por falta de referencias. Costo: ~150 bytes (+ los 384 B de los 3 frames PROGMEM que vuelven al binario).

2. **BREATHING → STARLIGHT**: el usuario pidió un efecto "ambiente nocturno". Reemplazo no fue flash-neutral (STARLIGHT pesa más); para meterlo se quitó adicionalmente `SPLIT_LAYER_STATE_ENABLE` (~130 B).

3. **`SPLIT_LAYER_STATE_ENABLE` removido** del `config.h` del keymap. Impacto práctico nulo en este setup porque:
   - El slave OLED nunca mostraba la capa (eso requería `SPLIT_OLED_ENABLE`, quitado desde el inicio por espacio AVR — ver decisión 2026-05-18 SPLIT features)
   - No tenemos indicadores RGB per-capa en el slave
   - Mod-tap / LT sigue funcionando porque cada lado evalúa su propia matriz

   **Cuándo volver a habilitarlo**: si en el futuro se agregan indicadores RGB de capa en el lado derecho (LEDs del slave cambian color según capa activa). Sin él, el slave no sabría qué capa está activa.

4. **`RGB_MATRIX_MAXIMUM_BRIGHTNESS 150`**: límite eléctrico, no arbitrario. Con 72 SK6812 a brillo absoluto del chip (255) el consumo teórico supera 4A — el USB del Mac (especialmente vía adaptador A↔C por el defecto del Pro Micro) no entrega esa corriente. **Confirmado en sesión**: al subir el brillo al máximo del tope configurado (150), el usuario reportó **titileo intermitente** de los LEDs. Es el síntoma clásico de **undervolt** del controlador → timing del data line a los SK6812 se corrompe. Mantener brillo ≤ 130 evita el problema. NO subir el define más allá de 150 sin cambiar a fuente USB con mejor amperaje.

**Pre-requisito físico**: jumper `Light Sel` del PCB debe estar en `UND` o `BL&UND`. Si está en `BL`, los SK6812 no reciben energía aunque el firmware esté perfecto.

**Reversible**: sí. Si en el futuro se prefiere recuperar WPM reactivo, volver a `WPM_ENABLE = yes`, restaurar `render_luna()` original y deshabilitar `RGB_MATRIX_ENABLE` (o cambiar a `RGBLIGHT_ENABLE` que es más liviano y permite mantener WPM).

## 2026-05-23 · Activar NKRO + `DEBOUNCE 8` para resolver dead-key intermitente en LATAM

**Decisión**: activar `NKRO_ENABLE = yes` + `FORCE_NKRO` en config, subir `DEBOUNCE` de 5 ms (default) a 8 ms. Para hacer espacio en flash, quitar los efectos RGB `STARLIGHT` y `SOLID_REACTIVE_MULTICROSS` (junto con sus cases en el switch OLED).

**Síntoma reportado**: al escribir rápido en LATAM (macOS), la tecla ´ (KC_LBRC) "no hace nada" y hay que repetirla para que la combinación ´+vocal produzca á/é/í/ó/ú. Intermitente, más frecuente al inicio de uso del Mac o tipeo rápido.

**Diagnóstico**:
- Verificado que `KC_LBRC` es keycode puro sin `LT()`/`MT()` ni combos → no es interferencia del firmware
- Verificado que NO había chatter (la tecla siempre registra cuando se prueba aislada)
- Causa raíz: **race condition entre las dos mitades del split + modo HID 6KRO de QMK**. La ´ está en la mitad derecha (slave), las vocales en la izquierda (master). El evento de ´ viaja por serial (~1-3 ms de lag) y, al escribir rápido, llega al master tan cerca del evento de la vocal que ambos se reportan en la misma ventana de polling USB (1 ms). En 6KRO el reporte HID es un array de 6 slots con orden ambiguo. macOS no puede saber qué tecla vino primero y la dead key del layout LATAM no combina.

**Por qué NKRO lo arregla**: cambia el reporte HID a un bitmap individual por tecla. Cada cambio se manda como evento atómico ordenado. Ya no hay ambigüedad de orden dentro de un mismo reporte.

**Por qué `DEBOUNCE 8` (no es la causa principal pero ayuda)**: subir de 5 a 8 ms agrega margen anti-chatter sin latencia perceptible al humano (8 ms < 1 frame a 60 fps). Costo en flash = 0 (es un define numérico).

**Costo en flash**: NKRO pesó **368 B medidos** (27652 → 28020). Antes del cambio el firmware estaba a 28498/28672 (174 libres) → no cabía. Se liberaron 846 B quitando STARLIGHT + MULTICROSS + sus cases OLED (medición conjunta; LTO produce dividendos no-lineales al quitar varios efectos juntos). Resultado final: **28020/28672 (652 libres)**.

**Por qué `STARLIGHT` y `MULTICROSS` y no otros**:
- `STARLIGHT` (label `Star`): efecto ambiental decorativo, no único — el gradient + custom MY_WAVE/MY_RAIN cubren el rol estético
- `SOLID_REACTIVE_MULTICROSS` (label `Cros`): efecto reactivo, pero el custom MY_RAIN ya provee reactividad con personalidad propia
- `SOLID_MULTISPLASH` (label `Wave`) **no se quitó** porque su código se comparte por LTO con el runner de MY_WAVE custom — quitarlo paradójicamente sube el binario (medido en sesión anterior)

**Por qué `FORCE_NKRO` y no `NKRO_ENABLE` solo**: `NKRO_ENABLE = yes` deja el binario con soporte para ambos modos pero arranca en 6KRO; requiere keycode `NK_TOGG` para cambiar. `FORCE_NKRO` asegura que arranque siempre en NKRO. El user pidió no incluir hotkey de toggle.

**Reversible**: sí. Si NKRO causara problemas en algún BIOS antiguo o KVM (improbable en macOS):
1. Quitar `FORCE_NKRO` y `NKRO_ENABLE = yes` → vuelve a 6KRO
2. Re-activar `ENABLE_RGB_MATRIX_STARLIGHT` y `ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS`
3. Restaurar los 2 cases en el switch OLED (`Star`, `Cros`)
4. Bajar `DEBOUNCE` a 5 (o quitar el define)

**Validación pendiente**: probar físicamente después de flashear que ´+vocal funciona consistente al escribir rápido. Tipear palabras como "también", "tenía", "está", "más rápido" y verificar que no se pierden vocales.

## 2026-05-23 · Sesión 2: Reorganización keymap (workflow Tech Lead) + mouse kinetic

**Contexto**: tras resolver el bug de dead keys con NKRO (decisión anterior), el user revisó el keymap completo y pidió 10 cambios para acomodar mejor su workflow diario como Tech Lead en macOS (window management, screenshare zoom, mouse preciso, layout más ergonómico).

### Cambios aplicados

**1. Convención de diagramas ASCII reescrita** (keymap.c comentarios + README.md). Los thumb clusters de Lower/Raise/Mouse mostraban contenido inconsistente con el código real (todos los thumbs son `_______` que heredan de Base, pero los diagramas mostraban combinaciones distintas — eran de iteraciones previas que nunca se actualizaron). Nueva convención documentada al inicio de `keymap.c`:
- `[KEY]` = heredada de Base (slot `_______`)
- `KEY` (sin corchetes) = asignada en esta capa
- `---` = bloqueada (`XXXXXXX`)
- `▼` = thumb que estás holdeando para activar la capa actual
- `[MUTM]` / `[PLAY]` = encoder push heredado de Base

Abreviaciones de 5 chars por límite visual: `[AGR]`=AltGr, `[RCT]`=RCtl, `[BSD]`=BSDL mod-morph, `[E/A]`=ESC/Adjust LT, `[MUT]`=MUTM, `[PLY]`=PLAY.

**2. Lower thumbs externos**: las dos únicas posiciones realmente libres del thumb cluster (pos 0 izq y pos 9 der, que en Base son `XXXXXXX`) ahora tienen propósito contextual al numpad activo en Lower:
- Pos 0 izq: `KC_PEQL` (= numpad)
- Pos 9 der: `KC_PENT` (Enter numpad)

**3. Raise mano derecha reorganizada para workflow Tech Lead**:

Fila 1 — Window/Spaces management mac (6 keycodes, 0 B en flash por ser combos QMK estándar):
- `MCTL` = `LCTL(KC_UP)` Mission Control
- `APXP` = `LCTL(KC_DOWN)` App Exposé
- `SPC-` / `SPC+` = `LCTL(KC_LEFT)` / `LCTL(KC_RGHT)` Space prev/next
- `ZM-` / `ZM+` = `LGUI(KC_PMNS)` / `LGUI(KC_PPLS)` Zoom out/in (para navegador, screenshare, IDE — verificar en LATAM Mac, si falla crear macro custom)

Fila 2 col 6-9: macros mac `SCRA`/`SCRT`/`LOCK`/`FQT` (movidas desde Adjust — más accesibles cerca de los cursores que se usan a menudo).
Fila 2 col 10: `QK_REP` (movido desde col 7).
Fila 3 col 10: `LGUI(KC_SPC)` Spotlight. Razón: el user dijo "tengo lejos CMD+Space"; ahora descansa en home row de la mano derecha.
Fila 3 col 3 izq: `GFG_MIEQ` (`-=`) reemplaza `S(KC_6)` (`^`). Razón: tener `+=` y `-=` juntos en orden. `^` se elimina de Raise (sigue accesible en Lower como `S(KC_6)`).

**4. Adjust limpiado**:
- `SCRF` (screenshot completo `⌘⇧3`) eliminado completamente del enum, handler y keymap. Poco uso confirmado.
- `SCRA`/`SCRT`/`LOCK`/`FQT` movidas a Raise (ver punto 3).
- Media (`VOL-`/`MUTE`/`VOL+` y `PREV`/`PLAY`/`NEXT`) movida una casilla a la derecha (cols 7-9 → 8-10). Razón ergonómica del user: descansan mejor en el meñique extendido en vez del índice al llegar desde el thumb hold.

**5. Mouse cascada completa**:
- Botones `BTN1`/`BTN3`/`BTN2`: fila 1 → fila 2
- Movimiento `MS_LEFT`/`DOWN`/`UP`/`RGHT`: fila 2 → fila 3
- Scroll `MS_WHLL`/`D`/`U`/`R`: fila 3 → fila 4 (cols 8-11)
- Fila 1 queda solo con `EXIT` en col 11; `EXIT` también en fila 4 col 13 (sin cambio)

Razón: la fila 1 era físicamente difícil de alcanzar con dedos descansados. Ahora botones en home row (fila 2), movimiento en alcance natural (fila 3), scroll en posición más extendida pero menos usado (fila 4).

**6. Mouse precisión con `MK_KINETIC_SPEED`**: activado en `users/gonzafg2/config.h` con parámetros tuneados:
```c
#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY              8
#define MOUSEKEY_INTERVAL           8
#define MOUSEKEY_MOVE_DELTA         16     // default 25
#define MOUSEKEY_INITIAL_SPEED      50     // default 100
#define MOUSEKEY_BASE_SPEED         3000   // default 5000
#define MOUSEKEY_DECELERATED_SPEED  400
#define MOUSEKEY_ACCELERATED_SPEED  3000
```
Resultado: tap individual = ~16 px (preciso para clicks de precisión), hold acelera suavemente con momentum tipo trackpad hasta 3000 px/s. Modo kinetic preferido sobre accelerated default por feel más natural.

### Medición de pesos

| Cambio | Costo en flash |
|---|---|
| `MK_KINETIC_SPEED` + params | +150 B (medido al toggle) |
| 7 keycodes Tech Lead (LCTL/LGUI combos) | 0 B (son macros QMK estándar) |
| `GFG_SCRF` eliminado (enum + case) | -30 B aprox |
| Reorganización keymap (mover keycodes) | 0 B |
| Diagramas ASCII | 0 B (solo comentarios) |
| **Total neto** | **+120 B aprox** |

Tamaño: 28020 → 28170 / 28672 (652 → 502 libres, 97% → 98%).

### Validación pendiente al flashear

1. **Zoom in/out** (`LGUI(KC_PPLS)` y `LGUI(KC_PMNS)`) en navegador/screenshare/IDE. Si no funciona en LATAM Mac, crear macro custom con `tap_code16(LGUI(LSFT(KC_0)))` para Cmd+Shift+0 (= Cmd++ en LATAM) y similar para Cmd+-.
2. **Mouse kinetic feel**: ¿tap individual = movimiento preciso? ¿hold acelera bien?
3. **Window management mac**: Mission Control, App Exposé, Spaces funcionan
4. **Spotlight** se abre rápido con la nueva posición home row
5. **Macros mac en Raise** (SCRA/SCRT/LOCK/FQT) cómodas sobre cursores
6. **Thumbs externos Lower** (= y Enter numpad) útiles cuando usas el numpad

### Reversible

Sí. Cada cambio es independiente:
- Quitar `MK_KINETIC_SPEED` + sus params → vuelve a accelerated default
- Restaurar bloques en `keymap.c` → keymap previo
- Re-agregar `GFG_SCRF` al enum + case → recupera screenshot completo
- Re-agregar `STARLIGHT`/`MULTICROSS` requiere quitar algo más (no caben en 502 B libres con todo lo nuevo)

## 2026-05-23 · Sesión 3: Activar `SPLIT_LAYER_STATE_ENABLE`, descartar `CHORDAL_HOLD`

**Contexto**: tras quedar con 502 B libres tras la sesión 2, el user pidió evaluar features de productividad que aporten valor. Se evaluaron `UNICODE_ENABLE`, `CHORDAL_HOLD`, `SPLIT_LAYER_STATE_ENABLE`, `TAPPING_TERM_PER_KEY` y otras.

### `SPLIT_LAYER_STATE_ENABLE`: activado (costo 0 B)

**Decisión**: activar `SPLIT_LAYER_STATE_ENABLE = yes` en `users/gonzafg2/rules.mk`.

**Por qué**: habilita que la mitad slave conozca la capa activa. Sin esto, el slave es ciego a la capa (solo procesa pulsaciones físicas y las manda al master, que las traduce). Activarlo abre tres puertas futuras:
1. Mostrar capa actual en el OLED slave (hoy muestra solo "Eres / un / Crack" + Luna)
2. RGB indicators per-layer en el slave (ej. cambiar color del thumb derecho según capa)
3. Animaciones reactivas a capa en el slave

**Costo medido**: **0 B**. Sorprendente — la medición previa (sesión 2026-05-22) decía ~130 B al quitarlo para meter STARLIGHT. Reactivarlo ahora costó 0 B porque LTO comparte código con algo ya presente en el build actual (probablemente las funciones de split transport ya están instanciadas por otras features de split que sí dependen del state).

**Tamaño**: 28170 → 28170 / 28672 (502 libres sin cambio).

**Reversible**: sí, `SPLIT_LAYER_STATE_ENABLE = no` y vuelve al estado anterior.

### `CHORDAL_HOLD`: probado y descartado

**Decisión**: NO activar `CHORDAL_HOLD`. Probado en sesión, pesó 1236 B (no cabe en 502 B libres, excede por 734 B).

**Plan probado** (revertido):
- `#define CHORDAL_HOLD` en `users/gonzafg2/config.h`
- Array `chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM` en `keymap.c` con `'L'`/`'R'` por posición usando el macro `LAYOUT`

**Costo medido**: **1236 B** (28170 → 29406, 734 B sobre el límite de 28672). Esto es **3-4× más pesado que la docs típica de QMK** (~340 B). Hipótesis: interacción con `HOLD_ON_OTHER_KEY_PRESS` + `PERMISSIVE_HOLD` ya activos, más el tamaño de la matriz del Sofle (5×14 = 70 posiciones × 1 byte cada una = 70 B solo del array, sin contar la lógica). Si la docs reporta ~340 B en keymaps mínimos, el costo escala con el contexto.

**Por qué se descartó (más allá del tamaño)**: en este keymap específico **CHORDAL_HOLD solo aplica a `GFG_ESCAD`** (LT(_ADJUST, KC_ESC) en el pinky derecho). No hay otros LT ni MT (`GFG_LWR`/`GFG_RSE` son `MO()`, no LT). El único caso de uso real sería evitar que ESC active Adjust accidentalmente al tipear rápido "ESC + tecla izq", que es un caso raro. ROI no justifica sacrificar 1.2 KB de otras features.

**Cuándo re-evaluar**: si en el futuro se agregan **home-row mods** (cada tecla de home row es un `MT()` con modificador en hold) o **más LT en thumbs**, CHORDAL_HOLD se vuelve crítico y valdría la pena buscar 1.2 KB sacrificando algo.

**Reversible**: sí, el código quedó comentado en `users/gonzafg2/config.h` con la nota:
```c
// CHORDAL_HOLD: descomentar para activar (probado 2026-05-23, pesaba ~1100 B
// en esta config, demasiado para el espacio disponible).
// #define CHORDAL_HOLD
```

### `UNICODE_ENABLE`: descartado sin probar

**Decisión**: NO activar.

**Por qué**:
1. Tamaño: ~500-1000 B según features, no cabe
2. Conflicto crítico con LATAM en macOS: requiere "Unicode Hex Input" como Input Source, choca con LATAM. Cambiar input source manualmente rompe el flujo de tipeo en español; cambiarlo desde firmware introduce delay y falla a veces
3. Mejores alternativas en macOS sin firmware: `Ctrl+Cmd+Space` (emoji picker nativo), Text Replacements en System Settings, Raycast/Alfred snippets, espanso. Todos funcionan en todas las apps sin tocar el teclado

### Estado final tras sesión 3

- Tamaño: 28170 / 28672 (502 libres, **sin cambio** del estado tras sesión 2)
- Único cambio efectivo: `SPLIT_LAYER_STATE_ENABLE = yes` (gratis, habilita futuro)
- Medición valiosa documentada: `CHORDAL_HOLD` pesa 1236 B en esta config (vs ~340 B típico de docs)

## Decisiones pendientes (sin resolver)

Ver [thumb-cluster-iteration.md](./thumb-cluster-iteration.md):
- ¿Mantener doble Enter o consolidar a uno solo?
- ¿Reemplazar `LWR` y `RSE` solos por TAB/BSPC dedicados?
- ¿Otra alternativa que el usuario proponga?

Pendiente verificar en físico (esta sesión):
- Posición real del Luna pet en el OLED (¿queda en parte inferior como esperado o en otra zona por la rotación 270°?)
- Estética de los sprites del gato en el OLED real
- Que el encoder push izq registre tap = Mute (puede ser problema de tapping_term del LT)
