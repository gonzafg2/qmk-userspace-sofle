# QMK Userspace - Sofle RGB (gonzafg2)

Configuración QMK para teclado **Sofle RGB** (ZoneKeyboards, PCB Dane Evans) con Pro Micro USB-C ATmega32U4, switches MX, 2 encoders rotatorios, 2 OLEDs y RGB underglow. Pensado para **macOS con layout Spanish ISO LATAM**.

Sigue la estructura oficial **QMK Userspace** — keymap mantenido fuera del fork de `qmk_firmware`, build automatizado por GitHub Actions.

Hermana del repo [zmk-config-corne](https://github.com/gonzafg2/zmk-config-corne) (mismo flujo de capas y macros adaptados a hardware cableado QMK).

## Hardware confirmado

| Componente | Detalle |
|---|---|
| PCB | Sofle RGB by Dane Evans (fabricado por ZoneKeyboards Chile) |
| Controlador | Pro Micro clon USB-C, ATmega32U4 (5V) |
| Switches | MX hotswap (Gateron Blue + otros MX) |
| LEDs | RGB SK6812 direccionables + LEDs blancos backlight tradicional |
| Encoders | 2 rotatorios EC11 (uno por mitad), con push button |
| OLED | 2x SSD1306 128x32 vertical |
| Comunicación split | TRRS |
| Jumpers en PCB | `Light Sel BL/UND/&BL`, `Backlight enable`, `Ind bypass` |

## Capas

### Base
```
| ESC | 1 | 2 | 3 | 4 | 5 |                              | 6 | 7 | 8 | 9 | 0 | DEL |
| TAB | Q | W | E | R | T |                              | Y | U | I | O | P |BSDL |
|SHFT | A | S | D | F | G |                              | H | J | K | L | Ñ | ´   |
|CTRL | Z | X | C | V | B |MUTE|              |LOCK*    | N | M | , | . | - |ESC† |
       | GUI | ALT |LWR* |LWR/ENT* |SFT/MOUSE*|   |SPC|RSE/ENT*|RSE* |ALT |GUI |
                                            [Vol]    [Scroll]
```

- `BSDL`: tap = Backspace · Shift+tap = Delete (mod-morph en código)
- `ESC†`: tap = ESC · hold = Adjust
- `SFT/MOUSE`: tap = LSFT · hold = Mouse layer
- `LWR/ENT` y `RSE/ENT`: tap = Enter · hold = Lower/Raise
- `LOCK`: Cmd+Ctrl+Q (lock screen macOS)
- Encoder izq: volumen · Encoder der: scroll vertical

### Lower (numpad + símbolos)
```
| ESC | F1 | F2 | F3 | F4 | F5 |                       | F6 | F7 | F8 | F9 |F10 |F11 |
| TAB | 7  | 8  | 9  | /  | *  |                       | (  | )  | \  | !  | ?  |BSDL|
|SHFT | 4  | 5  | 6  | +  | -  |                       | {  | }  | ~  | '  | "  | `  |
|CTRL | 1  | 2  | 3  | .  | 0  |BRDN|         |BRUP   | [  | ]  | <  | >  | |  | _  |
```
Encoder izq: brillo · Encoder der: scroll horizontal

### Raise (operadores + navegación)
```
| ESC |F12 |    |    |    |    |                       |    |    |    |    |    |    |
| TAB |  ! |  @ |  # |  $ |  % |                       |    |RPT |    |    | += |BSDL|
|SHFT |  ^ |    |  & | && | || |                       |LEFT|DOWN| UP |RGHT| -= |    |
|CTRL | => |... | == | !==|=== |MUTE|         |LOCK   |HOME|PGDN|PGUP|END |    |ESC†|
```
Encoder izq: cambio tab (`Cmd+[`/`Cmd+]`) · Encoder der: word nav (`Alt+←`/`Alt+→`)

### Adjust (sistema, media, RGB)
```
|QK_BT|    |    |    |    |    |                       |    |    |    |    |    |    |
|     |SCRF|SCRA|SCRT|LOCK|FQT |                       |RGB |MOD |HUI |SAI |VAI |    |
|     |    |    |    |    |    |                       |MOUS|VOL-|MUTE|VOL+|    |    |
|     |    |    |    |    |    |    |         |       |    |PREV|PLAY|NEXT|    |    |
```
Encoder izq: RGB hue · Encoder der: RGB brightness

### Mouse (toggle desde Adjust)
HJKL en der = movimiento de cursor · `KC_WH_*` = scroll · BTN1/2/3 = clicks.

## Combos
| Combo | Acción |
|---|---|
| `F + J` (home row) | Caps Word |
| `TAB + BSDL` (esquinas superiores) | Adjust momentáneo |

## Macros macOS
- `SCRF` → Cmd+Shift+3 (full screenshot)
- `SCRA` → Cmd+Shift+4 (área)
- `SCRT` → Cmd+Shift+5 (herramienta)
- `LOCK` → Cmd+Ctrl+Q (lock screen)
- `FQUIT` → Cmd+Alt+Esc (force quit)

## Operadores programación (Raise)
`=>` · `...` · `==` · `!==` · `===` · `&&` · `||` · `+=` · `-=`

## OLED
- Mitad izquierda (master): logo + nombre + capa actual + estado mods + WPM
- Mitad derecha (slave): logo + "typing with Sofle"

## Setup macOS para layout LATAM correcto

Como en el Corne, hay que configurar macOS en modo **ISO Spanish** para que los símbolos LATAM (Ñ, `´`, `<`, `>`, `¿`) coincidan con los keycodes.

```
System Settings → Keyboard → Change Keyboard Type → ISO (European)
```

## Build local

Requiere toolchain AVR:
```bash
brew install qmk/qmk/qmk
qmk setup
qmk config user.overlay_dir="$(pwd)"
qmk compile -kb sofle/rev1 -km gonzafg2
```

El `.hex` queda en `~/qmk_firmware/sofle_rev1_gonzafg2.hex`.

## Build CI (recomendado)

Push a `main` → GitHub Actions corre `qmk_userspace_build.yml` y `qmk_userspace_publish.yml` → descargar artifact con el `.hex`.

## Flash

1. Conecta la mitad a flashear via USB-C
2. Doble-click rápido en el botón reset del Pro Micro (o cortocircuita GND-RST)
3. Usa [QMK Toolbox](https://github.com/qmk/qmk_toolbox) o:
   ```bash
   qmk flash -kb sofle/rev1 -km gonzafg2
   ```
4. Repetir para la otra mitad

> Tras flashear con `MOUSEKEY_ENABLE` por primera vez, el HID descriptor cambia. Si tenías parejas BLE/USB previas activas, pueden requerir re-detección.

## VIA

`VIA_ENABLE = yes` está activo. El Sofle ya está soportado en [usevia.app](https://usevia.app). Custom keycodes (macros `GFG_*`) aparecen como `Any` keys — para reasignarlas via VIA hay que usar el keycode hex directamente.

## Layout (capas no estándar)

El Sofle agrega vs Corne:
- **Fila numérica completa** en Base (en Corne estaba sólo en Lower)
- **Thumb extra interior** por lado → mapeado a `LSFT (hold = Mouse)` izq y `Enter (hold = Raise)` der
- **Encoder presses** (centro fila inferior) → `KC_MUTE` izq y macro `LOCK` der

## Referencias
- [Sofle original (Josef Adamcik)](https://github.com/josefadamcik/SofleKeyboard)
- [Sofle RGB (Dane Evans)](https://github.com/devevans/sofle)
- [Tienda ZoneKeyboards Chile](https://zonekeyboards.cl/keyboards/sofle-rgb-zk)
- [QMK Userspace docs](https://docs.qmk.fm/newbs_external_userspace)
