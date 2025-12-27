/**
 * @file components.h
 * @author Paul Johnson
 * @brief 
 */

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdint.h>

#include "ecs/components/ai_comp.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/consumable_comp.h"
#include "ecs/components/destructible_comp.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/equippable_comp.h"
#include "ecs/components/item_comp.h"
#include "ecs/components/name_comp.h"

#include "ecs/components/stats_comp.h"

#include "ecs/entity.h"

#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void component_init(void);

void component_add(entity_id_t entity);
void component_remove(entity_id_t entity);

#endif // COMPONENTS_H