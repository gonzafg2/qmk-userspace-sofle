# QMK Userspace · Sofle RGB ZK (gonzafg2)

Configuración QMK para teclado **Sofle RGB V2 Rev2.1** (Josef Adamcik v2.1 con mod RGB de Dane Evans, fabricado por ZoneKeyboards) con Pro Micro USB-C ATmega32U4, switches MX, 2 encoders rotatorios, 2 OLEDs y 72 LEDs SK6812 MINI direccionables (per-key + underglow) controlados por `RGB_MATRIX`. Pensado para **macOS con layout Spanish ISO LATAM**.

Sigue la estructura oficial **QMK Userspace** — keymap mantenido fuera del fork de `qmk_firmware`, build automatizado por GitHub Actions.

Hermano del repo [zmk-config-corne](https://github.com/gonzafg2/zmk-config-corne) — mismo flujo de capas, macros y operadores prog, adaptado al stack QMK (cableado) en lugar de ZMK (BLE).

## Hardware confirmado

| Componente | Detalle |
|---|---|
| PCB | **Sofle RGB V2 Rev2.1** — Josef Adamcik v2.1 base + mod RGB de Dane Evans. Fabricado por ZoneKeyboards Chile (serigrafía "Power by Sofle RGB, Dane Evans" + logo lagarto ZK) |
| Controlador | Pro Micro clon **USB-C ATmega32U4 5V** |
| Switches | MX hotswap (Gateron Blue + otros MX, vástago cruz estándar) |
| LEDs | **72 SK6812 MINI direccionables** (58 per-key + 14 underglow, 36 per side, pin data D3) + LEDs blancos backlight tradicional. Jumper `Light Sel` selecciona alimentación: BL / **UND** (actual) / BL&UND |
| Encoders | 2× EC11 con push button (uno por mitad) |
| OLED | 2× SSD1306 128×32 en orientación vertical |
| Comunicación split | TRRS |
| Jumpers PCB | `Light Sel`, `Backlight enable`, `Ind bypass` |

## Las 5 capas — cómo cambiar entre ellas

```
                            ┌──────────┐
                            │   BASE   │ ← default (sin hold)
                            └─────┬────┘
                                  │
        ┌────────────┬────────────┼────────────┬────────────┐
        │            │            │            │            │
   hold col 4    hold col 2  hold AMBOS   hold ENC-IZQ  tap TGMOUSE
    izq thumb     der thumb   pulgares    (push botón)  desde Adjust
        │            │            │            │            │
        ▼            ▼            ▼            ▼            ▼
    ┌───────┐    ┌───────┐    ┌───────┐    ┌───────┐    ┌───────┐
    │ LOWER │    │ RAISE │    │ ADJUST│    │ MOUSE │    │ MOUSE │
    │  (1)  │    │  (2)  │    │  (3)  │    │  (4)  │    │  (4)  │
    └───────┘    └───────┘    └───────┘    └───────┘    └───────┘
                                  ▲ tambien: hold ESC pinky der
```

| Capa | # | Activación | Tipo |
|---|---|---|---|
| Base | 0 | default | — |
| Lower | 1 | hold thumb izq col 4 | momentary |
| Raise | 2 | hold thumb der col 2 | momentary |
| Adjust | 3 | hold AMBOS Lower+Raise (tri-layer) **o** hold ESC pinky der | momentary |
| Mouse | 4 | hold encoder push izq (momentary) **o** tap TG_MOUSE en Adjust (persistente) | mixto |

Salir de Mouse persistente: tap **EXIT** (esquina sup der o esquina inf der dentro de Mouse).

### Base — QWERTY LATAM macOS

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  1  │  2  │  3  │  4  │  5  │                              │  6  │  7  │  8  │  9  │  0  │ DEL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  Q  │  W  │  E  │  R  │  T  │                              │  Y  │  U  │  I  │  O  │  P  │BSDL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │  A  │  S  │  D  │  F  │  G  │                              │  H  │  J  │  K  │  L  │  Ñ  │  ´  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ CMD │  Z  │  X  │  C  │  V  │  B  │MUTM │  ◉vol     scrl◉  │PLAY │  N  │  M  │  ,  │  .  │  -  │ESC/A│
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │ ALT │ CTL │ LWR │ SPC │        │ ENT │ RSE │ALTGR│ CTL │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
```

`SFT` = Shift · `CMD` = Cmd (Mac) · `CTL` = Ctrl · `ALT` = Alt · `ALTGR` = AltGr (= RAlt en ISO LATAM)
`MUTM` = Mute al tap, hold = capa Mouse · `PLAY` = Play/Pause · `ESC/A` = Esc al tap, hold = capa Adjust

### Lower — numpad + símbolos LATAM

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ F12 │ F1  │ F2  │ F3  │ F4  │ F5  │                              │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  7  │  8  │  9  │  /  │  *  │                              │  (  │  )  │  \  │  !  │  ?  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  4  │  5  │  6  │  +  │  -  │                              │  {  │  }  │  ~  │  '  │  "  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │  1  │  2  │  3  │  .  │  0  │BRDN │ ◉brillo   scrH◉  │BRUP │  [  │  ]  │  <  │  >  │  |  │  _  │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │  ▼  │     │        │     │     │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                    ▲ activa
```

Casillas vacías = transparent (heredan de Base). Encoder izq cambia a brillo, encoder der a scroll horizontal.

### Raise — operadores programación + navegación

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  =  │ >=  │ <=  │ ??  │ ?.  │ **  │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  !  │  @  │  #  │  $  │  %  │                              │     │ RPT │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  ^  │ +=  │  &  │ &&  │ ||  │                              │  ←  │  ↓  │  ↑  │  →  │ -=  │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ =>  │ ... │ ==  │ !== │ === │     │ ◉tab     word◉   │     │HOME │PGDN │PGUP │ END │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │     │        │     │  ▼  │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                                                ▲ activa
```

`RPT` = `QK_REP` (repite la última tecla pulsada). Encoder izq cambia a tab nav (`⌘[` / `⌘]`), encoder der a word nav (`⌥←` / `⌥→`).

### Adjust — sistema, macros mac, media, **RGB**

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BOOT │ TOG │ NXT │ HU+ │ SA+ │ VA+ │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SP+ │ SP- │ PRV │ HU- │ SA- │ VA- │                              │TGMOU│     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │SCRF │SCRA │SCRT │LOCK │FQT  │                              │     │VOL- │MUTE │VOL+ │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │ ◉track  brillo◉  │     │     │PREV │PLAY │NEXT │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │  ▼  │     │        │     │  ▼  │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                          ▲ hold ambos LWR+RSE | hold ESC
```

**Sistema y macros mac:**
`BOOT` = `QK_BOOT` (entra a bootloader para flashear) · `SCRF/A/T` = screenshots mac (`⌘⇧3`/`4`/`5`)
`LOCK` = `⌘⌃Q` · `FQT` = Force Quit (`⌘⌥Esc`) · `TGMOU` = toggle capa Mouse persistente

**Controles RGB (RGB_MATRIX, keycodes `RM_*`):**

| Tecla en Adjust | Keycode QMK | Hace |
|---|---|---|
| `TOG` | `RM_TOGG` | Encender / apagar RGB |
| `NXT` / `PRV` | `RM_NEXT` / `RM_PREV` | Siguiente / anterior efecto |
| `HU+` / `HU-` | `RM_HUEU` / `RM_HUED` | Tono (matiz) +/- |
| `SA+` / `SA-` | `RM_SATU` / `RM_SATD` | Saturación +/- (gris ↔ vivo) |
| `VA+` / `VA-` | `RM_VALU` / `RM_VALD` | Brillo +/- (tope a 150 por límite USB) |
| `SP+` / `SP-` | `RM_SPDU` / `RM_SPDD` | Velocidad animación +/- |

**9 efectos en el ciclo** (`NXT` cicla todos):

1. `RGB_MATRIX_SOLID_COLOR` *(always-on de QMK, no se puede deshabilitar)* — todo el teclado en un solo color fijo del HUE actual
2. `RGB_MATRIX_GRADIENT_LEFT_RIGHT` *(default al boot)* — gradient estático rojo→violeta de izq a der
3. `RGB_MATRIX_STARLIGHT` — LEDs random titilan suavemente como estrellas (ambiental)
4. `RGB_MATRIX_CYCLE_LEFT_RIGHT` — colores corren horizontalmente (ambiental)
5. `RGB_MATRIX_SOLID_MULTISPLASH` — ondas circulares un solo color (reactivo, sin BG idle)
6. `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` — al pulsar, fila + columna se iluminan en cruz (reactivo, sin BG idle)
7. `RGB_MATRIX_MULTISPLASH` — ondas arcoíris (reactivo, sin BG idle)
8. **`MY_WAVE` (custom)** — ondas un solo color + **fondo idle tenue** del HUE actual
9. **`MY_RAIN` (custom)** — ondas arcoíris + **fondo idle tenue** del HUE actual

Los efectos custom (8-9) están implementados en [`rgb_matrix_user.inc`](./keyboards/sofle/keymaps/gonzafg2/rgb_matrix_user.inc) y usan `BG_VALUE = 50` (~20% de brillo idle, modulado por VAL global).

**Pre-requisito físico**: jumper `Light Sel` del PCB debe estar en `UND` o `BL&UND` para alimentar los SK6812.

**Brillo limitado a 150/255 por hardware**: con 72 SK6812 al máximo del chip, el consumo excede el amperaje USB del Mac vía adaptador A↔C → undervolt → LEDs parpadean intermitentemente. No subir `RGB_MATRIX_MAXIMUM_BRIGHTNESS` sin una fuente USB con mejor amperaje.

### Mouse — movimiento + scroll + click

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │BTN1 │BTN3 │BTN2 │     │     │EXIT │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │ ←M  │ ↓M  │ ↑M  │ →M  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │     │     │     │     │     │                              │ ←S  │ ↓S  │ ↑S  │ →S  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ CMD │     │     │     │     │     │     │  ◉scrV    scrH◉  │     │     │     │     │     │     │EXIT │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ CTL │ ALT │     │     │ SPC │        │ ENT │     │     │ALTGR│ CTL │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
              ▲ hold encoder push izq (momentario) | tap TGMOU desde Adjust (persistente)
```

`M` = movimiento del cursor · `S` = scroll · `BTN1/2/3` = clic izq / medio / der · `EXIT` = `TG(_MOUSE)` apaga la capa

Mano izq mantiene Shift y Cmd para combos: Shift+click (selección), Cmd+click (abrir en nueva pestaña), Ctrl+click (menú contextual mac).

## Modificadores standard PC — dónde queda cada uno

| Mod | Izquierda | Derecha |
|---|---|---|
| Cmd (LGUI/RGUI) | pinky fila 3 col 1 | — |
| Ctrl (LCTL/RCTL) | thumb col 1 | thumb col 5 |
| Alt (LALT) | thumb col 2 | — |
| AltGr (RAlt) | — | thumb col 4 (genera `¿ ¡ @ # € \` en ISO LATAM) |
| Shift (LSFT) | pinky fila 2 col 1 | — |
| Tab | pinky fila 1 col 1 (tradicional) | — |
| Bspc/Del | — | pinky fila 1 col 6 (mod-morph BSDL: tap=Bspc, Shift+tap=Del) |
| Enter | — | thumb col 1 (reposo) |
| Space | thumb col 5 (reposo) | — |

## Encoders por capa

| Capa | Encoder izq (rotación / push) | Encoder der (rotación / push) |
|---|---|---|
| Base | Volumen ± / **Mute (tap), Mouse (hold)** | Scroll vertical / Play-Pause |
| Lower | Brillo ± / Brillo down | Scroll horizontal / Brillo up |
| Raise | Tab nav `⌘[` `⌘]` / — | Word nav `⌥←` `⌥→` / — |
| Adjust | Track prev / next / — | Brillo ± / — |
| Mouse | Scroll vertical / — | Scroll horizontal / — |

`LOCK` pantalla (`⌘⌃Q`) sigue accesible desde la capa Adjust (segunda fila izq).

> **⚠️ Hardware conocido**: en la unidad actual los **push de los encoders no registran señal eléctrica** (cold joint diagnosticado, no es bug de firmware). La rotación funciona correctamente. Los keycodes de tap/hold están asignados correctamente y funcionarán una vez resoldados los pines del switch del EC11. Detalle del diagnóstico en [`claudedocs/hardware-notes.md`](./claudedocs/hardware-notes.md).

## Caps Word

Doble tap rápido de **Shift** (LSFT) activa Caps Word — mayúsculas temporales hasta que pulses espacio, enter, tab o pase un timeout. Útil para escribir constantes (`MAX_RETRIES`) o acrónimos sin mantener Shift.

Activado vía `DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD` (built-in de QMK, sin overhead de `COMBO_ENABLE`).

## Macros macOS (Adjust)

Implementadas con `tap_code16` LATAM-aware en `users/gonzafg2/gonzafg2.c`:

| Tecla | Acción |
|---|---|
| `SCRF` | `⌘⇧3` (screenshot completo) |
| `SCRA` | `⌘⇧4` (área) |
| `SCRT` | `⌘⇧5` (herramienta) |
| `LOCK` | `⌘⌃Q` (lock pantalla) |
| `FQT` | `⌘⌥Esc` (Force Quit) |

## Operadores de programación (Raise)

`=>` · `...` · `==` · `!==` · `===` · `&&` · `||` · `+=` · `-=` · `>=` · `<=` · `??` · `?.` · `**`

Implementados con `tap_code` y `tap_code16` enviando keycodes nativos LATAM (no `SEND_STRING` ASCII). Esto garantiza que `&&`, `||`, `=>`, etc. salgan correctos en macOS con teclado físico **ISO Spanish LATAM**.

## OLED

Ambos OLEDs son **SSD1306 128×32 en orientación vertical** (rotación 270°), formato 5 chars × 16 líneas.

### Mitad izquierda (master)

```
[logo GFG]    filas 0-3  — iniciales en Helvetica Neue Condensed Black
 by           fila 5
Sofle         fila 6
RGBv2         fila 7     — identificación del PCB
              fila 8     — separador
[gata pet]    filas 9-12 — gata estática (sentada alerta, 32×32)
CC AA         fila 13    — Ctrl izq/der + Alt/AltGr (ver abajo)
SS MM         fila 14    — Shift izq/der + Cmd izq/der (ver abajo)
Lower / Star  fila 15    — capa actual O efecto RGB (ver abajo)
```

**Filas 13-14 - indicadores de mods con distinción L/R** (codificación posicional fija, 2 filas × 5 chars = 8 mods + 2 separadores):

Fila 13 (Ctrl + Alt):

| Pos | Char | Mod |
|---|---|---|
| 0 | `C` | LCTL |
| 1 | `C` | RCTL |
| 2 | `_` | (separador visual, espacio) |
| 3 | `A` | LALT |
| 4 | `A` | RALT (AltGr) |

Fila 14 (Shift + GUI):

| Pos | Char | Mod |
|---|---|---|
| 0 | `S` | LSFT |
| 1 | `S` | RSFT |
| 2 | `_` | (separador visual, espacio) |
| 3 | `M` | LGUI (LCmd) |
| 4 | `M` | RGUI (RCmd) |

Cada posición tiene una letra fija que aparece sólo cuando ese mod específico está held; si no, un espacio. Posición 2 siempre es separador.

**Ejemplos**:
- Solo LCTL: `C    ` / `     `
- LCTL + LSFT + LCmd: `C    ` / `S  M `
- AltGr (RALT) + Shift derecho: `   _A` / ` S   ` (donde `_` es realmente espacio)
- Todos los 8 mods: `CC AA` / `SS MM`

**Fila 15 - comportamiento dinámico:**
- Por default muestra la **capa actual** alineada a la izquierda: `Base ` / `Lower` / `Raise` / `Conf.` / `Mouse` (5 chars; `Conf.` con punto final indica abreviación de Adjust/Config — `Config` tiene 6 chars y no cabe)
- Cuando cambias el efecto RGB con `RM_NEXT` / `RM_PREV` / `RM_TOGG`, **reemplaza** la capa por el efecto activo durante **2 segundos**, luego vuelve a la capa:

| Label | Efecto |
|---|---|
| `Grad` | `RGB_MATRIX_GRADIENT_LEFT_RIGHT` |
| `Star` | `RGB_MATRIX_STARLIGHT` |
| `Cycl` | `RGB_MATRIX_CYCLE_LEFT_RIGHT` |
| `Soli` | `RGB_MATRIX_SOLID_COLOR` (color sólido fijo) |
| `Wave` | `RGB_MATRIX_SOLID_MULTISPLASH` (ondas mono, sin BG idle) |
| `Cros` | `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` (cruz fila+columna) |
| `Rain` | `RGB_MATRIX_MULTISPLASH` (ondas arcoíris, sin BG idle) |
| `iWav` | `MY_WAVE` custom (ondas mono **+ BG idle tenue**) |
| `iRai` | `MY_RAIN` custom (ondas arcoíris **+ BG idle tenue**) |

Detección autocontenida en `render_layer_state()` — compara `rgb_matrix_get_mode()` con el último modo conocido, dispara el indicador en cambios. No requiere hooks en `process_record_user`.

### Mitad derecha (slave)

```
[logo GFG]    filas 0-3
 Eres         fila 5
  un          fila 7
Crack         fila 9
[Luna pet]    filas 12-15  — gato animado ciclando sit/walk/run
```

**Luna pet** cicla automáticamente entre 3 estados cada 6 segundos (ya no depende de WPM, que se deshabilitó para dejar espacio a RGB_MATRIX):

| Segundos | Estado | Animación |
|---|---|---|
| 0-6 | `luna_sit` | Frame estático (sentada) |
| 6-12 | `luna_walk_a` ↔ `luna_walk_b` | Camina alternando frames cada 400 ms |
| 12-18 | `luna_run_a` ↔ `luna_run_b` | Corre alternando frames cada 200 ms |

Cumplido el ciclo vuelve a `sit` y repite. Implementado con dos timers (`luna_state_timer` para el cambio de estado cada 6s + `luna_frame_timer` para el flip dentro de walk/run).

## Setup macOS para LATAM

El teclado Sofle es **físicamente ANSI** (6 columnas por lado, 12 teclas por fila, sin la tecla extra del ISO). El firmware envía keycodes USB estándar que macOS interpreta según **dos** factores independientes:

1. **Input Source** activo (la bandera arriba a la derecha del menu bar)
2. **Keyboard Type** asociado al teclado físico (ANSI / ISO / JIS)

### 1. Input Source

`System Settings → Keyboard → Input Sources` → agregar **Latin American** (LA). Activarlo con la bandera del menu bar o `Cmd+Space → Switch Input Source`.

### 2. Keyboard Type — IMPORTANTE

Por defecto macOS asume **ANSI** para teclados USB nuevos. Eso hace que `KC_NUBS` no produzca `<`/`>` y que `LALT(KC_MINS)` no produzca `\`. Hay que cambiarlo manualmente a **ISO**:

1. Conectar solo el Sofle (desconectar otros teclados externos)
2. Abrir Terminal y ejecutar:
   ```bash
   open "/System/Library/CoreServices/Keyboard Setup Assistant.app"
   ```
   (Si no existe en esa ruta, buscar "Keyboard Setup Assistant" en Spotlight)
3. El wizard pide presionar la tecla a la derecha del Shift izquierdo y a la izquierda del Shift derecho
4. Al final muestra 3 opciones: ANSI / JIS / **ISO (International)** → **elegir ISO**
5. Click Done

Una vez configurado como ISO, no hay que volver a hacerlo — macOS lo recuerda por el VID/PID del teclado.

### Verifica tipeando

- Tecla a la derecha de `L` → `ñ`
- Tecla a la derecha de `ñ` → `´` (acento muerto; presiona `a` después para `á`)
- `AltGr + 2` → `@`
- `AltGr + E` → `€`
- En capa Lower: `<`, `>`, `|`, `\` desde el lado der

### Gotcha — Ghostty + zellij/neovim + dead keys (`, \, ^, ~, @)

En LATAM Mac ISO, los caracteres `` ` `` `\` `^` `~` `@` se producen con Option+tecla y muchos son **dead keys** (acentos muertos). macOS los procesa correctamente en Firefox, TextEdit, VS Code, etc. — pero Ghostty por default los traga.

El conflicto: el firmware del teclado tiene **KC_RALT en el thumb derecho** para que zellij/neovim reciban Alt como modificador (M-x). Si configuras Ghostty con `macos-option-as-alt = false`, los dead keys funcionan pero pierdes Alt. Si pones `true`, ganas Alt pero pierdes los dead keys.

**Solución**: usar `macos-option-as-alt = right` en `~/.config/ghostty/config`:

```
macos-option-as-alt = right
```

Eso le dice a Ghostty:
- **LEFT Option** (lo que envía el firmware al hacer `\`, `^`, `~`, `@`, `` ` ``) → pasa a macOS → dead keys procesados normalmente
- **RIGHT Option** (el `KC_RALT` físico del thumb derecho) → intercepta como Alt → zellij/neovim lo reciben

Para que esto funcione, **todos los macros del firmware usan `LALT()` consistentemente** para los caracteres LATAM Option. El thumb `KC_RALT` queda exclusivamente para Alt de terminal.

### Gotcha — Claude Desktop intercepta `\`

La app Claude Desktop tiene un atajo global asignado a `\` (abre asistente de captura). Si la app está activa, el primer `\` que envíes abrirá ese asistente en vez de tipear el carácter. Workarounds:

- Desactivar el atajo: Claude Desktop → Settings → Shortcuts
- O cerrar el asistente cuando aparece: las pulsaciones siguientes de `\` ya van al campo activo

## Build

### Build local (requiere toolchain AVR)

```bash
brew install qmk/qmk/qmk
qmk setup
qmk config user.overlay_dir="$(pwd)"
qmk compile -kb sofle/rev1 -km gonzafg2
```

El `.hex` queda en `~/qmk_firmware/sofle_rev1_gonzafg2.hex`.

### Build CI (recomendado)

Haz push a `main` → GitHub Actions corre `qmk_userspace_build.yml` + `qmk_userspace_publish.yml` → el release `latest` se actualiza con el `.hex` adjunto.

## Flash (cómo subir el firmware al teclado)

1. Baja `sofle_rev1_gonzafg2.hex` del [release latest](https://github.com/gonzafg2/qmk-userspace-sofle/releases/tag/latest)
2. Conecta una mitad a flashear vía USB-C (parte por la mitad que normalmente va al PC)
3. Pon esa mitad en **modo bootloader**:
   - Opción A: doble-click rápido al botón `RESET` del Pro Micro (al lado del switch de 3 posiciones)
   - Opción B: cortocircuita los pads `GND` y `RST` con un clip metálico
4. Usa [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (abre el `.hex` → click `Flash`) o desde terminal:
   ```bash
   qmk flash -kb sofle/rev1 -km gonzafg2
   ```
5. Repite los pasos 2-4 con la otra mitad

### Troubleshooting

- **El Pro Micro no aparece en QMK Toolbox**: probablemente no entró a bootloader. Vuelve a hacer doble-click rápido al reset (ventana de 750ms).
- **Una mitad funciona, la otra no escribe**: la mitad que no funciona quedó en bootloader o no terminó de flashearse. Vuelve a flashearla.
- **Los OLEDs se ven al revés**: revisa `OLED_ROTATION_270` en `keymap.c`. Si lo cambias, recompila y reflashea.
- **Las dos mitades no se comunican (master tipea pero slave no manda nada)**: revisa el cable TRRS, que esté bien conectado en ambos lados.

## Features deshabilitadas (trade-offs AVR)

El ATmega32U4 tiene 28KB usables. Build actual está al **~99%** (muy cerca del límite — el número exacto cambia con cada feature y aparece en el output de `qmk compile`). Para llegar a este balance se sacrificó:

| Feature | Estado | Por qué se quitó |
|---|---|---|
| `VIA_ENABLE` | `no` | ~2.5 KB para Luna pet (sesión 2026-05-21) |
| `WPM_ENABLE` | `no` | ~500 B para meter `RGB_MATRIX_ENABLE` (sesión 2026-05-22). Luna ya no reacciona a velocidad de tipeo, cicla por timer fijo |
| `SPLIT_LAYER_STATE_ENABLE` | `no` | ~130 B para meter STARLIGHT como 5to efecto RGB. Sin impacto visible (slave no muestra capa por OLED ni RGB indicators) |
| `SPLIT_TRANSPORT_MIRROR`, `SPLIT_OLED_ENABLE`, `SPLIT_MODS_ENABLE`, `SPLIT_LED_STATE_ENABLE` | `no` | Build excedía 28KB en sesión inicial |

**Para revertir algún sacrificio**: hay que liberar el equivalente quitando otra feature. Las opciones más pesadas que aún siguen activas son `MOUSEKEY_ENABLE` (~700 B) y `RGB_MATRIX_ENABLE` (~3 KB).

## Diferencias vs Corne (ZMK)

| | Corne (ZMK / nice!nano BLE) | Sofle (QMK / Pro Micro USB-C) |
|---|---|---|
| Layout | devicetree `.keymap` | C arrays `LAYOUT(...)` |
| Hold-tap | `&mt`, `&lt`, `lt_fast` behaviors | `LT()`, `MT()` macros |
| Macros `=>`, `&&`, etc. | `behavior-macro` con keycodes LATAM | `tap_code16` con keycodes LATAM (mismo principio) |
| Mod-morph BSPC/DEL | `behavior-mod-morph` | handler en `process_record_user` |
| Combos | `combos` node | `combo_t key_combos[]` |
| Capa Adjust | conditional layers tienen bug, se accede via hold ESC o combo TAB+BSDL | tri-layer manual con flag (preserva LT) + hold ESC |
| Mouse layer | `tog 4` desde Adjust (solo persistente) | hold encoder izq (momentary) + tap TG desde Adjust (persistente) |
| Editor runtime | ZMK Studio | VIA web |
| Fila numérica | Solo en Lower (42 keys) | **En Base** (58 keys) |
| Thumbs por lado | 3 | **5** (más mods + Tab/Bspc dedicados) |
| Bluetooth | `&bt BT_SEL N` | N/A (cableado) |

## Referencias

- [Sofle original (Josef Adamcik)](https://github.com/josefadamcik/SofleKeyboard)
- [Sofle RGB (Dane Evans)](https://github.com/devevans/sofle)
- [Tienda ZoneKeyboards Chile](https://zonekeyboards.cl/keyboards/sofle-rgb-zk)
- [QMK Userspace docs](https://docs.qmk.fm/newbs_external_userspace)
- [zmk-config-corne (repo hermano)](https://github.com/gonzafg2/zmk-config-corne)
