/**
 * @file target_mode.c
 * @author Paul Johnson
 * @brief
 * @copyright Copyright (c) 2025
 *
 */

#include "target_mode.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/spatial.h"
#include "game/global_state.h"
#include "game/map.h"

#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private types
 * ***************************************************/
typedef enum
{
    TARGET,
    CANCEL,
    CONTINUE
} input_result_t;

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

static void target_init(target_context_t *ctx);
static void render_target_mode(target_context_t *ctx);
static input_result_t handle_input(target_context_t *ctx, unsigned int key);
static void target_resolve(target_context_t *ctx);

/***************************************************
 * public functions
 ***************************************************/

void target_mode(target_context_t *ctx)
{
    unsigned int key;
    input_result_t r;

    target_init(ctx);

    do
    {
        render_target_mode(ctx);
        key = key_press();
        r = handle_input(ctx, key);
    } while (r == CONTINUE);

    if (r == TARGET)
        target_resolve(ctx);
}

static void target_init(target_context_t *ctx)
{
    ctx->cursor.x = ctx->source.x;
    ctx->cursor.y = ctx->source.y;

    ctx->target_selected = 0;
    ctx->selected_entity = ENTITY_ID_INVALID;
    ctx->selected_tile.x = COORD_INVALID_VALUE;
    ctx->selected_tile.y = COORD_INVALID_VALUE;
}

static input_result_t handle_input(target_context_t *ctx, unsigned int key)
{
    coord_t *c = &ctx->cursor;

    switch (key)
    {
    case KEY_DOWN:
        if (c->y + 1 < MAP_HEIGHT)
            c->y++;
        return CONTINUE;
    case KEY_UP:
        if (c->y > 0)
            c->y--;
        return CONTINUE;
    case KEY_LEFT:
        if (c->x > 0)
            c->x--;
        return CONTINUE;
    case KEY_RIGHT:
        if (c->x + 1 < MAP_WIDTH)
            c->x++;
        return CONTINUE;
    case KEY_L_T:
        return TARGET;
    }

    return CANCEL;
}

static void render_target_mode(target_context_t *ctx)
{

    line_stepper_t ls;
    uint8_t colour;

    line_stepper_init(&ls, ctx->source.x, ctx->source.y, ctx->cursor.x, ctx->cursor.y);

    map_render();

    colour = in_range(ctx->source, ctx->cursor, ctx->max_range)
                 ? PALETTE_TARGETING_VIS
                 : PALETTE_TARGETING_BLOCKED;

    while (line_stepper_step(&ls))
    {
        if (ctx->require_los)
        {
            if (is_opaque(ls.x0, ls.y0))
                colour = PALETTE_TARGETING_BLOCKED;
        }
        zxnext_tilemap_set_attr(ls.x0, ls.y0, colour);
    }
}

static void target_resolve(target_context_t *ctx)
{
    coord_t *c = &ctx->cursor;

    if (!in_range(ctx->source, ctx->cursor, ctx->max_range))
        return;

    if (ctx->filter == TARGET_FILTER_ENTITY)
    {
        entity_id_t e = map_get_first(c->x, c->y);
        if (e != ENTITY_ID_INVALID)
        {
            ctx->selected_entity = e;
            ctx->target_selected = 1;
        }
    }
    else if (ctx->filter == TARGET_FILTER_TILE)
    {
        ctx->selected_tile = *c;
        ctx->target_selected = 1;
    }
}