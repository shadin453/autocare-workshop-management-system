#ifndef INVENTORY_H
#define INVENTORY_H

#include "common.h"

int inventoryLogin(void);
void inventoryMenu(void);

void addInventoryItem(void);
void viewInventory(void);
void searchInventoryItem(void);
void updateInventoryItem(void);
void deleteInventoryItem(void);

#endif