/**
 * @file components.c
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/components.h"

 #include <arch/zxn.h>

#include "ecs/entity.h"

#include "ecs/components/PAGE50/attack_comp.h"
#include "ecs/components/PAGE50/contained_comp.h"
#include "ecs/components/PAGE50/container_comp.h"
#include "ecs/components/PAGE50/equippable_comp.h"
#include "ecs/components/PAGE50/equipped_comp.h"
#include "ecs/components/PAGE50/creature_comp.h"
#include "ecs/components/PAGE50/item_comp.h"
#include "ecs/components/PAGE50/location_comp.h"

#include "ecs/components/PAGE51/player_comp.h"
#include "ecs/components/PAGE51/renderable_comp.h"
#include "ecs/components/PAGE51/slots_comp.h"
#include "ecs/components/PAGE51/stats_comp.h"
#include "ecs/components/PAGE51/timer_comp.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void components_init(void)
{
    comp_location_init(); 
    comp_timer_init();
}

/* attack */
void comp_melee_add(entity_id_t entity, const attack_comp_t melee)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    melee_add(entity, melee);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

void comp_ranged_add(entity_id_t entity, const attack_comp_t attack)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    ranged_add(entity, attack);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_melee_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    melee_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_ranged_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    ranged_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* consuamble */
void comp_consumable_add(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    consumable_add(entity);

    ZXN_WRITE_MMU6(current_bank);
}

void comp_consumable_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    consumable_remove(entity);

    ZXN_WRITE_MMU6(current_bank);
}

/* contained */
void comp_contained_add(entity_id_t entity, entity_id_t container, entity_id_t next)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    contained_add(entity, container, next);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_contained_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    contained_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* container */
void  comp_container_add(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    container_add(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_container_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    container_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* creature */
void comp_creature_add(entity_id_t entity, creature_kind_t kind)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    creature_add(entity, kind);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_creature_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    creature_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* destructable */
void comp_destructable_add(entity_id_t entity, const destructable_comp_t destructable)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    destructable_add(entity, destructable);

    ZXN_WRITE_MMU6(current_bank);

}

void comp_destructable_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     
    ZXN_WRITE_MMU6(PAGE_COMP_1);          

    destructable_remove(entity);

    ZXN_WRITE_MMU6(current_bank);           
}

/* effect */
void comp_effect_add(entity_id_t entity, effect_comp_t effect)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6(); 
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    effect_add(entity, effect);

    ZXN_WRITE_MMU6(current_bank);
}

void comp_effect_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6(); 
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    effect_remove(entity);

    ZXN_WRITE_MMU6(current_bank);
}

/* equippable */
void comp_equippable_add(entity_id_t entity, equippable_slot_t type)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    equippable_add(entity, type);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_equippable_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    equippable_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* equipped */
void comp_equipped_add(entity_id_t entity, entity_id_t equipped_by)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    equipped_add(entity, equipped_by);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_equipped_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    equipped_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* item */
void comp_item_add(entity_id_t entity, item_kind_t type, uint8_t quantity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    item_add(entity, type, quantity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_item_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    item_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* location */
void comp_location_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    location_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

void comp_location_add(entity_id_t entity, uint8_t x, uint8_t y)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    location_add(entity, x, y);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_location_move(entity_id_t entity, uint8_t x, uint8_t y)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    location_move(entity, x, y);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_location_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_COMP_1);          /* Page actions system into 8k MMU slot 6 */    

    location_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* name */
void comp_name_add(entity_id_t entity, name_id_t name)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    name_add(entity, name);

    ZXN_WRITE_MMU6(current_bank);
}

void comp_name_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    name_remove(entity);

    ZXN_WRITE_MMU6(current_bank); 
}

void system_name_print(text_window_t *win, name_id_t name)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMP_1);

    system_name_print(win, name);

    ZXN_WRITE_MMU6(current_bank);     
}

/* player */
void comp_player_add(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    player_add(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_player_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    player_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* renderable */
void comp_renderable_add(entity_id_t entity, const zxnext_tile_t tile)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    renderable_add(entity, tile);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_renderable_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    renderable_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* slots */
void comp_slots_add(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    slots_add(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_slots_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    slots_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* stats */
void comp_stats_add(entity_id_t entity, stats_comp_t stats_p)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    stats_add(entity, stats_p);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

void comp_stats_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    stats_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
}

/* timer */
void comp_timer_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    timer_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */ 
}

void comp_timer_add(entity_id_t entity, ticks_t ticks)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    timer_add(entity, ticks);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */        
}

void comp_timer_remove(entity_id_t entity)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_COMP_2);          /* Page actions system into 8k MMU slot 6 */    

    timer_remove(entity);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}

 /***************************************************
 * private functions
 ***************************************************/