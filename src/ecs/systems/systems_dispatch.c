/**
 * @file systems_dispatch.c
 * @author Paul  Johnson
 * @brief Game SYSTEMS_DISPATCH. Ensure parameters are not paged out of memory e.g. on stack or global game state
 */

#include "ecs/systems/systems_dispatch.h"

#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */
#include <stdarg.h>         /* va_list, va_start, va_end */

#include "ecs/components/stats_comp.h"
#include "ecs/components/attack_comp.h"

#include "core/zxnext.h"

#include "ecs/systems/PAGE30/monster_system.h"
#include "ecs/systems/PAGE32/item_system.h"
#include "ecs/systems/PAGE38/timer_system.h"
#include "ecs/systems/PAGE40/container_system.h"
#include "ecs/systems/PAGE42/event_system.h"
#include "ecs/systems/PAGE44/actions_system.h"
#include "ecs/systems/PAGE46/player_system.h"
#include "ecs/systems/PAGE48/equipment_system.h"
#include "ecs/systems/PAGE50/perception_system.h"
#include "ecs/systems/PAGE52/movement_system.h"
#include "ecs/systems/PAGE54/combat_system.h"
#include "ecs/systems/PAGE56/damage_system.h"
#include "ecs/systems/PAGE58/stats_system.h"
#include "ecs/systems/PAGE60/effect_system.h"
#include "ecs/systems/PAGE62/consumable_system.h"
#include "ecs/systems/PAGE64/name_system.h"
#include "ecs/systems/PAGE66/healing_system.h"
#include "ecs/systems/PAGE70/ai_system.h"
#include "ecs/systems/PAGE72/feature_system.h"
#include "ecs/systems/PAGE74/door_system.h"
#include "ecs/systems/PAGE74/transition_system.h"

#include "core/text.h"

#include "game/global_state.h"
#include "game/memory_map.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/

 void systems_init(void)
 {
    system_actions_init();
    system_combat_init();
    system_consumable_init();    
    system_container_init();
    system_damage_init();
    system_effect_init();
    system_equipment_init();
    system_event_init();
    system_monster_init();
    system_movement_init();
    system_player_init();
    system_stats_init();
    system_timer_init();
 }

/* AI System */
void system_ai_handle_event(const event_t *event)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_AI); 

    ai_system_handle_event(event);

    ZXN_WRITE_MMU6(current_bank);
}

void system_ai_process_entity_turn(entity_id_t id)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_AI); 

    ai_system_process_entity_turn(id);

    ZXN_WRITE_MMU6(current_bank);
}

 /* Actions system*/
 void system_actions_init(void)
 {

 }

bool system_actions_try_quaff(entity_id_t creature, entity_id_t item)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = actions_system_try_quaff(creature, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

bool system_actions_try_eat(entity_id_t creature, entity_id_t item)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = actions_system_try_eat(creature, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

bool system_actions_try_open(entity_id_t creature, entity_id_t feature)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = actions_system_try_open(creature, feature);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

bool system_actions_try_close(entity_id_t creature, entity_id_t feature)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = actions_system_try_close(creature, feature);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

 /* Container System */
void system_container_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

bool system_container_try_pickup(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;
    bool success;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    success = container_system_try_pickup(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return success;
}

bool system_container_try_drop(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;
    bool success;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    success = container_system_try_drop(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return success;
}

void system_container_add(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_add(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

void system_container_remove(entity_id_t item)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_remove(item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

uint8_t system_container_count(entity_id_t container)
{
    uint8_t current_bank;
    uint8_t count;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    count = container_system_count(container);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return count;
}
entity_id_t system_container_get_first(entity_id_t container)
{
    uint8_t current_bank;
    entity_id_t first;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    first = container_system_get_first(container);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return first;
}
entity_id_t system_container_get_next(entity_id_t entity)
{
    uint8_t current_bank;
    entity_id_t next;    

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    next = container_system_get_next(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return next;
}
entity_id_t system_container_get_at(entity_id_t container, uint8_t position)
{
    uint8_t current_bank;
    entity_id_t entity;    

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    entity = container_system_get_at(container, position);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return entity;
}

void system_container_mark_contents_for_destruction(entity_id_t container)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_mark_contents_for_destruction(container);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

void system_container_clean_up(entity_id_t id)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_clean_up(id);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

bool system_container_is_protected_by_persistence(entity_id_t id)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    result = container_system_is_protected_by_persistence(id);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

/* Consumable System*/
void system_consumable_init(void)
{

}

bool system_consumable_try_consume(entity_id_t actor, entity_id_t entity)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_CONSUMABLE_SYSTEM);

    result = consumable_system_try_consume(actor, entity);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}


/* Combat system */
void system_combat_init(void)
{

}

bool system_combat_try_attack(entity_id_t creature, entity_id_t target, attack_kind_t kind)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMBAT_SYSTEM);

    result = combat_system_try_attack(creature, target, kind);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}

uint8_t system_combat_attack_range(entity_id_t attacker, attack_kind_t kind)
{
    uint8_t current_bank;
    uint8_t result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMBAT_SYSTEM);

    result = combat_system_attack_range(attacker, kind);

    ZXN_WRITE_MMU6(current_bank);

    return result;    
}

/* Damage System*/
 void system_damage_init(void)
 {

 }

int8_t system_damage_try_take_damage(entity_id_t target, entity_id_t source, int8_t damage, damage_flag_t flag)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_DAMAGE_SYSTEM);

    result = damage_system_try_take_damage(target, source, damage, flag);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}

bool system_damage_try_kill(entity_id_t target, entity_id_t source)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_DAMAGE_SYSTEM);

    result = damage_system_try_kill(target, source);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}

bool system_door_try_open(entity_id_t actor, entity_id_t entity)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_DOOR_SYSTEM);

    result = door_system_try_open(actor, entity);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}

bool system_door_try_close(entity_id_t actor, entity_id_t entity)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_DOOR_SYSTEM);

    result = door_system_try_close(actor, entity);

    ZXN_WRITE_MMU6(current_bank);

    return result;
}

/* Effect System */
void system_effect_init(void)
{
    uint8_t mmu6_current_bank;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    effect_system_init();

    ZXN_WRITE_MMU6(mmu6_current_bank);
}

void system_effect_handle_event(const event_t *event)
{
    uint8_t mmu6_current_bank;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    effect_system_handle_event(event);

    ZXN_WRITE_MMU6(mmu6_current_bank);
}

void system_effect_process_entity_turn(entity_id_t entity)
{
    uint8_t mmu6_current_bank;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    effect_system_process_entity_turn(entity);

    ZXN_WRITE_MMU6(mmu6_current_bank);
}

int8_t system_effect_mod_sum(entity_id_t actor, attribute_t attribute)
{
    uint8_t mmu6_current_bank;
    uint8_t attribute_mod_sum = 0;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    attribute_mod_sum = effect_system_attribute_mod_sum(actor, attribute);

    ZXN_WRITE_MMU6(mmu6_current_bank);

    return attribute_mod_sum;
}

void system_effect_cleanup_entity(entity_id_t source)
{
    uint8_t mmu6_current_bank;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    effect_system_cleanup_entity(source);

    ZXN_WRITE_MMU6(mmu6_current_bank);
}

bool system_effect_has_condition(entity_id_t entity, condition_id_t condition)
{
    uint8_t mmu6_current_bank;
    bool result;

    mmu6_current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_EFFECT_SYSTEM_1);

    result = effect_system_has_condition(entity, condition);

    ZXN_WRITE_MMU6(mmu6_current_bank);

    return result;
}

/* Equipment System */
 void system_equipment_init(void)
 {

 }

bool system_equipment_try_equip(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = equipment_system_try_equip(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

bool system_equipment_try_unequip(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = equipment_system_try_unequip(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

bool system_equipment_is_equipped(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = equipment_system_is_equipped(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;
}

void system_equipment_cleanup(entity_id_t id)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    equipment_system_clean_up(id);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

/* Event System */
void system_event_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EVENT_SYSTEM);  /* Page event system into 8k MMU slot 6 */    

    event_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  
}

void system_event_emit(const event_t *event)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EVENT_SYSTEM);  /* Page event system into 8k MMU slot 6 */    

    event_system_emit(event);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  

}

/* Feature system*/
entity_id_t system_feature_create(feature_kind_t kind)
{
    entity_id_t entity;
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_FEATURE_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    entity = feature_system_create(kind);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */     

    return entity;    
}

/* Item system*/
entity_id_t system_item_create(item_kind_t kind, uint8_t quantity)
{
    entity_id_t entity;
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ITEM_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    entity = item_system_create(kind, quantity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */     

    return entity;
}

/* Healing System*/
int8_t system_healing_try_take_healing(entity_id_t actor, int8_t amount, healing_kind_t kind)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_HEALING_SYSTEM);

    result = healing_system_try(actor, amount, kind);

    ZXN_WRITE_MMU6(current_bank);         

    return result; 
}



/* Monster system*/
void system_monster_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MONSTER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    monster_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  
}

entity_id_t system_monster_create(creature_kind_t kind)
{
    entity_id_t entity;
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MONSTER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    entity = monster_system_create(kind);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */     

    return entity;
}

entity_id_t system_monster_create_player( void )
{
    entity_id_t entity;
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MONSTER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    entity = monster_system_create_player();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */     

    return entity;
}

/* Movement system */
void system_movement_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  

    movement_system_init();

    ZXN_WRITE_MMU6(current_bank);
}

void system_movement_place(entity_id_t actor, uint8_t x, uint8_t y)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  

    movement_system_place(actor, x, y);

    ZXN_WRITE_MMU6(current_bank);    
}

bool system_movement_try_move(entity_id_t id, int8_t dx, int8_t dy)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = movement_system_try_move(id, dx, dy);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;    
}

bool system_movement_try_move_random(entity_id_t actor)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = movement_system_try_move_random(actor);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;    
}

bool system_movement_try_move_towards(entity_id_t entity, coord_t *coord)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);

    result = movement_system_try_move_towards(entity, coord);

    ZXN_WRITE_MMU6(current_bank);

    return result;        
}

bool system_movement_location_equal(entity_id_t entity1, entity_id_t entity2)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = movement_system_location_equal(entity1, entity2);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;    
}

bool system_movement_are_adjacent(entity_id_t entity1, entity_id_t entity2)
{
    uint8_t current_bank;
    bool result;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    result = movement_system_are_adjacent(entity1, entity2);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return result;        
}

void system_movement_detach(entity_id_t id)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  

    movement_system_detach(id);

    ZXN_WRITE_MMU6(current_bank);    
}

/* Name system*/
void system_name_print(text_window_t *win, name_id_t name)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_NAME_SYSTEM);

    name_system_print(win, name);

    ZXN_WRITE_MMU6(current_bank);     
}

/* Player System */
void system_player_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_PLAYER_SYSTEM);  /* Page player system into 8k MMU slot 6 */    

    player_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

/* Perception system */
bool system_perception_try_check(entity_id_t creature)
{
    uint8_t current_bank;
    uint8_t result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_PERCEPTION_SYSTEM);

    result = perception_system_try_check(creature);

    ZXN_WRITE_MMU6(current_bank);

    return result; 
}

bool system_perception_can_see_target(entity_id_t ai, entity_id_t target)
{
    uint8_t current_bank;
    uint8_t result;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_PERCEPTION_SYSTEM);

    result = perception_system_can_see_target(ai, target);

    ZXN_WRITE_MMU6(current_bank);

    return result; 
}

void system_player_handle_event(const event_t *event)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_PLAYER_SYSTEM);  /* Page player system into 8k MMU slot 6 */    

    player_system_handle_event(event);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void system_player_update(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_PLAYER_SYSTEM);  /* Page player system into 8k MMU slot 6 */    

    player_system_update();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* Stats system */
void system_stats_init(void)
{

}

uint8_t system_stats_get_stat_cur(entity_id_t actor, stat_kind_t stat)
{
    uint8_t current_bank;
    uint8_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_stat_cur(actor, stat);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_stat_base(entity_id_t actor, stat_kind_t stat)
{
    uint8_t current_bank;
    int8_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_stat_base(actor, stat);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

int8_t system_stats_get_stat_modifier(entity_id_t actor, stat_kind_t stat)
{
    uint8_t current_bank;
    int8_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_stat_modifier(actor, stat);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_speed_cur(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_speed_cur(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_speed_base(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_speed_base(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_ac_cur(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_ac_cur(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_ac_base(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_ac_base(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_hp_cur(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_hp_cur(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_hp_max(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_hp_max(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;    
}

uint8_t system_stats_get_mp_cur(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_mp_cur(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;
}

uint8_t system_stats_get_mp_max(entity_id_t actor)
{
    uint8_t current_bank;
    speed_t value;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_STATS_SYSTEM);

    value = stats_system_get_mp_max(actor);

    ZXN_WRITE_MMU6(current_bank);

    return value;    
}

/* Timer system*/
void system_timer_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    timer_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  
}

void system_timer_update(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    timer_system_update();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

}

bool system_timer_has_fired(entity_id_t entity)
{
    uint8_t current_bank;
    bool fired;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);  

    fired = timer_system_has_fired(entity);

    ZXN_WRITE_MMU6(current_bank);       

    return fired;
}

void system_timer_reset(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);          

    timer_system_reset(entity);

    ZXN_WRITE_MMU6(current_bank);       
}

void system_timer_start(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);          

    timer_system_start(entity);

    ZXN_WRITE_MMU6(current_bank);
}

void system_timer_stop(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);          

    timer_system_stop(entity);

    ZXN_WRITE_MMU6(current_bank);

}

void system_timer_cleanup(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_TIMER_SYSTEM);          

    timer_system_cleanup(entity);

    ZXN_WRITE_MMU6(current_bank);         
}

/* Transition System */
void system_transition_try(entity_id_t source, entity_id_t target)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_TRANSITION_SYSTEM);

    transition_system_try(source, target);

    ZXN_WRITE_MMU6(current_bank);
}