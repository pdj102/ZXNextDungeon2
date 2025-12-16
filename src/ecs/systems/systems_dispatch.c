/**
 * @file systems_dispatch.c
 * @author Paul  Johnson
 * @brief Game SYSTEMS_DISPATCH
 */

#include "ecs/systems/systems_dispatch.h"

#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */

#include "core/zxnext.h"

#include "ecs/systems/PAGE30/monster_system.h"
#include "ecs/systems/PAGE32/item_system.h"
#include "ecs/systems/PAGE38/timer_system.h"
#include "ecs/systems/PAGE40/container_system.h"
#include "ecs/systems/PAGE42/event_system.h"
#include "ecs/systems/PAGE44/actions_system.h"
#include "ecs/systems/PAGE46/player_system.h"
#include "ecs/systems/PAGE48/equipment_system.h"
#include "ecs/systems/PAGE52/movement_system.h"

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
 * functions
 ***************************************************/

 void systems_init(void)
 {
    system_monster_init();
    system_item_init();
    system_timer_init();
    system_container_init();
    system_combat();
    system_event_init();
    system_actions_init();
    system_player_init();
    system_equipment_init();
 }

 /* Actions system*/
 void system_actions_init(void)
 {

 }

bool_t system_actions_try_quaff(entity_id_t creature, entity_id_t item)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_quaff(creature, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_actions_try_eat(entity_id_t creature, entity_id_t item)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_eat(creature, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_actions_try_open(entity_id_t creature, entity_id_t feature)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_open(creature, feature);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_actions_try_close(entity_id_t creature, entity_id_t feature)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_close(creature, feature);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

int8_t system_actions_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_take_damage(creature, damage, type);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_actions_try_die(entity_id_t creature)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ACTIONS_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = actions_system_try_die(creature);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
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

bool_t system_container_try_pickup(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;
    bool_t success;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    success = container_system_try_pickup(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return success;
}

bool_t system_container_try_drop(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;
    bool_t success;

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

void system_container_remove(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_remove(container, item);

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

/* Combat system */
void system_combat_init(void)
{

}

bool_t system_combat_try_melee_attack(entity_id_t creature, entity_id_t target)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_COMBAT_SYSTEM);

    status = combat_system_try_melee_attack(creature, target);

    ZXN_WRITE_MMU6(current_bank);

    return status;
}

/* Equipment System */
 void system_equipment_init(void)
 {

 }

bool_t system_equipment_try_equip(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = equipment_system_try_equip(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_equipment_try_unequip(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = equipment_system_try_unequip(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
}

bool_t system_equipment_is_equipped(entity_id_t actor, entity_id_t item)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EQUIPMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = equipment_system_is_equipped(actor, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;
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

void system_event_emit(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_EVENT_SYSTEM);  /* Page event system into 8k MMU slot 6 */    

    event_system_emit(type, src, tgt, val);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  

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

void system_player_update(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_PLAYER_SYSTEM);  /* Page player system into 8k MMU slot 6 */    

    player_system_update();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */    
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

bool_t system_timer_has_fired(entity_id_t entity)
{
    uint8_t current_bank;
    bool_t fired;

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

void system_monster_print_name(text_window_t *win, creature_kind_t kind)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MONSTER_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    monster_system_print_name(win, kind);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  

}

/* Movement system */
bool_t system_movement_try_move(entity_id_t actor, int8_t dx, int8_t dy)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = movement_system_try_move(actor, dx, dy);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;    
}

bool_t system_movement_location_equal(entity_id_t entity1, entity_id_t entity2)
{
    uint8_t current_bank;
    bool_t status;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_MOVEMENT_SYSTEM);  /* Page actions system into 8k MMU slot 6 */    

    status = movement_system_location_equal(entity1, entity2);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return status;    
}

/* Item system*/

void system_item_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ITEM_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    item_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  
}

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

void system_item_print_name(text_window_t *win, item_kind_t kind)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ITEM_SYSTEM);  /* Page timer system into 8k MMU slot 6 */    

    item_system_print_name(win, kind);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */  

}