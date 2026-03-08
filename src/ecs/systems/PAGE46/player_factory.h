/**
 * @file player_factory.h
 * @author Paul Johnson
 * @brief Player character creation and initialisation
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "ecs/systems/PAGE42/event_system.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
entity_id_t player_factory_create(void);

#endif // PLAYER_FACTORY_H
