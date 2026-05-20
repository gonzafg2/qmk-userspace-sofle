# Thumb cluster — iteración abierta

## Estado al cerrar la sesión

**Abierta**: el usuario detectó que hay **doble Enter** y le mostré que también hay redundancia en `LWR` y `RSE` "solos". Eligió ver 3 propuestas en diagrama; al ver la pregunta de selección pidió aclarar antes de elegir. Pendiente respuesta del usuario.

## El thumb cluster del Sofle (físico)

Cada mitad tiene **5 thumbs** + 1 encoder con push:
- Thumb 5 izq y Thumb 1 der son **altos verticales 1.5u** (`h: 1.5` en el `keyboard.json`) — posición de reposo del pulgar
- Los otros 4 thumbs son planos, alcanzables con desviación
- El encoder push es una tecla aparte (matrix `[4,5]` izq, `[9,5]` der) en la fila 4, no en la 5

## Layout actual (commit `09eaf80`)

```c
// Base layer, fila thumb (linea final del LAYOUT macro)
KC_LGUI, KC_LALT, GFG_LWR, GFG_LWRENT, GFG_SFTMS,    KC_SPC, GFG_RSEENT, GFG_RSE, KC_RALT, KC_RGUI
```

| Pos | Tecla | Tap | Hold |
|---|---|---|---|
| Izq 1 (externo) | GUI | Cmd | — |
| Izq 2 | ALT | Option | — |
| Izq 3 | LWR | — | Lower |
| Izq 4 | LWR/ENT | Enter | Lower |
| Izq 5 ⭐ reposo | SFT/MOUS | Shift | Mouse |
| Der 1 ⭐ reposo | SPC | Espacio | — |
| Der 2 | RSE/ENT | Enter | Raise |
| Der 3 | RSE | — | Raise |
| Der 4 | ALTGR | RAlt (LATAM) | — |
| Der 5 (externo) | GUI | Cmd der | — |

## Redundancias identificadas

1. **Doble Enter** — `LWR/ENT` (izq 4) y `RSE/ENT` (der 2) ambos producen Enter al tap. Útil ambidiestro pero gasta dos teclas en la misma función.
2. **Doble trigger Lower** — `LWR` (izq 3) y `LWR/ENT` (izq 4) ambos activan Lower al hold. El primero no tiene tap útil.
3. **Doble trigger Raise** — `RSE` (der 3) y `RSE/ENT` (der 2). Idem.

**Origen del problema**: heredé el diseño 1:1 del Corne (que tiene solo 3 thumbs por lado, donde `LWR` y `RSE` dedicados eran necesarios). Al replicar al Sofle con 5 thumbs, no aproveché las posiciones extra.

## 3 propuestas presentadas (sin elección aún)

### A · Status quo
Mantener actual. Doble Enter + LWR/RSE solos redundantes.

```
┌─────┬─────┬─────┬─────┐  ┌─────┐  ┌─────┐  ┌─────┬─────┬─────┬─────┐
│ GUI │ ALT │ LWR │LWR/ │  │SFT/ │  │ SPC │  │RSE/ │ RSE │ALTGR│ GUI │
│     │     │     │ ENT │  │MOUS │  │     │  │ ENT │     │     │     │
└─────┴─────┴─────┴─────┘  └─────┘  └─────┘  └─────┴─────┴─────┴─────┘
```

### B · TAB y BSPC en pulgares (mínima invasión)
Reemplazar LWR solo → TAB, y RSE solo → BSDL. Mantener doble Enter.

```
┌─────┬─────┬─────┬─────┐  ┌─────┐  ┌─────┐  ┌─────┬─────┬─────┬─────┐
│ GUI │ ALT │ TAB │LWR/ │  │SFT/ │  │ SPC │  │RSE/ │BSDL │ALTGR│ GUI │
│     │     │     │ ENT │  │MOUS │  │     │  │ ENT │     │     │     │
└─────┴─────┴─────┴─────┘  └─────┘  └─────┘  └─────┴─────┴─────┴─────┘
```

Pros: edición más veloz (TAB/BSPC sin estirar meñique). Ambidiestro mantenido.

### C · Una sola Enter
Quitar doble Enter. Enter solo en der. Thumb izq col 4 queda como LWR puro (hold).

```
┌─────┬─────┬─────┬─────┐  ┌─────┐  ┌─────┐  ┌─────┬─────┬─────┬─────┐
│ GUI │ ALT │ TAB │ LWR │  │SFT/ │  │ SPC │  │RSE/ │BSDL │ALTGR│ GUI │
│     │     │     │hold │  │MOUS │  │     │  │ ENT │     │     │     │
└─────┴─────┴─────┴─────┘  └─────┘  └─────┘  └─────┴─────┴─────┴─────┘
```

Pros: menos ambigüedad muscle memory. Contras: pierdes Enter en mano izq.

## Cómo retomar

1. Releer este archivo
2. Preguntar al usuario si decidió entre A/B/C o quiere una alternativa
3. Si elige B o C: editar `keyboards/sofle/keymaps/gonzafg2/keymap.c` línea de thumb en `_BASE`; las capas `_LOWER`/`_RAISE`/`_ADJUST`/`_MOUSE` heredan via `_______` así que no requieren cambios
4. Verificar tamaño AVR tras el cambio (estamos cerca del límite de 28KB)
5. Push, validar CI, actualizar README

## Archivos a tocar si se acepta cambio

- `keyboards/sofle/keymaps/gonzafg2/keymap.c` — única línea del thumb row en `_BASE`
- `README.md` — diagramas de Base + tabla maestra tap-hold
- `users/gonzafg2/gonzafg2.h` — si se agregan nuevos custom keycodes (no necesario para B ni C)
