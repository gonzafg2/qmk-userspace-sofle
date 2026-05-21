# Hardware — observaciones físicas del Sofle RGB ZK

Notas recopiladas de las fotos del PCB del usuario (sesión inicial). Útil para entender qué hay disponible y qué pin/feature usar al agregar capacidades.

## Identificación del PCB

- **Serigrafía visible**: `Power by Sofle RGB, Dane Evans` (parte inferior del PCB) + logo lagarto de ZoneKeyboards
- Significa: **PCB original de Dane Evans**, fabricado por ZK con su branding del lagarto. No es un re-diseño, es el mismo electrónicamente.
- Repo de referencia: https://github.com/devevans/sofle (NO el original de Josef Adamcik, que es `josefadamcik/SofleKeyboard`)
- **Compatible con `keyboards/sofle/rev1` de QMK mainline** (mismo pinout y matriz)

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
2. **RGB direccionable**: LEDs SK6812 5050 (4-pin, cuadrado blanco con cruz negra) intercalados
3. Jumper `Backlight enable` controla el backlight
4. Jumper `Ind bypass` para el indicator LED del Pro Micro

**No identificado**: pin exacto del data line RGB en el ATmega32U4 (probablemente D3 según convención Sofle/Dane Evans pero hay que confirmar con el esquemático).

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

## Posibles ampliaciones futuras

- **Activar RGB**: agregar override en `users/gonzafg2/config.h`:
  ```c
  #define WS2812_DI_PIN D3  // por confirmar
  #define RGBLED_NUM 70     // ~35 per side, contar SK6812 SMD del PCB
  ```
  Y `RGBLIGHT_ENABLE = yes` en rules.mk (revisar tamaño AVR, ~3KB extra).

- **Activar backlight blanco** (no direccionable): usar `BACKLIGHT_ENABLE = yes` y configurar `BACKLIGHT_PIN`.

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
