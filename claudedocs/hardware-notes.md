# Hardware — observaciones físicas del Sofle RGB ZK

Notas recopiladas de las fotos del PCB del usuario (sesión inicial). Útil para entender qué hay disponible y qué pin/feature usar al agregar capacidades.

## Identificación del PCB

- **Nombre comercial completo**: **Sofle RGB V2 Rev2.1** (confirmado por el usuario en sesión 2026-05-22)
- **Serigrafía visible**: `Power by Sofle RGB, Dane Evans` (parte inferior del PCB) + logo lagarto de ZoneKeyboards
- **Origen del diseño**: PCB v2.1 original de Josef Adamcik (https://github.com/josefadamcik/SofleKeyboard) con la modificación RGB de Dane Evans encima. ZK lo fabrica y le pone su branding del lagarto.
- **Compatible con `keyboards/sofle/rev1` de QMK mainline** (mismo pinout y matriz, mismo target QMK)

## Controlador

- Pro Micro clónico con **USB-C** (confirmado, foto del conector USB-C horizontal)
- Etiqueta visible: `5V 3.3V` y `VII` → **ATmega32U4 5V**
- Montado en sockets (no soldado directo) — se puede reemplazar
- Reset button presente al lado del switch de 3 posiciones

## Switches

- Tipo: **MX hotswap** (Kailh sockets)
- Muestras vistas: Gateron Blue (clicky) + otros MX blancos no identificados
- Stem cruz MX estándar (foto del switch fuera del PCB)

## LEDs

Mix de dos sistemas (jumper `Light Sel` selecciona cuál se alimenta):
1. **Backlight tradicional**: LEDs SMD blancos pequeños (3528-2pin) entre cada switch socket
2. **RGB direccionable**: **72 LEDs SK6812 MINI** total (36 per side): 58 per-key + 14 underglow
3. Jumper `Backlight enable` controla el backlight
4. Jumper `Ind bypass` para el indicator LED del Pro Micro

**Configuración RGB confirmada** (de `keyboards/sofle/info.json` mainline):
- Pin data line: **D3** (definido en mainline como `ws2812.pin`)
- `rgb_matrix.split_count = [36, 36]`
- `rgb_matrix.driver = ws2812`
- Layout completo (per-LED matrix coords + underglow flags) ya definido en mainline

**Implicación**: para activar RGB **no se necesitan defines** de pin/count/split en `config.h` del keymap. Solo defines estéticos (default mode, brightness, lista de efectos).

## Encoders

- 2× EC11 con push button (perilla dorada visible)
- Pines según `keyboard.json` de sofle/rev1: izq `F5/F4`, der `F4/F5` (cruzados por el split)
- Resolution=2 por default en mainline (no tocar)
- Push button: matrix `[4,5]` izq y `[9,5]` der

## OLEDs

- 2× SSD1306 128×32 en orientación vertical (módulo azul I2C de 4 pines: GND/VCC/SCL/SDA)
- Visible en foto inicial mostrando `QMK Firmware` boot screen + `Sofle LAYER Base`

## Comunicación split

- TRRS jack en cada mitad (visible en foto del controlador)
- Cable TRRS conecta las dos mitades

## Jumpers configurables

| Jumper | Función | Notas |
|---|---|---|
| `Light Sel` | BL / UND / BL&UND | Selecciona qué LEDs alimentar (backlight, underglow RGB, o ambos) |
| `Backlight enable` | ON/OFF | Habilita el backlight tradicional |
| `Ind bypass` | bypass / normal | Desconecta el LED indicator del Pro Micro |

## Configuración eléctrica (referencia rápida)

Del `keyboards/sofle/rev1/keyboard.json` de QMK mainline:

```json
"matrix_pins": {
    "cols": ["F6", "F7", "B1", "B3", "B2", "B6"],
    "rows": ["C6", "D7", "E6", "B4", "B5"]
},
"encoder": {
    "rotary": [{"pin_a": "F5", "pin_b": "F4", "resolution": 2}]
},
"split": {
    "encoder": {
        "right": {"rotary": [{"pin_a": "F4", "pin_b": "F5", "resolution": 2}]}
    }
}
```

## RGB Matrix activo (estado actual desde 2026-05-22)

`RGB_MATRIX_ENABLE = yes` en `keyboards/sofle/keymaps/gonzafg2/rules.mk`. Defines estéticos en `config.h` del keymap. Ver [decisions-log.md](./decisions-log.md) entrada del 2026-05-22 para detalle completo.

**Pre-requisito físico para que enciendan los LEDs**: jumper `Light Sel` del PCB debe estar en `UND` o `BL&UND`.

## Posibles ampliaciones futuras

- **Activar backlight blanco** (no direccionable): usar `BACKLIGHT_ENABLE = yes` y configurar `BACKLIGHT_PIN`. Atención: ocupa flash adicional y requiere jumper `Light Sel` en `BL` o `BL&UND`.

- **Recuperar WPM reactivo en Luna**: si se libera espacio (p.ej. quitando MOUSEKEY o efectos RGB), revertir `WPM_ENABLE = yes` + restaurar `render_luna()` original.

- **VIA con custom keycodes legibles**: generar `vial.json` para el repo (alternativa a VIA mainline).

## Restricciones de hardware

- **ATmega32U4 = 28KB usables** después del bootloader Caterina (32KB - 4KB bootloader)
- Build actual está cerca del límite — cada feature nueva requiere medir
- LTO (`LTO_ENABLE = yes`) ya activo para máximo compactado

## Defecto del Pro Micro USB-C clónico

**Problema confirmado**: el Pro Micro USB-C del Sofle ZK **no se prende ni enumera** cuando se conecta con cable USB-C ↔ USB-C directo al Mac mini M4 Pro 2024. **Funciona solo con adaptador USB-A** (cable USB-A↔USB-C, con USB-A del lado del Mac).

**Causa**: defecto conocido en clones chinos. Implementan el conector USB-C físicamente pero **omiten el resistor 5.1kΩ entre pines CC1/CC2 y GND**. Sin ese resistor, los Mac (Apple Silicon, spec USB-C estricta) no detectan al dispositivo y no entregan 5V por el puerto. Los puertos USB-A tradicionales siempre entregan 5V sin negociación CC, por eso el adaptador funciona como workaround.

**Workaround usado**: cable USB-A↔USB-C + adaptador USB-A en el Mac. Es la solución actual.

**Soluciones permanentes posibles** (para futuro, no necesarias ahora):
1. Soldar resistor SMD 5.1kΩ entre CC1/CC2 y GND del Pro Micro (modificación HW pequeña)
2. Reemplazar el Pro Micro por un controlador de marca confiable: Elite-C, SparkFun Pro Micro USB-C, KB2040, RP2040 Pro Micro
3. Seguir usando el adaptador A↔C indefinidamente (es perfectamente válido y no causa problemas funcionales)

**Implicación para flashear**: siempre conectar la mitad a flashear con adaptador USB-A → cable USB-A↔USB-C → teclado. No intentar cable C↔C directo, no funciona.

## Encoder push buttons no funcionan (cold joint diagnosticado)

**Síntoma confirmado** (sesión 2026-05-21): rotación de ambos encoders funciona OK en todas las capas; **el tap/hold del push button del encoder NO registra evento de matriz en ninguna capa**.

**Cómo se diagnosticó**: temporalmente se habilitó debug en master OLED que mostraba el último matrix event (`row,col` + hex del keycode) en filas 11-12. Resultados:
- `SPC` (thumb izq col 4) → `4,4` y `0x002C` ✓ (matrix [4,4] funciona)
- `,` (der) → `8,3` y `0x0036` ✓ (matrix [8,3] funciona)
- **Encoder push izq** (matrix [4,5]) → **OLED no se actualiza** (ningún evento)
- **Encoder push der** (matrix [9,5]) → **OLED no se actualiza** (ningún evento)

Como row 4 y row 9 funcionan (thumbs OK) y col 5 funciona (DEL, BSDL, LBRC, ESCAD OK), la intersección row 4×col 5 y row 9×col 5 (que son exactamente los encoder push) deberían funcionar — pero no llega señal eléctrica al pin del Pro Micro.

**Diagnóstico**: **cold joint** en los pines del switch del encoder. El switch interno EC11 funciona mecánicamente (se siente el click táctil) y los 5 puntos de soldadura están visibles, pero al menos uno de los dos pines del switch no hace contacto eléctrico con su pad del PCB.

**Soluciones por probabilidad**:
1. **Resoldar los 5 pines del encoder** con flux + estaño nuevo — resuelve cold joints invisibles
2. **Verificar con multímetro** (modo continuidad) entre los pads del switch presionando el encoder; si no hay continuidad eléctrica, switch defectuoso → reemplazar EC11
3. **Reemplazar el encoder completo** si los puntos anteriores no resuelven

**Estado firmware**: correcto. Los keycodes `GFG_MUTM` (Mute + Mouse layer hold) y `KC_MPLY` (Play/Pause) están asignados correctamente a las matrix positions [4,5] y [9,5]. Cuando se arregle el hardware, funcionarán sin necesidad de tocar firmware.
