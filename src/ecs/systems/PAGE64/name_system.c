/**
 * @file name_system.c
 * @author Paul Johnson
 * @brief name system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE64/name_system.h"

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "ecs/components/name_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private variables
 ***************************************************/
static const char *name_base[NAME_COUNT] = 
{
    [NAME_NONE] = "NONE",
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    [NAME_RAT] = "Rat",
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [NAME_COMMONER] = "Commoner",
    [NAME_PLAYER] = "You",
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [NAME_WITHERWEED] = "Witherweed",
    /* MONSTER_CLASS_UNDEAD */

    /* Melee weapons */
    [NAME_CLUB] = "club",
    [NAME_SHORT_SWORD] = "short sword",
    /* Ranged weapons*/
    [NAME_SHORT_BOW] = "short bow",
    /* Armour */    
    [NAME_LEATHER_ARMOUR] = "leather armour",
    /* Shields */
    [NAME_SHIELD] = "shield",
    /* Ammo */
    [NAME_ARROW] = "arrow",
    /* Potions */    
    [NAME_POTION_OF_HEALING] = "potion of healing",
    /* Scrolls */
    /* Food and drink */
    [NAME_BREAD] = "bread",
    /* Rings */
    [NAME_RING_OF_STRENGTH] = "ring of strength",
    /* Wands */
    /* Light sources */
    /* Keys */
    [NAME_KEY] = "key",
    /* Quest items */
    [NAME_AMULET] = "Amulet of Yendor",

    // Doors
    [NAME_CLOSED_DOOR] = "closed door",
    [NAME_OPEN_DOOR] = "open door",
    // Containers & Storage
    [NAME_CHEST] = "chest",
    // Alters
    // Mechanisms (levers, switches, )
    // Traps (hidden)
    // Statues
    // Stairs
    [NAME_UP_STAIRS] = "up stairs",
    [NAME_DOWN_STAIRS] = "down stairs",
    // Hazards
};

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
void name_system_print(text_window_t *win, name_id_t name)
{
   text_print_string(win, name_base[name]);
}
 
 /***************************************************
 * private functions
 ***************************************************/