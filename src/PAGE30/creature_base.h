/**
 * @file creature_base.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CREATURE_BASE_H
#define CREATURE_BASE_H

#include "../creature_comp_priv.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void creature_base_init(uint8_t creature, uint8_t kind);

extern const creature_comp_base_t creature_bases[];

#endif // CREATURE_BASE_H
