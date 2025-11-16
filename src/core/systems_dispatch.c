/**
 * @file systems_dispatch.c
 * @author Paul  Johnson
 * @brief Game SYSTEMS_DISPATCH
 */

#include "systems_dispatch.h"

#include <arch/zxn.h>

#include "zxnext.h"

#include "../ecs/systems/PAGE38/timer_system.h"
#include "../ecs/systems/PAGE40/container_system.h"


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

/* Container System */
void system_container_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_init();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}
bool_t system_container_place_item_in(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;
    bool_t success;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    success = container_system_place_item_in(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */

    return success;
}
void system_container_remove_item_from(entity_id_t container, entity_id_t item)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_remove_item_from(container, item);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}
void system_container_mark_contents_for_destruction(entity_id_t container)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_mark_contents_for_destruction(container);

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}
void system_container_clean_up(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();         /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_CONTAINER_SYSTEM);  /* Page container system into 8k MMU slot 6 */    

    container_system_clean_up();

    ZXN_WRITE_MMU6(current_bank);       /* restore previous bank */
}