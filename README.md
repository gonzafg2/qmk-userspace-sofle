# QMK Userspace · Sofle RGB ZK (gonzafg2)

Configuración QMK para teclado **Sofle RGB** (ZoneKeyboards, PCB original de Dane Evans) con Pro Micro USB-C ATmega32U4, switches MX, 2 encoders rotatorios, 2 OLEDs y RGB underglow. Pensado para **macOS con layout Spanish ISO LATAM**.

Sigue la estructura oficial **QMK Userspace** — keymap mantenido fuera del fork de `qmk_firmware`, build automatizado por GitHub Actions.

Hermano del repo [zmk-config-corne](https://github.com/gonzafg2/zmk-config-corne) — mismo flujo de capas y macros adaptados a hardware cableado QMK.

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

## Capas

### Base — QWERTY LATAM macOS

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  1  │  2  │  3  │  4  │  5  │                              │  6  │  7  │  8  │  9  │  0  │ DEL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  Q  │  W  │  E  │  R  │  T  │                              │  Y  │  U  │  I  │  O  │  P  │BSDL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │  A  │  S  │  D  │  F  │  G  │                              │  H  │  J  │  K  │  L  │  Ñ  │  ´  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CTRL │  Z  │  X  │  C  │  V  │  B  │MUTE │  ◉vol    scrl◉   │LOCK │  N  │  M  │  ,  │  .  │  -  │ ESC │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ ALT │ LWR │LWR/ │SFT/ │        │ SPC │RSE/ │ RSE │ALTGR│ GUI │
                  │     │     │     │ ENT │MOUS │        │     │ ENT │     │     │     │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
```

### Lower — numpad + símbolos LATAM

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │ F1  │ F2  │ F3  │ F4  │ F5  │                              │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  7  │  8  │  9  │  /  │  *  │                              │  (  │  )  │  \  │  !  │  ?  │BSDL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │  4  │  5  │  6  │  +  │  -  │                              │  {  │  }  │  ~  │  '  │  "  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CTRL │  1  │  2  │  3  │  .  │  0  │BRDN │ ◉brillo scrlH◉   │BRUP │  [  │  ]  │  <  │  >  │  |  │  _  │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ ALT │  ▼  │ ENT │ SFT │        │ SPC │ ENT │ RSE │ALTGR│ GUI │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                    ▲ activa
```

### Raise — operadores programación + navegación

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │ F12 │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  !  │  @  │  #  │  $  │  %  │                              │     │ RPT │     │     │ +=  │BSDL │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │  ^  │     │  &  │ &&  │ ||  │                              │  ←  │  ↓  │  ↑  │  →  │ -=  │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CTRL │ =>  │ ... │ ==  │ !== │ === │MUTE │ ◉tab     word◉   │LOCK │HOME │PGDN │PGUP │ END │     │ ESC │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ ALT │ LWR │ ENT │ SFT │        │ SPC │ ENT │  ▼  │ALTGR│ GUI │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                                                       ▲ activa

RPT = repite la última tecla pulsada (QK_REP)
```

### Adjust — sistema, media, mouse-toggle

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BOOT │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │SCRF │SCRA │SCRT │LOCK │FQT  │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │MOUSE│VOL- │MUTE │VOL+ │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │MUTE │ ◉track  brillo◉  │LOCK │     │PREV │PLAY │NEXT │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ ALT │ LWR │ ENT │ SFT │        │ SPC │ ENT │ RSE │ALTGR│ GUI │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘

BOOT = QK_BOOT (entra a bootloader)        MOUSE = toggle capa Mouse
SCRF/A/T = screenshots macOS               LOCK = Cmd+Ctrl+Q
FQT = Force Quit (Cmd+Alt+Esc)
```

> Acceso: **hold ESC** (esquina inf. der. de Base) o **combo TAB + BSDL**.

### Mouse — movimiento + scroll + click

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                              ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │                              │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │                              │     │ ←M  │ ↓M  │ ↑M  │ →M  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                              ├─────┼─────┼─────┼─────┼─────┼─────┤
│ SFT │     │     │     │     │     │                              │     │ ←S  │ ↓S  │ ↑S  │ →S  │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐                  ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CTRL │     │     │     │     │     │MUTE │  ◉scrlV scrlH◉   │LOCK │     │BTN1 │BTN3 │BTN2 │     │EXIT │
└─────┴─────┴─────┼─────┼─────┼─────┴─────┴─────┐        ┌───┴─────┴─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ ALT │ LWR │ ENT │  ▼  │        │ SPC │ ENT │ RSE │ALTGR│ GUI │
                  └─────┴─────┴─────┴─────┴─────┘        └─────┴─────┴─────┴─────┴─────┘
                                          ▲ activa
M = Mouse movement (HJKL)       S = Scroll (mismas teclas)
BTN1/2/3 = click izq/der/medio  EXIT = volver a Base (toggle off)
```

> Acceso: **hold SFT** desde Base (tap-hold momentáneo) o **toggle MOUSE** desde Adjust (persistente).

---

## Tabla maestra · tap-hold

| Tecla | Tap | Hold | Notas |
|---|---|---|---|
| `ESC` (inf. der. Base) | Escape | Capa **Adjust** | layer-tap |
| `SFT` (col izq) | Left Shift | Capa **Mouse** | layer-tap |
| `LWR` (thumb izq col 3) | — | Capa **Lower** | momentary |
| `RSE` (thumb der col 3) | — | Capa **Raise** | momentary |
| `LWR/ENT` (thumb izq col 4) | Enter | Capa **Lower** | layer-tap |
| `RSE/ENT` (thumb der col 4) | Enter | Capa **Raise** | layer-tap |
| `BSDL` (sup. der.) | Backspace | (con Shift) → Delete | mod-morph |
| `ALTGR` (thumb der col 4 desde el medio) | RAlt → habilita `¿ ¡ @ # €` en macOS ISO LATAM | — | — |

## Tabla · encoders por capa

| Capa | Encoder izq rotación / push | Encoder der rotación / push |
|---|---|---|
| Base | Volumen ± / Mute | Scroll vertical / Lock screen |
| Lower | Brillo ± / Mute | Scroll horizontal / Lock screen |
| Raise | Tab nav `⌘[` `⌘]` / Mute | Word nav `⌥←` `⌥→` / Lock screen |
| Adjust | Track prev / next / Mute | Brillo ± / Lock screen |
| Mouse | Scroll vertical / Mute | Scroll horizontal / Lock screen |

## Combos

| Combo | Acción |
|---|---|
| `F` + `J` (home row) | **Caps Word** — mayúsculas hasta espacio/enter |
| `TAB` + `BSDL` (esquinas sup.) | Acceso momentáneo a **Adjust** |

## Macros macOS (Adjust)

| Tecla | Acción |
|---|---|
| `SCRF` | Cmd+Shift+3 (screenshot completo) |
| `SCRA` | Cmd+Shift+4 (área) |
| `SCRT` | Cmd+Shift+5 (herramienta) |
| `LOCK` | Cmd+Ctrl+Q (lock screen) |
| `FQT` | Cmd+Alt+Esc (Force Quit) |

## Operadores de programación (Raise)

`=>` · `...` · `==` · `!==` · `===` · `&&` · `||` · `+=` · `-=`

Implementados con `SEND_STRING` en `users/gonzafg2/gonzafg2.c`.

## OLED

- **Mitad izquierda (master)**: logo `GFG` + capa actual + estado mods (CTRL/SHIFT) + WPM
- **Mitad derecha (slave)**: logo + texto "typing with Sofle"

## Setup macOS para LATAM

Como en el Corne, configurá macOS como **ISO Spanish** para que los símbolos coincidan con los keycodes QMK:

```
System Settings → Keyboard → Change Keyboard Type → ISO (European)
```

Verificá tipeando: `Ñ` y `´` deben funcionar; con AltGr (thumb der) → `¿ ¡ @ # €`.

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

Push a `main` → GitHub Actions corre `qmk_userspace_build.yml` + `qmk_userspace_publish.yml` → release `latest` con el `.hex` adjunto.

## Flash

1. Bajá `sofle_rev1_gonzafg2.hex` del [release latest](https://github.com/gonzafg2/qmk-userspace-sofle/releases/tag/latest)
2. Conectá la mitad a flashear via USB-C
3. Doble-click en el reset del Pro Micro (o cortocircuita GND-RST)
4. Usá [QMK Toolbox](https://github.com/qmk/qmk_toolbox) o `qmk flash -kb sofle/rev1 -km gonzafg2`
5. Repetí los pasos 2-4 con la otra mitad

## VIA

`VIA_ENABLE = yes` está activo. Sofle ya está soportado en [usevia.app](https://usevia.app). Los custom keycodes `GFG_*` aparecen como `Any` (hex) en VIA — reasignables manualmente con el código hex correspondiente.

## Diferencias vs Corne (ZMK)

| | Corne (ZMK) | Sofle (QMK) |
|---|---|---|
| Layout | devicetree `.keymap` | C arrays `LAYOUT(...)` |
| Hold-tap | `&mt`, `&lt` behaviors | `LT()`, `MT()` macros |
| Macros `=>`, `&&`, etc. | `behavior-macro` | `SEND_STRING("=>")` |
| Mod-morph BSPC/DEL | `behavior-mod-morph` | handler manual en `process_record_user` |
| Combos | `combos` node | `combo_t key_combos[]` |
| Bluetooth | `&bt BT_SEL N` | N/A (cableado USB) |
| Editor runtime | ZMK Studio | VIA web |
| Fila numérica | Solo en Lower (42 keys) | **En Base** (58 keys) |
| Thumbs por lado | 3 | **5** |

## Referencias

- [Sofle original (Josef Adamcik)](https://github.com/josefadamcik/SofleKeyboard)
- [Sofle RGB (Dane Evans)](https://github.com/devevans/sofle)
- [Tienda ZoneKeyboards Chile](https://zonekeyboards.cl/keyboards/sofle-rgb-zk)
- [QMK Userspace docs](https://docs.qmk.fm/newbs_external_userspace)
