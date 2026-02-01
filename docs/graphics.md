
Oh this is a *great* moment to stop future pain. A locked-down style guide will save you **months** of visual inconsistency and rework — especially on an 8-bit machine.

Below is a **Spectrum Next Roguelike Item Tileset Style Guide**, tuned specifically for:

* 8×8 tiles
* palette-swapped item colours
* classic roguelike readability
* low resolution + CRT friendliness
* future extensibility

---

# Spectrum Next Roguelike

## Item Tileset Style Guide (8×8)

---

## 1. Core Design Goals

All item tiles must:

1. Be **instantly readable at 1× scale**
2. Work under **palette swapping** (item recolouring)
3. Share a **consistent visual language**
4. Avoid reliance on colour alone
5. Look good on **real hardware** (blur + colour bleed)

---

## 2. Palette Rules (Hard Law)

### Background

* **Index 0** → transparent
  Never draw “background colour” pixels.

### Item colour ramp (recolourable)

* **Index 1** → light shade
* **Index 2** → main colour
* **Index 3** → dark shade

These **must always be treated as a single colour ramp**.

> If you recolour the item, **all three indices swap together**.

### Neutral colours (use sparingly)

* **Index 4** → black (outlines only)
* **Index 5–7** → greys (metal, stone, paper)
* **Index 8** → white (tiny highlights only)

⚠️ **Most items should avoid neutrals entirely** unless required by identity.

---

## 3. Shape First, Colour Second

Items must be identifiable by **silhouette alone**.

### Good silhouettes:

* Potion → round body + narrow neck
* Scroll → horizontal rectangle + rolled ends
* Ring → hollow circle
* Wand → long thin diagonal
* Weapon → asymmetric profile

### Bad silhouettes:

* Blob shapes
* Colour-only distinction
* Flat rectangles with no internal structure

**Test:**
If the tile is all one colour (index 2), it should *still* read.

---

## 4. Shading Rules (Very Important)

### Use a 3-tone ramp only

```
Light (1) → Main (2) → Dark (3)
```

### Allowed shading patterns

* Dark outline + main fill
* Dark bottom / light top
* Single-pixel highlight on curved surfaces

### Forbidden

* Checkerboard dithering
* Mid-tone noise
* Random pixels for “texture”

> Texture comes from **shape**, not noise.

---

## 5. Outlines & Edges

### General rule

* Items **do not need full black outlines**
* Prefer **dark shade (3)** for internal outlines

### When black (4) is allowed

* Sharp metal edges (sword tip)
* Hollow objects (rings)
* Rare emphasis (legendary items)

Even then:
**1 pixel max thickness**

---

## 6. Item Class Visual Language

Each item category has a *visual contract*.

### Potions

* Rounded
* Vertical symmetry
* Highlighted glass
* Colour = liquid

### Scrolls

* Horizontal
* Rolled ends
* Mostly neutral (greys)
* Tiny coloured seal or rune allowed

### Rings

* Circular or diamond outline
* Hollow center (transparent)
* Strong dark outline

### Wands

* Diagonal or vertical
* Thin profile
* Tip highlight

### Weapons

* Asymmetrical
* Clear handle + blade distinction
* Metal uses greys, not item colour

### Armour

* Chunky
* Mostly neutral
* Item colour used as trim or emblem

---

## 7. Pixel Density Rules

### Target fill

* **30–60% filled pixels**
* Avoid full 8×8 fill unless intentional

### Avoid

* Single isolated pixels
* Long straight lines without breaks
* Excessive diagonals

Spectrum Next pixels like **chunky geometry**.

---

## 8. Orientation & Alignment

* Prefer **centered** designs
* Vertical items slightly taller than wide
* Horizontal items slightly wider than tall
* Avoid touching tile edges unless needed for silhouette

---

## 9. Consistency Rules

All items must share:

* Same light direction (top-left)
* Same contrast level
* Same shading logic
* Same outline thickness

If one tile breaks a rule, **fix the tile**, not the rules.

---

## 10. Prompt Template (Use This Every Time)

When asking me to design a tile, use:

```
Design an 8×8 Spectrum Next roguelike item tile.

Item: <name>
Category: <potion / weapon / scroll / etc>

Palette rules:
Index 0: transparent
Index 1: light item shade
Index 2: main item colour
Index 3: dark item shade
(1–3 recolour together)

Constraints:
- Use indices {0,1,2,3} only
- Must read at 1× scale
- Classic roguelike style
- Shape-first, recolour-safe

Output:
- 8×8 grid of palette indices
- Brief explanation of silhouette and recolouring behavior
```

---

## 11. Final Sanity Check (Before Accepting a Tile)

Ask yourself:

* Can I recognise it in 0.5 seconds?
* Does it still read in monochrome?
* Does recolouring break nothing?
* Would this still look good on a CRT?

If yes → ship it 🚀

---

If you want, next we can:

* Design **canonical reference tiles** (potion, scroll, sword, ring)
* Create a **palette-swap test sheet**
* Define **monster tile rules** to match item style
* Lock down **terrain tiles** to the same visual grammar

You’re building this *right* — very Spectrum Next, very old-school, very solid.


Yes — terrain tiles absolutely need *their own* rules, and they’re **not the same rules as items**. If items are “objects you look at”, terrain is “space you read at a glance”.

Below is a **locked-down terrain tile style guide** that matches what you’re building on the Spectrum Next and plays nicely with your item rules.

---

# Spectrum Next Roguelike

## Terrain Tile Style Guide (8×8)

---

## 1. Core Purpose of Terrain Tiles

Terrain exists to answer **three questions instantly**:

1. Can I walk there?
2. Does it block vision?
3. Is it special (door, stairs, water, trap)?

Terrain must:

* Fade into the background
* Be readable in peripheral vision
* Never compete with items or actors

> Terrain is *information*, not decoration.

---

## 2. Palette Philosophy (Different From Items!)

### Terrain does NOT use the item recolour ramp

Terrain colours are **fixed** and semantic.

Suggested terrain palette usage:

* **Index 0** → transparent (rare; see below)
* **Indices 4–7** → blacks + greys (walls, floors)
* **Index 8** → white (highlights, doors, stairs)
* **One accent colour max** for special tiles

⚠️ Terrain tiles should **not** use indices 1–3 unless the tile is *functionally special* (stairs, portal, lava).

---

## 3. Floors vs Walls (The Big Readability Rule)

### Floors

* Low contrast
* Repeating texture
* No hard outlines
* Never pure black

### Walls

* High contrast
* Hard edges
* Clear blocking shape
* Usually darker than floors

**Player vision should “snap” to walls automatically.**

---

## 4. Floor Tile Design Rules

### Visual role

* Background texture
* Spatial continuity

### Rules

* 1–3 pixels of variation only
* Use **greys only**
* No outlines
* No symmetry required

### Example structure

* Mostly mid grey
* Occasional dark/light pixel
* No repeating obvious pattern every tile

> Floors should disappear once you stop looking directly at them.

---

## 5. Wall Tile Design Rules

### Visual role

* Impassable space
* Map structure

### Rules

* Strong silhouette
* Solid mass
* Minimal texture
* Darker than floors

### Typical construction

* 6–7 solid pixels wide
* Dark face
* Slight highlight on top or left

Avoid:

* Brick patterns
* High-frequency detail
* Noisy textures

---

## 6. Doors (Special Terrain)

Doors must read as:

* Passable (sometimes)
* Interactive
* Distinct from walls

### Rules

* Vertical rectangle
* Light interior
* Dark frame
* Closed doors block vision, open do not

Palette:

* Greys + white
* Optional accent pixel

---

## 7. Stairs & Level Transitions

These are **terrain + UI**, so they *may* break rules slightly.

### Rules

* High contrast
* Clear direction (up/down)
* Readable even under entities

Use:

* White highlights
* Dark shadow
* Optional accent colour

Stairs should pop **more than floor**, **less than items**.

---

## 8. Traps & Hazards

Traps are *terrain pretending to be floor*.

### Rules

* Floor-like base
* Subtle visual tell
* Same footprint as floor tile

Example cues:

* 1 pixel symbol
* Slight contrast shift
* Repeated motif across trap types

> Traps should be readable *after* you learn the game.

---

## 9. Transparency Rules

Terrain should almost never use transparency.

Exceptions:

* Pits
* Holes
* Chasms
* Overlays (webs, blood, scorch marks)

Transparent tiles must still read clearly against all floors.

---

## 10. Tile Adjacency & Tiling Strategy

Decide **early**:

### Option A — Simple tiles

* One tile per terrain type
* Fast, classic, clear
* Recommended for roguelikes

### Option B — Auto-tiling

* Edges and corners
* More code
* More tiles
* Risk of visual noise

For Spectrum Next:

> **Simple tiles + strong silhouettes** usually win.

---

## 11. Contrast Hierarchy (Critical)

From lowest to highest visual priority:

1. Floor
2. Wall
3. Special terrain (doors, stairs)
4. Items
5. Actors (player, monsters)

If terrain competes with actors → terrain is wrong.

---

## 12. Terrain Prompt Template

Use this when asking me for terrain tiles:

```
Design an 8×8 Spectrum Next roguelike terrain tile.

Tile: <floor / wall / door / stairs / trap>

Palette rules:
- Index 0: transparent (only if needed)
- Use greys (4–7) primarily
- White (8) for highlights only
- No item recolour ramp unless special

Constraints:
- Must read instantly at 1× scale
- Terrain-first, low noise
- Classic roguelike style
- Must not compete with items

Output:
- 8×8 grid of palette indices
- Brief explanation of readability and adjacency behavior
```

---

## 13. Golden Rule of Terrain

> If you notice the floor while fighting a monster, the floor is too loud.

---

If you want, next we can:

* Design **canonical floor + wall tiles**
* Create **stairs up/down pair**
* Define **trap iconography**
* Build a **terrain test room** to validate contrast

You’re doing exactly the right thing by separating item and terrain visual rules — this is how classic roguelikes stay readable for decades.

