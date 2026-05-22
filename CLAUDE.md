# CLAUDE.md

Guía para Claude Code al trabajar con este repo.

## Antes de empezar — leer `claudedocs/`

Carpeta con el contexto persistente entre sesiones:

- [`claudedocs/session-context.md`](./claudedocs/session-context.md) — contexto general, estado actual, qué se hizo y qué quedó pendiente
- [`claudedocs/thumb-cluster-iteration.md`](./claudedocs/thumb-cluster-iteration.md) — discusión abierta sobre redundancia en el thumb cluster (doble Enter, LWR/RSE solos)
- [`claudedocs/decisions-log.md`](./claudedocs/decisions-log.md) — decisiones tomadas con su justificación (por qué QMK, por qué RGB OFF, por qué quitamos split features, etc.)
- [`claudedocs/hardware-notes.md`](./claudedocs/hardware-notes.md) — observaciones físicas del PCB (jumpers, pines, LEDs, controlador)

Al retomar trabajo, leer primero esos archivos para entender estado y contexto antes de editar código.

## Qué es

QMK Userspace para Sofle RGB ZK (Dane Evans, Pro Micro USB-C ATmega32U4, MX hotswap, 2 encoders, 2 OLEDs, RGB underglow SK6812 — actualmente OFF). Hermano del repo `zmk-config-corne`.

## Estructura

```
qmk-userspace-sofle/
├── qmk.json                                          # define build matrix
├── .github/workflows/build_binaries.yml              # CI oficial QMK userspace
├── users/gonzafg2/                                   # código compartido
│   ├── gonzafg2.{c,h}                                # custom keycodes, macros
│   ├── config.h                                      # tapping term, defines varios
│   └── rules.mk                                      # features comunes
└── keyboards/sofle/keymaps/gonzafg2/                 # keymap específico
    ├── keymap.c                                      # capas + encoder map + OLED
    ├── config.h                                      # OLED, split, RGB
    └── rules.mk                                      # OLED, ENCODER, RGB, VIA
```

## Comandos

```bash
# Build local (requiere brew install qmk/qmk/qmk)
qmk compile -kb sofle/rev1 -km gonzafg2

# Flash directo (con keyboard en bootloader mode)
qmk flash -kb sofle/rev1 -km gonzafg2

# CI: push a main → artifacts en GitHub Actions
```

## Convenciones de capas

| ID | Nombre | Trigger | Uso |
|---|---|---|---|
| 0 | `_BASE` | siempre | QWERTY LATAM + fila numérica |
| 1 | `_LOWER` | hold thumb izq | numpad, F-keys, símbolos |
| 2 | `_RAISE` | hold thumb der | operadores prog, navegación |
| 3 | `_ADJUST` | hold ESC ó tri-layer LWR+RSE | sistema, media, RGB, mouse toggle |
| 4 | `_MOUSE` | hold LSFT ó toggle Adjust | mouse + scroll |

## Custom keycodes (definidos en `users/gonzafg2/gonzafg2.h`)

Prefijo `GFG_` para no chocar con keycodes mainline. Implementados en `process_record_user` de `gonzafg2.c` con `SEND_STRING`.

- Operadores: `GFG_ARROW`, `GFG_SPREAD`, `GFG_EQEQ`, `GFG_NEQ`, `GFG_TEQ`, `GFG_AND`, `GFG_OR`, `GFG_PLEQ`, `GFG_MIEQ`
- Macros macOS: `GFG_SCRF/A/T`, `GFG_LOCK`, `GFG_FQUIT`
- Mod-morph: `GFG_BSDL` (BS por default, Del con shift)
- Helpers de capa: `GFG_LWR`, `GFG_RSE`, `GFG_ADJ`, `GFG_ESCAD`, `GFG_SFTMS`, `GFG_LWRENT`, `GFG_RSEENT`

## Convenciones al editar

- Editar capas en `keymaps/gonzafg2/keymap.c` (no en `users/`)
- Agregar custom keycodes nuevos al enum en `gonzafg2.h` y handler en `gonzafg2.c`
- Cambios en encoder por capa: `encoder_map[]` al final de `keymap.c`
- OLED: funciones al final de `keymap.c`, master vs slave en `oled_task_user`
- Si tocás `rules.mk` y agregás features nuevas, revisa que no rompan tamaño AVR (32KB flash límite)

## Validar antes de commit

```bash
qmk compile -kb sofle/rev1 -km gonzafg2
```

Si falla por tamaño AVR, deshabilita features en `rules.mk` (orden de costo: `RGB_MATRIX > VIA > OLED > MOUSEKEY > COMBO`).

## Diferencias clave vs Corne (ZMK)

| Concepto | ZMK (Corne) | QMK (Sofle) |
|---|---|---|
| Layout | devicetree `.keymap` | C arrays `LAYOUT(...)` |
| Hold-tap | `&mt`, `&lt` behaviors | `LT()`, `MT()` macros |
| Macro tipo `=>` | `behavior-macro` | `SEND_STRING("=>")` |
| Mod-morph | `behavior-mod-morph` | manual en `process_record_user` |
| Combos | `combos` node | `combo_t key_combos[]` |
| BT | `&bt BT_SEL N` | N/A (cableado) |
| Studio | `studio_unlock` | VIA (`VIA_ENABLE=yes`) |
| Sleep/power | `CONFIG_ZMK_SLEEP` | N/A (USB power) |
