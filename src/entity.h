/**
 * @file entity.h
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
/***************************************************
 * public types
 ***************************************************/
typedef uint8_t entity_id_t; /* Type for entity IDs */

/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);
entity_id_t entity_create(void);
void entity_destroy(entity_id_t id);

#endif // ENTITY_H
