/**
 * @file equipment_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIPMENT_SYSTEM_H
#define EQUIPMENT_SYSTEM_H

#include <sys\types.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void equipment_system_init(void);

void equipment_system_clean_up(entity_id_t id);

#endif // EQUIPMENT_SYSTEM_H
