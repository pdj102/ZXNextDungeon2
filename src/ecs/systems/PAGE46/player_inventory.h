/**
 * @file player_inventory.h
 * @author Paul Johnson
 * @brief Player inventory management actions
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef PLAYER_INVENTORY_H
#define PLAYER_INVENTORY_H

/***************************************************
 * public function prototypes
 ***************************************************/
void player_inventory_show(void);
void player_inventory_drop(void);
void player_inventory_eat(void);
void player_inventory_equip(void);
void player_inventory_unequip(void);

#endif // PLAYER_INVENTORY_H
