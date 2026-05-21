# QMK Userspace · Sofle RGB ZK (gonzafg2)

Configuración QMK para teclado **Sofle RGB** (ZoneKeyboards, PCB original de Dane Evans) con Pro Micro USB-C ATmega32U4, switches MX, 2 encoders rotatorios, 2 OLEDs y RGB underglow. Pensado para **macOS con layout Spanish ISO LATAM**.

Sigue la estructura oficial **QMK Userspace** — keymap mantenido fuera del fork de `qmk_firmware`, build automatizado por GitHub Actions.

Hermano del repo [zmk-config-corne](https://github.com/gonzafg2/zmk-config-corne) — mismo flujo de capas, macros y operadores prog, adaptado al stack QMK (cableado) en lugar de ZMK (BLE).

## Hardware confirmado

| Componente | Detalle |
|---|---|
| PCB | Sofle RGB by **Dane Evans** (fabricado por ZoneKeyboards Chile, ver "Power by Sofle RGB, Dane Evans" serigrafiado) |
| Controlador | Pro Micro clon **USB-C ATmega32U4 5V** |
| Switches | MX hotswap (Gateron Blue + otros MX, vástago cruz estándar) |
| LEDs | RGB SK6812 direccionables + LEDs blancos backlight tradicional (jumper `Light Sel` permite BL / UND / &BL) |
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
                                            o combo TAB+BSDL
```

| Capa | # | Activación | Tipo |
|---|---|---|---|
| Base | 0 | default | — |
| Lower | 1 | hold thumb izq col 4 | momentary |
| Raise | 2 | hold thumb der col 2 | momentary |
| Adjust | 3 | hold AMBOS Lower+Raise (tri-layer) **o** hold ESC pinky der **o** combo TAB+BSDL | momentary |
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
│ CMD │  Z  │  X  │  C  │  V  │  B  │MUTM │  ◉vol     scrl◉  │LOCK │  N  │  M  │  ,  │  .  │  -  │ESC/A│
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ CTL │ ALT │     │ LWR │ SPC │        │ ENT │ RSE │     │ALTGR│ CTL │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
```

`SFT` = Shift · `CMD` = Cmd (Mac) · `CTL` = Ctrl · `ALT` = Alt · `ALTGR` = AltGr (= RAlt en ISO LATAM)
`MUTM` = Play/Pause al tap, hold = capa Mouse · `LOCK` = Cmd+Ctrl+Q (lock pantalla) · `ESC/A` = Esc al tap, hold = capa Adjust

### Lower — numpad + símbolos LATAM

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ F1  │ F2  │ F3  │ F4  │ F5  │                              │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
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
│     │ F12 │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  !  │  @  │  #  │  $  │  %  │                              │     │ RPT │     │     │ +=  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  ^  │     │  &  │ &&  │ ||  │                              │  ←  │  ↓  │  ↑  │  →  │ -=  │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ =>  │ ... │ ==  │ !== │ === │     │ ◉tab     word◉   │     │HOME │PGDN │PGUP │ END │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │     │     │        │     │  ▼  │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                                                ▲ activa
```

`RPT` = `QK_REP` (repite la última tecla pulsada). Encoder izq cambia a tab nav (`⌘[` / `⌘]`), encoder der a word nav (`⌥←` / `⌥→`).

### Adjust — sistema, macros mac, media, RGB

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BOOT │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │SCRF │SCRA │SCRT │LOCK │FQT  │                              │TGMOU│     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │     │VOL- │MUTE │VOL+ │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │ ◉track  brillo◉  │     │     │PREV │PLAY │NEXT │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │  ▼  │     │        │     │  ▼  │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                          ▲ hold ambos LWR+RSE | hold ESC | combo TAB+BSDL
```

`BOOT` = `QK_BOOT` (entra a bootloader para flashear) · `SCRF/A/T` = screenshots mac (`⌘⇧3`/`4`/`5`)
`LOCK` = `⌘⌃Q` · `FQT` = Force Quit (`⌘⌥Esc`) · `TGMOU` = toggle capa Mouse persistente

### Mouse — movimiento + scroll + click

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │BTN1 │BTN3 │BTN2 │     │EXIT │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │     │ ←M  │ ↓M  │ ↑M  │ →M  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │     │     │     │     │     │                              │     │ ←S  │ ↓S  │ ↑S  │ →S  │     │
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
| Base | Volumen ± / **Play-Pause (tap), Mouse (hold)** | Scroll vertical / Lock pantalla |
| Lower | Brillo ± / Brillo down | Scroll horizontal / Brillo up |
| Raise | Tab nav `⌘[` `⌘]` / — | Word nav `⌥←` `⌥→` / Lock |
| Adjust | Track prev / next / — | Brillo ± / — |
| Mouse | Scroll vertical / — | Scroll horizontal / — |

## Combos

| Combo | Acción |
|---|---|
| `F` + `J` (home row) | **Caps Word** — mayúsculas hasta espacio/enter |
| `TAB` + `BSDL` (esquinas sup.) | Acceso momentáneo a **Adjust** |

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

`=>` · `...` · `==` · `!==` · `===` · `&&` · `||` · `+=` · `-=`

Implementados con `tap_code` y `tap_code16` enviando keycodes nativos LATAM (no `SEND_STRING` ASCII). Esto garantiza que `&&`, `||`, `=>`, etc. salgan correctos en macOS con teclado físico **ISO Spanish LATAM**.

## OLED

- **Mitad izquierda (master)**: logo `GFG` + capa actual (Base/Lwr/Rse/Adj/Mouse) + estado mods (CTRL/SHIFT)
- **Mitad derecha (slave)**: logo + texto "typing with Sofle"

## Setup macOS para LATAM

El teclado Sofle es **físicamente ANSI** (6 columnas por lado, 12 teclas por fila, sin la tecla extra del ISO). El firmware envía keycodes USB estándar que macOS interpreta según el layout configurado.

Para que los símbolos LATAM (ñ, ´, ¿, ¡, etc.) y los operadores prog (`<`, `>`, `=>`, `&&`, `||`) funcionen, configura **una** de estas opciones en `System Settings → Keyboard`:

| Opción | Input Source | Keyboard Type | Recomendado |
|---|---|---|---|
| **A** | `Spanish - ISO` | ANSI (default) | ✓ más simple |
| B | `Spanish (Latin America)` | ISO European | alternativa |

Ambas hacen que el keycode `KC_NUBS` se mapee a `<`/`>` (necesario para los operadores `=>`, `==`, etc.) y que `KC_SCLN` produzca `ñ`, `KC_LBRC` produzca `´`, etc.

Si ya tenías un teclado mecánico con macOS configurado para español LATAM (por ejemplo, vienes de un Corne), **probablemente ya tienes esto configurado** y no necesitas tocar nada.

### Verifica tipeando

- Tecla a la derecha de `L` → `ñ`
- Tecla a la derecha de `ñ` → `´` (acento muerto; presiona `a` después para `á`)
- `AltGr + 2` (thumb der col 4 + número 2) → `@`
- `AltGr + E` → `€`
- En capa Lower: `<` y `>` desde el lado der (col 3-4 fila 3)

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

## VIA

`VIA_ENABLE = yes` está activo. Sofle ya está soportado en [usevia.app](https://usevia.app). Los custom keycodes `GFG_*` (macros mac, operadores prog, BSDL) aparecen como `Any` (hex) en VIA — reasignables manualmente con el código hex correspondiente.

Para tener los `GFG_*` con nombre legible, habría que generar un `vial.json` custom (no implementado todavía).

## Diferencias vs Corne (ZMK)

| | Corne (ZMK / nice!nano BLE) | Sofle (QMK / Pro Micro USB-C) |
|---|---|---|
| Layout | devicetree `.keymap` | C arrays `LAYOUT(...)` |
| Hold-tap | `&mt`, `&lt`, `lt_fast` behaviors | `LT()`, `MT()` macros |
| Macros `=>`, `&&`, etc. | `behavior-macro` con keycodes LATAM | `tap_code16` con keycodes LATAM (mismo principio) |
| Mod-morph BSPC/DEL | `behavior-mod-morph` | handler en `process_record_user` |
| Combos | `combos` node | `combo_t key_combos[]` |
| Capa Adjust | conditional layers tienen bug, se accede via hold ESC o combo TAB+BSDL | `update_tri_layer_state` (funciona en QMK) + hold ESC + combo |
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
