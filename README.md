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
                                  ▲ también: hold ESC pinky der
```

| Capa | # | Activación | Tipo |
|---|---|---|---|
| Base | 0 | default | — |
| Lower | 1 | hold thumb izq col 4 | momentary |
| Raise | 2 | hold thumb der col 2 | momentary |
| Adjust | 3 | hold AMBOS Lower+Raise (tri-layer) **o** hold ESC pinky der | momentary |
| Mouse | 4 | hold encoder push izq (momentary) **o** tap TG_MOUSE en Adjust (persistente) | mixto |

Salir de Mouse persistente: tap **EXIT** (esquina sup der o esquina inf der dentro de Mouse).

### Convención de los diagramas

En los diagramas de Lower / Raise / Adjust / Mouse se usa esta notación para distinguir teclas asignadas en la capa de teclas heredadas de Base:

| Símbolo | Significado |
|---|---|
| `KEY` (sin corchetes) | Keycode asignado en esta capa (sobrescribe a Base) |
| `[KEY]` (entre corchetes) | Slot `_______` que **hereda** la tecla `KEY` de Base (no está sobrescrita) |
| Celda vacía | Slot que **no produce nada** en esta capa — se dibuja en blanco. Cubre dos casos equivalentes desde el punto de vista del usuario: `XXXXXXX` explícito en esta capa, o `_______` que hereda `XXXXXXX` desde Base (caso típico: thumbs externos en Raise/Adjust/Mouse) |
| `▼` | Thumb que estás **holdeando** ahora para activar esta capa |
| `[MUTM]` / `[PLAY]` | Encoder push heredado de Base (LT mouse / play) |

Abreviaciones por espacio en celdas de 5 chars: `[SFT]`=LSFT, `[CMD]`=LGUI, `[CTL]`=LCTL, `[ALT]`=LALT, `[AGR]`=AltGr, `[RCT]`=RCtl, `[BSD]`=BSDL mod-morph, `[E/A]`=ESC tap/Adjust hold.

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
│[TAB]│  7  │  8  │  9  │  /  │  *  │                              │  (  │  )  │  \  │  !  │  ?  │[BSD]│
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│[SFT]│  4  │  5  │  6  │  +  │  -  │                              │  {  │  }  │  ~  │  '  │  "  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│[CMD]│  1  │  2  │  3  │  .  │  0  │BRDN │ ◉brillo   scrH◉  │BRUP │  [  │  ]  │  <  │  >  │  |  │  _  │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │[ALT]│[CTL]│  ▼  │[SPC]│        │[ENT]│[RSE]│[AGR]│[RCT]│     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                    ▲ activa
```

Encoder izq cambia a brillo, encoder der a scroll horizontal.

**Thumbs externos (cols 0 y 13 fila 4):** vacíos (`XXXXXXX`). Eran `KP=` / `KENT` hasta la sesión 2026-05-23 (sesión 5); se quitaron por bajo uso real — la calculadora se invoca con Spotlight y el Enter del numpad ya está cubierto por `[ENT]` heredado del thumb interior.

### Raise — operadores prog + navegación + window mgmt mac

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  =  │ >=  │ <=  │ ??  │ ?.  │ **  │                              │MCTL │APXP │SPCL │SPCR │ ZM- │ ZM+ │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│  ¿  │  ¡  │  @  │  #  │  $  │  %  │                              │SCRA │SCRT │LOCK │FQT  │ RPT │ ZM0 │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│[SFT]│  ^  │ +=  │ -=  │ &&  │ ||  │                              │  ←  │  ↓  │  ↑  │  →  │SPOT │EMJI │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│[CMD]│ =>  │ ... │ ==  │ !== │ === │[MUT]│ ◉tab     word◉   │[PLY]│HOME │PGDN │PGUP │ END │     │[E/A]│
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │[ALT]│[CTL]│[LWR]│[SPC]│        │[ENT]│  ▼  │[AGR]│[RCT]│     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                                                ▲ activa
```

**Operadores prog (mano izq):** `=` · `>=` · `<=` · `??` · `?.` · `**` (fila 1); `¿` · `¡` · `@` · `#` · `$` · `%` (fila 2); `^` · `+=` · `-=` · `&&` · `||` (fila 3); `=>` · `...` · `==` · `!==` · `===` (fila 4). Pinky col 0 fila 2: `¿` (apertura de pregunta LATAM), reemplaza el `JBk` que vivía ahí — se eliminó por bajo uso del workflow Neovim. Col 1 fila 2: `¡` (apertura de exclamación LATAM) reemplaza el `!` simple que sigue accesible en Lower. `[SFT]` y `[CMD]` se mantienen heredados porque son modifiers útiles mientras editas en Raise (Shift+arrow para selección, Cmd+arrow/Shift+arrow para navegación y selección por línea/archivo, Cmd+S/Z/C/V/F universales).

**Aperturas LATAM Mac (hipótesis del keycode, verificar al flashear):**

| Símbolo | Keycode propuesto | Razón |
|---|---|---|
| `¿` | `KC_EQL` | En layout Spanish - Latin American Mac, la tecla US `=` (scancode 0x2E) produce `¿` sin shift por convención ISO LATAM (fila numérica `' ¿` a la derecha del 0) |
| `¡` | `S(KC_EQL)` | Misma tecla con shift produce `¡` |

Si la hipótesis falla, alternativas a probar: `A(KC_1)` para `¡` (Option+1, layout Spanish ISO), `A(S(KC_1))` o `A(KC_SLSH)` para `¿`.

**Window/Spaces management mac (fila 1 mano der):**

| Label | Keycode | Acción macOS |
|---|---|---|
| `MCTL` | `LCTL(KC_UP)` | Mission Control |
| `APXP` | `LCTL(KC_DOWN)` | App Exposé |
| `SPCL` / `SPCR` | `LCTL(KC_LEFT)` / `LCTL(KC_RGHT)` | Space izquierda / derecha |
| `ZM-` / `ZM+` | `LGUI(KC_PMNS)` / `LGUI(KC_PPLS)` | Zoom out / Zoom in (en navegador, screenshare, IDE — verificar en LATAM Mac tras flasheo, si no funciona ajustamos con macro custom) |
| `ZM0` | `LGUI(KC_0)` | Zoom reset (Cmd+0) — fila 2 col 11, reemplaza el `[BSDL]` heredado |
| `SPOT` | `LGUI(KC_SPC)` | Spotlight (Cmd+Space, cómodo en home row der) |
| `EMJI` | `LGUI(LCTL(KC_SPC))` | Emoji & Symbol picker (Cmd+Ctrl+Space) — fila 3 col 11 al lado de SPOT |

> **Tip — cambio de Spaces se siente lento**: macOS anima el cambio de Space ~300 ms y el foco llega después. Si el problema es "cambias de Space y empiezas a tipear en el anterior", **no es del firmware** — es animación del OS. Hay dos formas de mitigarlo, con trade-off:
>
> - **Opción A — `Reduce Motion` ON** (search "reduce motion" en System Settings; en versiones recientes está en Accessibility → Motion o Display según release). Acelera dramáticamente el cambio de Space. **Trade-off**: estatiza también las animaciones del Liquid Glass (los widgets siguen translúcidos pero sin la refracción animada que les da el efecto "vivo"). Si te molesta visualmente, usa la Opción B.
> - **Opción B — Hack del Dock**: `defaults write com.apple.dock expose-animation-duration -float 0.05; killall Dock`. Acelera solo la animación de Mission Control / Spaces sin tocar Liquid Glass. **Trade-off**: en macOS reciente (Sequoia 15+ / Tahoe 26+) `killall Dock` puede no ser suficiente — quizás requiera **logout completo** (`osascript -e 'tell app "System Events" to log out'`) para que WindowServer recoja el cambio. Y aún así, en algunas versiones este setting ya no afecta al Space switching por keyboard shortcut. Si confirmás que no aplica, queda la Opción A.

**Macros mac sobre cursores (fila 2 mano der, movidas desde Adjust en sesión 2026-05-23):**

| Label | Keycode | Acción macOS |
|---|---|---|
| `SCRA` | `⌘⇧4` | Screenshot área |
| `SCRT` | `⌘⇧5` | Screenshot herramienta (Captura) |
| `LOCK` | `⌘⌃Q` | Lock pantalla |
| `FQT` | `⌘⌥Esc` | Force Quit |
| `RPT` | `QK_REP` | Repite la última tecla pulsada |

> `SCRF` (screenshot completo `⌘⇧3`) **eliminado** en la misma sesión: poco uso. Si lo necesitas, vuelve a agregarlo al enum y a `process_record_user` en `users/gonzafg2/`.

Encoder izq: tab nav (`⌘[` / `⌘]`). Encoder der: word nav (`⌥←` / `⌥→`).

### Adjust — sistema, media, mouse toggle, **RGB**

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BOOT │ TOG │ NXT │ HU+ │ SA+ │ VA+ │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SP+ │ SP- │ PRV │ HU- │ SA- │ VA- │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │TGMOU│     │VOL- │MUTE │VOL+ │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │[MUT]│ ◉track  brillo◉  │[PLY]│     │     │PREV │PLAY │NEXT │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │[ALT]│[CTL]│  ▼  │[SPC]│        │[ENT]│  ▼  │[AGR]│[RCT]│     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                          ▲ hold ambos LWR+RSE | hold ESC
```

**Cambios sesión 2026-05-23:**
- Las 5 macros mac (`SCRF`/`SCRA`/`SCRT`/`LOCK`/`FQT`) ya no viven en Adjust — `SCRF` eliminado, las otras 4 movidas a Raise sobre los cursores
- Media (VOL/MUTE y PREV/PLAY/NEXT) movido **una casilla a la derecha** (cols 7-9 → 8-10) para descansar en meñique extendido en vez de índice — más cómodo cuando llegas desde el thumb hold
- `TGMOU` bajado de fila 2 col 6 → fila 3 col 6 (sesión 4) para alinearse horizontalmente con el bloque de media (VOL/MUTE/VOL+) en la misma fila

**Sistema:**
`BOOT` = `QK_BOOT` (entra a bootloader para flashear) · `TGMOU` = toggle capa Mouse persistente

**Controles RGB (RGB_MATRIX, keycodes `RM_*`):**

| Tecla en Adjust | Keycode QMK | Hace |
|---|---|---|
| `TOG` | `RM_TOGG` | Encender / apagar RGB |
| `NXT` / `PRV` | `RM_NEXT` / `RM_PREV` | Siguiente / anterior efecto |
| `HU+` / `HU-` | `RM_HUEU` / `RM_HUED` | Tono (matiz) +/- |
| `SA+` / `SA-` | `RM_SATU` / `RM_SATD` | Saturación +/- (gris ↔ vivo) |
| `VA+` / `VA-` | `RM_VALU` / `RM_VALD` | Brillo +/- (tope a 150 por límite USB) |
| `SP+` / `SP-` | `RM_SPDU` / `RM_SPDD` | Velocidad animación +/- |

**5 efectos en el ciclo** (`NXT` cicla todos):

1. `RGB_MATRIX_SOLID_COLOR` *(always-on de QMK, no se puede deshabilitar; aparece como `RGB?` en el OLED)* — todo el teclado en un solo color fijo del HUE actual
2. `RGB_MATRIX_GRADIENT_LEFT_RIGHT` *(default al boot)* — gradient estático rojo→violeta de izq a der
3. `RGB_MATRIX_SOLID_MULTISPLASH` — ondas circulares un solo color (reactivo, sin BG idle)
4. **`MY_WAVE` (custom)** — ondas un solo color + **fondo idle pulsando (respiración)** del HUE actual
5. **`MY_RAIN` (custom)** — ondas arcoíris + **fondo idle pulsando (respiración)** del HUE actual

> **Histórico** — sesión 2026-05-23: removidos `RGB_MATRIX_STARLIGHT` (label `Star`) y `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` (label `Cros`) para liberar 846 B y habilitar `NKRO_ENABLE` (368 B). Ver [decisions-log.md](./claudedocs/decisions-log.md) para el diagnóstico completo del race condition de dead keys LATAM que motivó el cambio.

Los efectos custom están implementados en [`rgb_matrix_user.inc`](./keyboards/sofle/keymaps/gonzafg2/rgb_matrix_user.inc). El BG idle **late tipo corazón** (lub-dub + pausa) usando una lookup table piecewise de 32 frames × ~32ms = ciclo ~1 segundo (~60 BPM). Pico del lub: 88 (~35%); pico del dub: 70 (~28%); reposo: ~15-20 (~6-8%). El brillo total queda modulado por el VAL global.

**Pre-requisito físico**: jumper `Light Sel` del PCB debe estar en `UND` o `BL&UND` para alimentar los SK6812.

**Brillo limitado a 150/255 por hardware**: con 72 SK6812 al máximo del chip, el consumo excede el amperaje USB del Mac vía adaptador A↔C → undervolt → LEDs parpadean intermitentemente. No subir `RGB_MATRIX_MAXIMUM_BRIGHTNESS` sin una fuente USB con mejor amperaje.

### Mouse — movimiento + scroll + click

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │EXIT │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │BTN1 │BTN3 │BTN2 │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│[SFT]│     │     │     │     │     │                              │ ←M  │ ↓M  │ ↑M  │ →M  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│[CMD]│     │     │     │     │     │[MUT]│  ◉scrV    scrH◉  │[PLY]│ ←S  │ ↓S  │ ↑S  │ →S  │     │EXIT │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │[ALT]│[CTL]│[LWR]│[SPC]│        │[ENT]│[RSE]│[AGR]│[RCT]│     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
              ▲ hold encoder push izq (momentario) | tap TGMOU desde Adjust (persistente)
```

`M` = movimiento del cursor · `S` = scroll · `BTN1/2/3` = clic izq / medio / der · `EXIT` = `TG(_MOUSE)` apaga la capa

Mano izq mantiene Shift y Cmd para combos: Shift+click (selección), Cmd+click (abrir en nueva pestaña), Ctrl+click (menú contextual mac).

**Cascada de filas (sesión 2026-05-23):** botones BTN1/3/2 bajaron de fila 1 → fila 2; movimiento de fila 2 → fila 3; scroll de fila 3 → fila 4. Razón: la fila 1 quedaba muy alta para los dedos descansados, físicamente difícil de alcanzar. Ahora botones quedan en home row, movimiento en fila 3 (alcance natural del meñique-anular-medio-índice), scroll en fila 4.

**Alineación scroll (sesión 4 2026-05-23):** scroll movido de cols 9-12 → cols 8-11 en fila 4 para quedar alineado verticalmente con movimiento (fila 3 cols 6-9 físicas) y botones (fila 2 cols 6-8 físicas). Antes el scroll estaba desfasado un espacio a la derecha respecto a movimiento/botones.

**Precisión del movimiento (sesión 2026-05-23):** activado `MK_KINETIC_SPEED` en `users/gonzafg2/config.h` para movimiento smooth con momentum (más natural tipo trackpad). Parámetros tuneados: `MOUSEKEY_MOVE_DELTA 16` (default 25), `MOUSEKEY_INITIAL_SPEED 50` (default 100), `MOUSEKEY_BASE_SPEED 2000` (default 5000, bajado de 3000 en sesión 4 por feedback de aceleración muy rápida). Resultado: tap individual = ~16 px (preciso), hold acelera suavemente hasta 2000 px/s.

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

## Split — comunicación master ↔ slave

El Sofle es un teclado **split** con dos mitades comunicándose por TRRS. La mitad izquierda es la **master** (`MASTER_LEFT` en config); es la que se conecta por USB al Mac. La derecha es la **slave**.

**Cómo procesa pulsaciones:** la slave detecta una tecla apretada físicamente y manda solo "posición (fila, col) apretada" al master por TRRS. El master, que sabe en qué capa estás, traduce esa posición usando `keymaps[][][]` y manda el keycode resultante a USB. La slave **nunca conoce la capa** por default.

**`SPLIT_LAYER_STATE_ENABLE` (activado en sesión 2026-05-23 sesión 3):** sincroniza el `layer_state` (qué capa está activa) del master a la slave por TRRS. Costó **0 B** en este contexto por dividendos de LTO con otras features split presentes. Hoy no tiene efecto visible — habilita futuro:
1. Mostrar capa actual en el OLED de la slave (hoy solo muestra "Eres / un / Crack" + Luna pet estático)
2. RGB indicators per-capa en la slave (ej. cambiar color del thumb derecho según capa activa)
3. Cualquier feedback visual no-USB en la slave que dependa de la capa

## Caps Word

Doble tap rápido de **Shift** (LSFT) activa Caps Word — mayúsculas temporales hasta que pulses espacio, enter, tab o pase un timeout. Útil para escribir constantes (`MAX_RETRIES`) o acrónimos sin mantener Shift.

Activado vía `DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD` (built-in de QMK, sin overhead de `COMBO_ENABLE`).

## Macros macOS (Raise)

Implementadas con `tap_code16` LATAM-aware en `users/gonzafg2/gonzafg2.c`. **Movidas de Adjust a Raise en sesión 2026-05-23** (encima de los cursores) para acceso más rápido:

| Tecla | Acción |
|---|---|
| `SCRA` | `⌘⇧4` (screenshot área) |
| `SCRT` | `⌘⇧5` (screenshot herramienta) |
| `LOCK` | `⌘⌃Q` (lock pantalla) |
| `FQT` | `⌘⌥Esc` (Force Quit) |

`SCRF` (`⌘⇧3` screenshot completo) eliminado — poco uso. Si vuelve a hacer falta, agregarlo al enum `gfg_keycodes` en `gonzafg2.h` y al switch en `gonzafg2.c`.

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
Lower / Wave  fila 15    — capa actual O efecto RGB (ver abajo)
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
| `Wave` | `RGB_MATRIX_SOLID_MULTISPLASH` (ondas mono, sin BG idle) |
| `iWav` | `MY_WAVE` custom (ondas mono **+ BG idle pulsando**) |
| `iRai` | `MY_RAIN` custom (ondas arcoíris **+ BG idle pulsando**) |
| `RGB?` | `RGB_MATRIX_SOLID_COLOR` (always-on, sin label propio para ahorrar flash) |

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

### Tipeo rápido y dead keys (NKRO)

Si al escribir muy rápido en LATAM notabas que **´+vocal no producía la tilde** (ej. tipear "también" rápido salía "tambien" o "tambi´en"), era un race condition entre las dos mitades del split y el modo HID **6KRO** de QMK.

**Causa raíz**: la ´ (`KC_LBRC`) está en la mitad derecha; las vocales en la izquierda (master). Al teclear rápido, el evento de la ´ viaja por TRRS al master, y si llega dentro de la misma ventana de polling USB (~1 ms) que la siguiente vocal, ambos se reportan en un único reporte HID 6KRO sin orden claro. macOS no sabe cuál tecla vino primero y la dead key del layout LATAM no combina, dejando como si no hubieras apretado nada.

**Fix aplicado** (sesión 2026-05-23, ver [decisions-log.md](./claudedocs/decisions-log.md)):

- `NKRO_ENABLE = yes` + `FORCE_NKRO` → cambia el formato HID de array de 6 slots compartidos (6KRO) a bitmap con un bit por tecla (NKRO). Los reportes HID en ambos modos son **snapshots de estado** (no eventos ordenados), pero al no compartir slots, NKRO elimina la ambigüedad sobre qué tecla ocupa qué slot del array. Empíricamente esto resolvió el bug — la causa exacta probablemente combina la eliminación de esa ambigüedad con diferencias de timing/batching de reportes entre los dos modos en QMK. Costo: **368 B medidos**.
- `DEBOUNCE 8` (default QMK = 5) → margen extra anti-chatter. Costo: 0 B (es un define numérico).

El firmware arranca siempre en NKRO sin necesidad de hotkey de toggle. Si por alguna razón necesitas volver a 6KRO en una máquina con BIOS antiguo o KVM problemático, hay que recompilar quitando `FORCE_NKRO`.

**Verificación**: tipea palabras con tildes lo más rápido posible — "también", "tenía", "está", "más rápido", "véelo" — y todas las vocales acentuadas deberían salir consistentes.

## Build

### Build local (requiere toolchain AVR)

```bash
brew install qmk/qmk/qmk          # instala qmk + avr-gcc@8 como dependencia
qmk setup
qmk config user.overlay_dir="$(pwd)"
qmk compile -kb sofle/rev1 -km gonzafg2
```

El `.hex` queda en `~/qmk_firmware/sofle_rev1_gonzafg2.hex` y también en la raíz del userspace.

> **⚠️ Gotcha — `avr-gcc` no está en el PATH por default**
>
> Homebrew instala `avr-gcc@8` como **keg-only** (no se simbolinkea a `/opt/homebrew/bin`) porque su tap permite tener múltiples versiones coexistiendo. Resultado: `qmk compile` falla con `sh: avr-gcc: command not found` aunque el paquete esté instalado.
>
> **Fix persistente** — agregar a `~/.zshrc`:
> ```bash
> export PATH="/opt/homebrew/opt/avr-gcc@8/bin:/opt/homebrew/opt/avr-binutils/bin:$PATH"
> ```
>
> **Por qué fijar a la serie 8.x y no actualizar a versiones mayores**: QMK tiene problemas conocidos con `avr-gcc >= 9` (binarios 10-20% más grandes). Con el firmware al 97% del ATmega32U4, `avr-gcc 12+` muy probablemente no cabe. El CI oficial de QMK usa intencionalmente `avr-gcc 8.x`, y este repo documenta `8.5.0` como baseline en [`claudedocs/feature-weights.md`](./claudedocs/feature-weights.md). `brew upgrade avr-gcc@8` para parches dentro de 8.x es seguro.

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

El ATmega32U4 tiene 28672 bytes usables (`28KB - bootloader Caterina`). Build actual: **28170 / 28672 bytes (98%, 502 libres)** medidos con `avr-gcc 8.5.0` + LTO. Resultado de 3 sesiones del 2026-05-23:
1. **NKRO + DEBOUNCE 8** para fix de dead keys LATAM (368 B), quitando STARLIGHT + MULTICROSS para liberar 846 B
2. **Reorganización keymap Tech Lead** + `MK_KINETIC_SPEED` mouse (+150 B neto)
3. **`SPLIT_LAYER_STATE_ENABLE`** reactivado (0 B por LTO compartido), `CHORDAL_HOLD` probado y descartado (1236 B, no cabe + ROI marginal)

Para llegar a este balance se sacrificó:

| Feature | Estado | Por qué se quitó |
|---|---|---|
| `VIA_ENABLE` | `no` | ~2.5 KB para Luna pet (sesión 2026-05-21) |
| `WPM_ENABLE` | `no` | ~500 B para meter `RGB_MATRIX_ENABLE` (sesión 2026-05-22). Luna ya no reacciona a velocidad de tipeo, cicla por timer fijo |
| `SPLIT_LAYER_STATE_ENABLE` | `yes` (reactivado 2026-05-23) | Activado de nuevo, costo medido **0 B** (LTO comparte código con otras features split ya presentes). Habilita futuro mostrar capa en OLED slave o RGB indicators per-layer. |
| `ENABLE_RGB_MATRIX_STARLIGHT` (`Star`) | quitado 2026-05-23 | Liberar espacio para `NKRO_ENABLE` (368 B). Ver gotcha de tipeo rápido / dead keys arriba |
| `ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` (`Cros`) | quitado 2026-05-23 | Mismo motivo. Quitar **STARLIGHT + MULTICROSS + 2 cases OLED juntos** liberó **846 B medidos** — mucho más que la suma individual estimada (~320 B), porque LTO produce dividendos no-lineales cuando se eliminan varios efectos a la vez |
| `SPLIT_TRANSPORT_MIRROR`, `SPLIT_OLED_ENABLE`, `SPLIT_MODS_ENABLE`, `SPLIT_LED_STATE_ENABLE` | `no` | Build excedía 28KB en sesión inicial |

**Features activadas significativas (con peso medido en este build):**

| Feature | Estado | Peso | Notas |
|---|---|---|---|
| `RGB_MATRIX_ENABLE` + ws2812 + 5 efectos | `yes` | ~3000 B | El mayor consumidor del firmware |
| `OLED_ENABLE` + renderers custom | `yes` | ~2200 B | Logo GFG, capa, mods L/R, gata, Luna pet, indicador RGB |
| `MOUSEKEY_ENABLE` | `yes` | ~700 B | Necesario para la capa `_MOUSE` |
| `NKRO_ENABLE` + `FORCE_NKRO` | `yes` | **368 B** | Activado 2026-05-23 para resolver race condition de dead keys LATAM en split |
| `MK_KINETIC_SPEED` | `yes` | ~150 B | Activado 2026-05-23: modo mouse kinetic con momentum, más natural y preciso |
| `CAPS_WORD_ENABLE` | `yes` | ~250 B | Doble-tap Shift para CAPS WORD |
| `ENCODER_MAP_ENABLE` | `yes` | ~180 B | Encoder por capa declarativo |

**Para revertir algún sacrificio**: hay que liberar el equivalente quitando otra feature. Las opciones más pesadas activas son `RGB_MATRIX_ENABLE` (~3 KB) y `OLED_ENABLE` (~2.2 KB). Con los 502 B libres actuales puedes:

- ✅ Agregar 1 efecto RGB chico tipo `BREATHING` (~50 B)
- ✅ `SPLIT_LAYER_STATE_ENABLE` ya está activado (costó 0 B por LTO)
- ⚠️ `RAINBOW_MOVING_CHEVRON` (~150 B) ajustado pero entra
- ❌ `CHORDAL_HOLD` (probado 2026-05-23: pesó **1236 B**, no cabe — 3-4× más de lo que reporta la docs de QMK; ver `claudedocs/feature-weights.md` para el detalle)
- ❌ Reactivar `WPM_ENABLE` + `STARLIGHT` juntos (sumarían >630 B)
- ❌ Habilitar `VIA_ENABLE` (~2500 B, no cabe sin sacrificar RGB o OLED)
- ❌ `UNICODE_ENABLE` (~500-1000 B + conflicto con LATAM Input Source en macOS)

Catálogo completo de pesos medidos por feature en [`claudedocs/feature-weights.md`](./claudedocs/feature-weights.md), con descripción detallada de cada componente del firmware activo.

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
